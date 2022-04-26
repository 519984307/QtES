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
    Q_PLUGIN_METADATA(IID "org.DJEL.QtES.Plugin.%{PluginName}" FILE "%{PluginName}.xml")

public:
    explicit %{PluginClass}();
    ~%{PluginClass}();

    bool initialize(const QStringList &arguments, QString *errorMessage);
    void extensionsInitialized();
    bool delayedInitialize();

private:
    std::unique_ptr<Internal::%{PluginCN}Private> d_ptr_;

private:
    Q_DISABLE_COPY(%{PluginCN})
    Q_DECLARE_PRIVATE_D(d_ptr_.get(), Internal::%{PluginCN})
};

} // namespace Internal
} // namespace %{PluginName}

#endif // %{JS: Cpp.headerGuard('%{PluginHdrFileName}')}
