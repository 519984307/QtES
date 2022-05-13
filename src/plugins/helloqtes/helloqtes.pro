include(../plugincfg.prf)

QT += core

TEMPLATE = lib
CONFIG += plugin
TARGET = helloqtes

HEADERS += \
    helloqtesservice.h \
    helloqtesserviceimpl.h \
    helloqtesplugin.h \

SOURCES += \
    helloqtesserviceimpl.cpp \
    helloqtesplugin.cpp \

RESOURCES += \
    resource.qrc

OTHER_FILES += \
    CMakeLists.txt \

DISTFILES += helloqtes.xml

deployModule(helloqtes.xml, $$PLUGINS_DIR)
#deployModule(helloqtesservice.h, $$INCLUDE_DIR/pluginsNMS/)

