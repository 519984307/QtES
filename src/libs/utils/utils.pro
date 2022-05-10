include(../../../global.pri)

QT       += network

TARGET = utils
TEMPLATE = lib
DESTDIR = $$LIB_DIR

DEFINES += UTILS_LIBRARY

SOURCES += \
    environment.cpp \
    hostosinfo.cpp

HEADERS += \
    utils_global.h \
    environment.h \
    hostosinfo.h

OTHER_FILES += \
    CMakeLists.txt \
