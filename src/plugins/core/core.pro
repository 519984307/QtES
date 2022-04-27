include(../plugincfg.prf)

QT += core

TEMPLATE = lib
CONFIG += plugin
TARGET = Core

HEADERS += \
    coreservice.h \
    coreserviceimpl.h \
    coreplugin.h \

SOURCES += \
    coreserviceimpl.cpp \
    coreplugin.cpp \

RESOURCES += \
    resource.qrc

DISTFILES += Core.xml

deployModule(Core.xml, $$PLUGINS_DIR)
#deployModule(coreservice.h, $$INCLUDE_DIR/pluginsNMS/)

