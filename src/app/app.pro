include(../../global.pri)
include(../../rpath.pri)

include(../shared/qtsingleapplication/qtsingleapplication.pri)

QT += core gui widgets

CONFIG += console
TEMPLATE  = app
DESTDIR = $$BIN_DIR

INCLUDEPATH += \
    $$PWD/ \
    $$PWD/../ \
    $$PWD/../libs/ \
    $$PWD/../plugins/

LIBS += -L$$LIB_DIR/ -lextensionsystem

HEADERS += \
    ../tools/crashhandler/crashhandlersetup.h \
    app_version.h

SOURCES += \
    main.cpp \
    ../tools/crashhandler/crashhandlersetup.cpp
