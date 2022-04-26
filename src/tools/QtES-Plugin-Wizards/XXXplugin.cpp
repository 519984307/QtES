#include "%{PluginHdrFileName}"
#include "%{ServiceImplHdrFileName}"

#include "extensionsystem/pluginmanager.h"

#include <QDebug>
#include <QtPlugin>

namespace %{PluginName} {
namespace Internal {

class %{PluginCN}Private
{
    Q_DECLARE_PUBLIC(%{PluginCN})
protected:
    %{PluginCN} *const q_ptr;

public:
    %{PluginCN}Private(%{PluginCN} &object);
    virtual ~%{PluginCN}Private();

private:
    %{ServiceImpl} service;
};

%{PluginClass}Private::%{PluginClass}Private(%{PluginCN} &object) : q_ptr(&object)
{
    ExtensionSystem::PluginManager::addObject(&service);
}

%{PluginClass}Private::~%{PluginClass}Private()
{
    ExtensionSystem::PluginManager::removeObject(&service);
}

%{PluginClass}::%{PluginClass}() : d_ptr_(new %{PluginCN}Private(*this))
{
    qDebug() << __func__;
}

%{PluginClass}::~%{PluginClass}()
{
    qDebug() << __func__;
}

bool %{PluginClass}::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorMessage)

    qDebug() << "initialize %{PluginName} Plugin";

    return true;
}

void %{PluginClass}::extensionsInitialized()
{
    qDebug() << "extensions initialized %{PluginName} Plugin";
}

bool %{PluginClass}::delayedInitialize()
{
    qDebug() << "delayed initialize %{PluginName} Plugin";

    return true;
}

} // namespace Internal
} // namespace %{PluginName}


Q_EXPORT_PLUGIN(%{PluginName}::Internal::%{PluginClass})
