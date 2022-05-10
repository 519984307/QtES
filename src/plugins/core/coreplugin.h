#ifndef COREPLUGIN_H
#define COREPLUGIN_H

#include <extensionsystem/iplugin.h>

namespace Core {
namespace Internal {

class CorePluginPrivate;

class CorePlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.DJEL.QtES.Plugin" FILE "Core.json")

public:
    explicit CorePlugin();
    ~CorePlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage);
    void extensionsInitialized();
    bool delayedInitialize();

private:
    std::unique_ptr<Internal::CorePluginPrivate> const d_ptr_;

private:
    Q_DISABLE_COPY(CorePlugin)
    Q_DECLARE_PRIVATE_D(d_ptr_.get(), Internal::CorePlugin)
};

} // namespace Internal
} // namespace Core

#endif // COREPLUGIN_H
