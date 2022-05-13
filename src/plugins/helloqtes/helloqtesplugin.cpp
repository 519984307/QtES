#include "helloqtesplugin.h"

#include "extensionsystem/pluginmanager.h"
#include "helloqtesserviceimpl.h"
#include <extensionsystem/pluginview.h>

#include <QDebug>
#include <QVBoxLayout>
#include <QWidget>
#include <QtPlugin>

namespace HelloQtES {
namespace Internal {

class HelloQtESPluginPrivate
{
    Q_DECLARE_PUBLIC(HelloQtESPlugin)

public:
    HelloQtESPluginPrivate(HelloQtESPlugin &object);
    virtual ~HelloQtESPluginPrivate();

protected:
    HelloQtESPlugin *const q_ptr;

private:
    HelloQtESServiceImpl service;
    std::unique_ptr<QWidget> widget;
};

HelloQtESPluginPrivate::HelloQtESPluginPrivate(HelloQtESPlugin &object) : q_ptr(&object)
{
    ExtensionSystem::PluginManager::addObject(&service);
    widget = std::unique_ptr<QWidget>(new QWidget);
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
    ExtensionSystem::PluginView *view = new ExtensionSystem::PluginView();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(view);
    d_ptr_->widget->setLayout(layout);
    d_ptr_->widget->show();

    return true;
}

} // namespace Internal
} // namespace HelloQtES

Q_EXPORT_PLUGIN(HelloQtES::Internal::HelloQtESPlugin)
