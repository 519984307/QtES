%{Cpp:LicenseTemplate}\
#ifndef %{JS: Cpp.headerGuard('%{PluginHdrFileName}')}
#define %{JS: Cpp.headerGuard('%{PluginHdrFileName}')}

#include <extensionsystem/iplugin.h>

namespace %{PluginName} {
namespace Internal {

class %{PluginCN}Private;

class %{PluginClass} : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "wg.es.pluginframework" FILE "%{PluginName}.json")

public:
    explicit %{PluginClass}();
    ~%{PluginClass}();

    bool initialize(const QStringList &arguments, QString *errorMessage);
    void extensionsInitialized();
    bool delayedInitialize();

private:
    QScopedPointer<Internal::%{PluginCN}Private> d_ptr_;

private:
    Q_DISABLE_COPY(%{PluginCN})
    Q_DECLARE_PRIVATE_D(d_ptr_, Internal::%{PluginCN})
};

} // namespace Internal
} // namespace %{PluginName}

#endif // %{JS: Cpp.headerGuard('%{PluginHdrFileName}')}
