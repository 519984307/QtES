#include "%{PluginHdrFileName}"
#include "%{ServiceImplHdrFileName}"

#include "extensionsystem/pluginmanager.h"

#include <QDebug>
#include <QtPlugin>

namespace %{PluginName} {
namespace Internal {

class %{PluginClassCN}Private
{
    Q_DECLARE_PUBLIC(%{PluginClassCN})
protected:
    %{PluginClassCN} *const q_ptr;

public:
    %{PluginClassCN}Private(%{PluginClassCN} &object);
    virtual ~%{PluginClassCN}Private();

private:
    %{ServiceImpl} service;
};

%{PluginClassCN}Private::%{PluginClassCN}Private(%{PluginClassCN} &object) : q_ptr(&object)
{
    ExtensionSystem::PluginManager::addObject(&service);
}

%{PluginClassCN}Private::~%{PluginClassCN}Private()
{
    ExtensionSystem::PluginManager::removeObject(&service);
}

%{PluginClassCN}::%{PluginClassCN}() : d_ptr_(new %{PluginClassCN}Private(*this))
{
    qDebug() << __func__;
}

%{PluginClassCN}::~%{PluginClassCN}()
{
    qDebug() << __func__;
}

bool %{PluginClassCN}::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorMessage)

    qDebug() << "initialize %{PluginName} Plugin";

    return true;
}

void %{PluginClassCN}::extensionsInitialized()
{
    qDebug() << "extensions initialized %{PluginName} Plugin";
}

bool %{PluginClassCN}::delayedInitialize()
{
    qDebug() << "delayed initialize %{PluginName} Plugin";

    return true;
}

} // namespace Internal
} // namespace %{PluginName}

Q_EXPORT_PLUGIN(%{PluginName}::Internal::%{PluginClassCN})
