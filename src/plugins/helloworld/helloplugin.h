#ifndef HELLO_PLUGIN_H
#define HELLO_PLUGIN_H

#include <extensionsystem/iplugin.h>

namespace Hello {
namespace Internal {

class HelloPluginPrivate;

class HelloPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID "org.DJEL.QtES.Plugin.HelloPlugin" FILE "helloplugin.xml")

public:
    HelloPlugin();
    ~HelloPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage);
    void extensionsInitialized();
    bool delayedInitialize();

private:
    std::unique_ptr<Internal::HelloPluginPrivate> d_ptr_;
    Q_DISABLE_COPY(HelloPlugin)
    Q_DECLARE_PRIVATE_D(d_ptr_.get(), Internal::HelloPlugin)
};

} // namespace Internal
} // namespace Hello

#endif // HELLO_PLUGIN_H
