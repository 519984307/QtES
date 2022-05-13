include(../plugincfg.prf)

QT += core

TEMPLATE = lib
CONFIG += plugin
TARGET = %{ProjectName}

HEADERS += \\
    %{ServiceHdrFileName} \\
    %{ServiceImplHdrFileName} \\
    %{PluginHdrFileName} \\

SOURCES += \\
    %{ServiceImplSrcFileName} \\
    %{PluginSrcFileName} \\

RESOURCES += \\
    resource.qrc

OTHER_FILES += \\
    CMakeLists.txt \\

DISTFILES += %{ProjectName}.xml

deployModule(%{ProjectName}.xml, $$PLUGINS_DIR)
#deployModule(%{ServiceHdrFileName}, $$INCLUDE_DIR/pluginsNMS/)

