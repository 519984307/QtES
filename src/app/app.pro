include(../../global.pri)
include(../../rpath.pri)

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

SOURCES += \
    main.cpp
