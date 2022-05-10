include(../plugincfg.prf)

QT += core

TEMPLATE = lib
CONFIG += plugin
TARGET = HelloQtES

HEADERS += \
    helloqtesservice.h \
    helloqtesserviceimpl.h \
    helloqtesplugin.h \

SOURCES += \
    helloqtesserviceimpl.cpp \
    helloqtesplugin.cpp \

RESOURCES += \
    resource.qrc

OTHER_FILES +=     CMakeLists.txt 
DISTFILES += HelloQtES.xml

deployModule(HelloQtES.xml, $$PLUGINS_DIR)
#deployModule(helloqtesservice.h, $$INCLUDE_DIR/pluginsNMS/)

