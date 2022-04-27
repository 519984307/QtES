include(../plugincfg.prf)

QT += core

TEMPLATE = lib
CONFIG += plugin
TARGET = %{PluginName}

HEADERS += \\
    %{ServiceHdrFileName} \\
    %{ServiceImplHdrFileName} \\
    %{PluginHdrFileName} \\

SOURCES += \\
    %{ServiceImplSrcFileName} \\
    %{PluginSrcFileName} \\

RESOURCES += \\
    resource.qrc

DISTFILES += %{PluginName}.xml

deployModule(%{PluginName}.xml, $$PLUGINS_DIR)
#deployModule(%{ServiceHdrFileName}, $$INCLUDE_DIR/pluginsNMS/)

