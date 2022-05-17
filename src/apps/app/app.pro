include(../../../global.pri)
include(../../../rpath.pri)

include(../../shared/qtsingleapplication/qtsingleapplication.pri)

QT += core gui widgets

CONFIG += console
TEMPLATE  = app
DESTDIR = $$BIN_DIR

win32: DEFINES += ENABLE_QT_BREAKPAD

INCLUDEPATH += \
    $$PWD/ \
    $$PWD/../ \
    $$PWD/../../libs/ \
    $$PWD/../../plugins/

LIBS += -L$$LIB_DIR/ -lextensionsystem

HEADERS += \
    version_info.h \
    ../../shared/splashscreen/splashscreen.h \
    ../version_ini_tag.h

SOURCES += \
    main.cpp \
    ../../shared/splashscreen/splashscreen.cpp \

contains(DEFINES, ENABLE_QT_BREAKPAD){

}else{
    HEADERS += \
        ../../tools/crashhandler/crashhandlersetup.h \

    SOURCES += \
        ../../tools/crashhandler/crashhandlersetup.cpp \
}

OTHER_FILES += \
    CMakeLists.txt \
