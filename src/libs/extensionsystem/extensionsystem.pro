include(../../../global.pri)

QT += core gui widgets

TARGET = extensionsystem
TEMPLATE = lib
DESTDIR = $$LIB_DIR

DEFINES += EXTENSIONSYSTEM_LIBRARY

unix:!macx:!freebsd*:LIBS += -ldl

INCLUDEPATH += $$PWD/../

HEADERS += \
    pluginerrorview.h \
    plugindetailsview.h \
    invoker.h \
    iplugin.h \
    iplugin_p.h \
    extensionsystem_global.h \
    pluginmanager.h \
    pluginmanager_p.h \
    pluginspec.h \
    pluginspec_p.h \
    pluginview.h \
    optionsparser.h \
    plugincollection.h \
    pluginerroroverview.h \
    aggregate.h

SOURCES += \
    pluginerrorview.cpp \
    plugindetailsview.cpp \
    invoker.cpp \
    iplugin.cpp \
    pluginmanager.cpp \
    pluginspec.cpp \
    pluginview.cpp \
    optionsparser.cpp \
    plugincollection.cpp \
    pluginerroroverview.cpp \
    aggregate.cpp

FORMS += \
    pluginview.ui \
    pluginerrorview.ui \
    plugindetailsview.ui \
    pluginerroroverview.ui

RESOURCES += pluginview.qrc

OTHER_FILES += \
    CMakeLists.txt \
