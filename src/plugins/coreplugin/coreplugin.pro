include(../plugincfg.prf)

QT += core gui

TEMPLATE = lib
CONFIG += plugin

HEADERS += \
    coreplugin.h

SOURCES += \
    coreplugin.cpp

DISTFILES += coreplugin.xml

#description.files += coreplugin.xml
#description.path = $$PLUGINS_DIR/
#INSTALLS += description

deployModule(coreplugin.xml, $$PLUGINS_DIR)
