include(../plugincfg.prf)

QT += core

TEMPLATE = lib
CONFIG += plugin

HEADERS += \
    helloservice.h \
    helloserviceimpl.h \
    helloplugin.h

SOURCES += \
    helloserviceimpl.cpp \
    helloplugin.cpp

DISTFILES += helloplugin.xml

deployModule(helloplugin.xml, $$PLUGINS_DIR)
