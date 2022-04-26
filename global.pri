#config global parameter
#name=global
#label=公共变量定义
#description=定义工程中常用的环境变量

###### DO NOT MODIFY THIS ######

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++0x

unix:QMAKE_CXXFLAGS_DEBUG += -O3

lessThan(QT_MAJOR_VERSION, 5): INCLUDEPATH += $$PWD/Qt4/4.$$QT_MINOR_VERSION

INSTALL_DIR     = $$PWD/bin

INCLUDE_DIR = $$PWD/include
INCLUDEPATH += $$INCLUDE_DIR

SRC_DIR = $$PWD/

LIB_SRC_DIR     = $$SRC_DIR/libs
PLUGIN_SRC_DIR  = $$SRC_DIR/plugins

BIN_DIR     = $$INSTALL_DIR #/bin
LIB_DIR     = $$INSTALL_DIR #/libs
PLUGINS_DIR     = $$INSTALL_DIR/plugins



defineTest(deployModule) {
    DEPLOY_FILES = $$1
    DEPLOY_DIR = $$2
    win32:DEPLOY_DIR ~= s,/,\\,g

    isEmpty(DEPLOY_DIR) {
        return(false)
    }

    exists($$DEPLOY_DIR) {
    } else {
        lessThan(QT_MAJOR_VERSION, 5) {
            win32: system(cmd /c md $$DEPLOY_DIR)
            unix:!mac: system(mkdir $$DEPLOY_DIR)
        } else {
            mkpath($$DEPLOY_DIR)
        }
    }

    for(FILE, DEPLOY_FILES) {
        FILE = $$FILE
        win32: FILE ~= s,/,\\,g
        win32: system(cmd /c copy /y $$FILE $$DEPLOY_DIR)
        unix:!mac: system(cp $$FILE $$DEPLOY_DIR)
    }
    return(true)
}

defineTest(copyFolder) {
    SRC_FOLDER = $$1
    DEST_FOLDER = $$2
    SRC_FOLDER = $$PWD/$$SRC_FOLDER

    win32 {
        SRC_FOLDER ~= s,/,\\,g
        DEST_FOLDER ~= s,/,\\,g
    }

    isEmpty(SRC_FOLDER) {
        return(false)
    }

    isEmpty(DEST_FOLDER) {
        return(false)
    }
    win32: system(cmd /c robocopy $$SRC_FOLDER $$DEST_FOLDER /e)
    unix:!mac: system(cp -r $$SRC_FOLDER $$DEST_FOLDER)
    return(true)
}
