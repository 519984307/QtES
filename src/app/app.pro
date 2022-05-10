include(../../global.pri)
include(../../rpath.pri)

include(../shared/qtsingleapplication/qtsingleapplication.pri)

QT += core gui widgets

CONFIG += console
TEMPLATE  = app
DESTDIR = $$BIN_DIR

DEFINES += ENABLE_QT_BREAKPAD

INCLUDEPATH += \
    $$PWD/ \
    $$PWD/../ \
    $$PWD/../libs/ \
    $$PWD/../plugins/

LIBS += -L$$LIB_DIR/ -lextensionsystem

HEADERS += \
    app_version.h

SOURCES += \
    main.cpp \

contains(DEFINES, ENABLE_QT_BREAKPAD){

}else{
    HEADERS += \
        ../tools/crashhandler/crashhandlersetup.h \

    SOURCES += \
        ../tools/crashhandler/crashhandlersetup.cpp \
}

OTHER_FILES += \
    CMakeLists.txt \
