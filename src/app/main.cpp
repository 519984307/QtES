
#include "../plugins/helloqtes/helloqtesservice.h"
#include "../tools/crashhandler/crashhandlersetup.h"
#include "app_version.h"
#include "qtsingleapplication.h"
#include <extensionsystem/iplugin.h>
#include <extensionsystem/pluginmanager.h>
#include <extensionsystem/pluginspec.h>
#include <extensionsystem/pluginview.h>

#include <QDebug>
#include <QFileInfo>
#include <QList>
#include <QMessageBox>
#include <QThreadPool>

using namespace ExtensionSystem;

static const char appNameC[] = "App";
static const char corePluginNameC[] = "Core";

static void printSpecs(QList<PluginSpec *> plugins)
{
    qDebug() << " ==================== Get Plugins Info Started ==================== ";

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

    qDebug() << " ==================== Get Plugins Info finished ==================== ";
}

void crashtest()
{
    char *p = (char *)100;
    *p = 100;
}

int main(int argc, char **argv)
{
    SharedTools::QtSingleApplication app((QLatin1String(appNameC)), argc, argv);
    if (app.isRunning()) {
        QString log = QString("%1 is running.").arg(QLatin1String(appNameC));
        qWarning() << log;
        QMessageBox::warning(nullptr, "warning", log);
        return 0;
    }

    const int threadCount = QThreadPool::globalInstance()->maxThreadCount();
    QThreadPool::globalInstance()->setMaxThreadCount(qMax(4, 2 * threadCount));

    // Display a backtrace once a serious signal is delivered.
    CrashHandlerSetup setupCrashHandler(Core::Constants::APP_NAME);

    QString pluginPath = QApplication::applicationDirPath() + "/plugins/";

    PluginManager pluginManager;
    PluginManager::setPluginPaths(QStringList() << pluginPath);

    QObject::connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    QObject::connect(&app, SIGNAL(aboutToQuit()), &pluginManager, SLOT(shutdown()));

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
    if (PluginManager::hasError()) {

        qWarning() << endl
                   << " ======================== Load Plugin Failed ======================= ";
        foreach (PluginSpec *spec, plugins) {
            // only show errors on startup if plugin is enabled.
            if (spec->hasError() && spec->isEnabledInSettings() && !spec->isDisabledIndirectly()) {
                qWarning() << QString("Failed to load %1:").arg(spec->name()) << endl
                           << spec->errorString() << endl;
            }
        }
        qWarning() << " =================================================================== ";
    }

    // if (coreplugin->hasError()) {
    //     qWarning() << "Failed to load Core:" << coreplugin->errorString();
    //     return 1;
    // }

    HelloQtES::Service *helloQtESService = PluginManager::getObject<HelloQtES::Service>();
    if (helloQtESService != nullptr)
        helloQtESService->sayHello();

    // crashtest();

    // PluginManager::instance()->shutdown();

    PluginView view;
    view.show();

    const int r = app.exec();
    return r;
}
