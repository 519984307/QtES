%{Cpp:LicenseTemplate}\
#ifndef %{JS: Cpp.headerGuard('%{ServiceHdrFileName}')}
#define %{JS: Cpp.headerGuard('%{ServiceHdrFileName}')}

#include <QObject>

namespace %{PluginName} {

class Service
{
public:
    virtual ~Service() {}
};

} // namespace %{PluginName}

#define %{PluginName}_Service_iid "wg.es.pluginframework.%{PluginName}.service"
Q_DECLARE_INTERFACE(%{PluginName}::Service, %{PluginName}_Service_iid)

#endif // %{JS: Cpp.headerGuard('%{ServiceHdrFileName}')}
