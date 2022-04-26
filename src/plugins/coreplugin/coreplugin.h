#ifndef CORE_PLUGIN_H
#define CORE_PLUGIN_H

#include <extensionsystem/iplugin.h>

namespace Core {
namespace Internal {

class CorePlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.DJEL.QtES.Plugin.CorePlugin" FILE "coreplugin.xml")

public:
    CorePlugin();
    ~CorePlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage);
    void extensionsInitialized();
    bool delayedInitialize();
};

} // namespace Internal
} // namespace Core

#endif // CORE_PLUGIN_H
