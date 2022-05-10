%{Cpp:LicenseTemplate}\
#ifndef %{JS: Cpp.headerGuard('%{PluginHdrFileName}')}
#define %{JS: Cpp.headerGuard('%{PluginHdrFileName}')}

#include <extensionsystem/iplugin.h>

namespace %{PluginName} {
namespace Internal {

class %{PluginClassCN}Private;

class %{PluginClassCN} : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.DJEL.QtES.Plugin" FILE "%{PluginName}.json")

public:
    explicit %{PluginClassCN}();
    ~%{PluginClassCN}();

    bool initialize(const QStringList &arguments, QString *errorMessage);
    void extensionsInitialized();
    bool delayedInitialize();

private:
    std::unique_ptr<Internal::%{PluginClassCN}Private> const d_ptr_;

private:
    Q_DISABLE_COPY(%{PluginClassCN})
    Q_DECLARE_PRIVATE_D(d_ptr_.get(), Internal::%{PluginClassCN})
};

} // namespace Internal
} // namespace %{PluginName}

#endif // %{JS: Cpp.headerGuard('%{PluginHdrFileName}')}
