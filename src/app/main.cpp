#include <extensionsystem/iplugin.h>
#include <extensionsystem/pluginmanager.h>
#include <extensionsystem/pluginspec.h>
#include "../plugins/helloworld/helloservice.h"

#include "extensionsystem/pluginview.h"

#include <QApplication>
#include <QFileInfo>
#include <QDebug>
#include <QList>

using namespace ExtensionSystem;

const char corePluginNameC[] = "coreplugin";

static void printSpecs(QList<PluginSpec *> plugins)
{
    qDebug() << "==================== get specs started ====================";

    for (int i = 0; i < plugins.count(); ++i) {
        PluginSpec *spec = plugins[i];

        if (i != 0)
            qDebug() << "########################################";

        qDebug() << "name:" << spec->name();
        qDebug() << "version:" << spec->version();
        qDebug() << "compatVersion:" << spec->compatVersion();
        qDebug() << "vendor:" << spec->vendor();
        qDebug() << "copyright:" << spec->copyright();
        qDebug() << "license:" << spec->license();
        qDebug() << "description:" << spec->description();
        qDebug() << "url:" << spec->url();
        qDebug() << "category:" << spec->category();

        QList<PluginDependency> vector = spec->dependencies();
        foreach (PluginDependency dep, vector) {
            qDebug() << "Depends:" << dep.toString();
        }

        qDebug() << "errorString:" << spec->errorString();
    }

    qDebug() << "==================== get specs finished ====================";
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QString pluginPath = QApplication::applicationDirPath() + "/plugins/";

    PluginManager pluginManager;
    PluginManager::setPluginPaths(QStringList() << pluginPath);

    const QList<PluginSpec *> plugins = PluginManager::plugins();
    PluginSpec *coreplugin = nullptr;

    printSpecs(plugins);

    foreach (PluginSpec *spec, plugins) {
        if (spec->name() == QLatin1String(corePluginNameC)) {
            coreplugin = spec;
            break;
        }
    }

    if (coreplugin == nullptr) {
        qCritical() << "Could not find Core plugin.";
        return 1;
    }

    if (!coreplugin->isEffectivelyEnabled()) {
        qCritical() << "Core plugin is disabled.";
        return 1;
    }

    if (coreplugin->hasError()) {
        qCritical() << coreplugin->errorString();
        return 1;
    }


    PluginManager::loadPlugins();
    if (coreplugin->hasError()) {
        qWarning() << "Failed to load core:" << coreplugin->errorString();
        return 1;
    }

    Hello::Service *helloService = PluginManager::getObject<Hello::Service>();
    if (helloService != nullptr)
        helloService->sayHello();

    QObject::connect(&app, SIGNAL(aboutToQuit()), &pluginManager, SLOT(shutdown()));

    PluginManager::instance()->shutdown();

    return app.exec();
}
