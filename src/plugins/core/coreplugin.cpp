#include "coreplugin.h"
#include "coreserviceimpl.h"

#include "extensionsystem/pluginmanager.h"

#include <QDebug>
#include <QtPlugin>

namespace Core {
namespace Internal {

class CorePluginPrivate
{
    Q_DECLARE_PUBLIC(CorePlugin)
protected:
    CorePlugin *const q_ptr;

public:
    CorePluginPrivate(CorePlugin &object);
    virtual ~CorePluginPrivate();

private:
    CoreServiceImpl service;
};

CorePluginPrivate::CorePluginPrivate(CorePlugin &object) : q_ptr(&object)
{
    ExtensionSystem::PluginManager::addObject(&service);
}

CorePluginPrivate::~CorePluginPrivate()
{
    ExtensionSystem::PluginManager::removeObject(&service);
}

CorePlugin::CorePlugin() : d_ptr_(new CorePluginPrivate(*this))
{
    qDebug() << __func__;
}

CorePlugin::~CorePlugin()
{
    qDebug() << __func__;
}

bool CorePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorMessage)

    qDebug() << "initialize Core Plugin";

    return true;
}

void CorePlugin::extensionsInitialized()
{
    qDebug() << "extensions initialized Core Plugin";
}

bool CorePlugin::delayedInitialize()
{
    qDebug() << "delayed initialize Core Plugin";

    return true;
}

} // namespace Internal
} // namespace Core


Q_EXPORT_PLUGIN(Core::Internal::CorePlugin)
