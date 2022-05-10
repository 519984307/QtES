#include "helloqtesplugin.h"
#include "helloqtesserviceimpl.h"

#include "extensionsystem/pluginmanager.h"

#include <QDebug>
#include <QtPlugin>

namespace HelloQtES {
namespace Internal {

class HelloQtESPluginPrivate
{
    Q_DECLARE_PUBLIC(HelloQtESPlugin)
protected:
    HelloQtESPlugin *const q_ptr;

public:
    HelloQtESPluginPrivate(HelloQtESPlugin &object);
    virtual ~HelloQtESPluginPrivate();

private:
    HelloQtESServiceImpl service;
};

HelloQtESPluginPrivate::HelloQtESPluginPrivate(HelloQtESPlugin &object) : q_ptr(&object)
{
    ExtensionSystem::PluginManager::addObject(&service);
}

HelloQtESPluginPrivate::~HelloQtESPluginPrivate()
{
    ExtensionSystem::PluginManager::removeObject(&service);
}

HelloQtESPlugin::HelloQtESPlugin() : d_ptr_(new HelloQtESPluginPrivate(*this))
{
    qDebug() << __func__;
}

HelloQtESPlugin::~HelloQtESPlugin()
{
    qDebug() << __func__;
}

bool HelloQtESPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorMessage)

    qDebug() << "initialize HelloQtES Plugin";

    return true;
}

void HelloQtESPlugin::extensionsInitialized()
{
    qDebug() << "extensions initialized HelloQtES Plugin";
}

bool HelloQtESPlugin::delayedInitialize()
{
    qDebug() << "delayed initialize HelloQtES Plugin";

    return true;
}

} // namespace Internal
} // namespace HelloQtES

Q_EXPORT_PLUGIN(HelloQtES::Internal::HelloQtESPlugin)
