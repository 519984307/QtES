#ifndef HELLOQTESPLUGIN_H
#define HELLOQTESPLUGIN_H

#include <extensionsystem/iplugin.h>

namespace HelloQtES {
namespace Internal {

class HelloQtESPluginPrivate;

class HelloQtESPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.DJEL.QtES.Plugin.HelloQtES" FILE "HelloQtES.xml")

public:
    explicit HelloQtESPlugin();
    ~HelloQtESPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage);
    void extensionsInitialized();
    bool delayedInitialize();

private:
    std::unique_ptr<Internal::HelloQtESPluginPrivate> d_ptr_;

private:
    Q_DISABLE_COPY(HelloQtESPlugin)
    Q_DECLARE_PRIVATE_D(d_ptr_.get(), Internal::HelloQtESPlugin)
};

} // namespace Internal
} // namespace HelloQtES

#endif // HELLOQTESPLUGIN_H
