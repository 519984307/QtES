
#include "../plugins/helloqtes/helloqtesservice.h"
#include "../version_ini_tag.h"
//#include "log/logger.h"
#include "qtsingleapplication.h"
#include "version_info.h"
#include <extensionsystem/iplugin.h>
#include <extensionsystem/pluginmanager.h>
#include <extensionsystem/pluginspec.h>
#include <extensionsystem/pluginview.h>

#include <QSettings>

#ifdef ENABLE_QT_BREAKPAD

#else
#    include "../tools/crashhandler/crashhandlersetup.h"
#endif

#include <QDebug>
#include <QFileInfo>
#include <QList>
#include <QMessageBox>
#include <QThreadPool>

using namespace ExtensionSystem;

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

void writeSettings()
{
    QString AppName = QString::fromStdString(Sys::Version::appName());
    QString AppDisplayName = QString::fromStdString(Sys::Version::appDisplayName());
    QString Version = QString::fromStdString(Sys::Version::version());
    QString OrganizationName = QString::fromStdString(Sys::Version::organizationName());
    QString OrganizationDomain = QString::fromStdString(Sys::Version::organizationDomain());
    QString BuildDate = QString::fromStdString(Sys::Version::buildDate());
    QString BuildTime = QString::fromStdString(Sys::Version::buildTime());
    QString Commit = QString::fromStdString(Sys::Version::commit());
    QString Branch = QString::fromStdString(Sys::Version::branch());
    QString Tag = QString::fromStdString(Sys::Version::tag());
    QString FullVersion = QString::fromStdString(Sys::Version::fullVersion());

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, OrganizationName, AppName);
    settings.beginGroup(VersionIniTag::APPGROUP);
    settings.setValue(VersionIniTag::APPNAME, AppName);
    settings.setValue(VersionIniTag::APPDISPLAYNAME, AppDisplayName);
    settings.setValue(VersionIniTag::VERSION, Version);
    settings.setValue(VersionIniTag::ORGANIZATIONNAME, OrganizationName);
    settings.setValue(VersionIniTag::ORGANIZATIONDOMAIN, OrganizationDomain);
    settings.setValue(VersionIniTag::BUILDDATE, BuildDate);
    settings.setValue(VersionIniTag::BUILDTIME, BuildTime);
    settings.setValue(VersionIniTag::COMMIT, Commit);
    settings.setValue(VersionIniTag::BRANCH, Branch);
    settings.setValue(VersionIniTag::TAG, Tag);
    settings.setValue(VersionIniTag::FULLVERSION, FullVersion);
    settings.endGroup();
}

void crashtest()
{
    char *p = (char *)100;
    *p = 100;
}

const char helloQtESPluginNameC[] = "helloqtes";

int main(int argc, char **argv)
{
    // setting
    writeSettings();

    QString AppName = QString::fromStdString(Sys::Version::appName());
    QString Version = QString::fromStdString(Sys::Version::version().c_str());
    QString OrganizationName = QString::fromStdString(Sys::Version::organizationName());
    QString OrganizationDomain = QString::fromStdString(Sys::Version::organizationDomain());

    SharedTools::QtSingleApplication app(AppName, argc, argv);
    app.setApplicationName(AppName);
    app.setApplicationVersion(Version);
    app.setOrganizationName(OrganizationName);
    app.setOrganizationDomain(OrganizationDomain);

    if (app.isRunning()) {
        QString log = QString("%1 is running.").arg(AppName);
        qWarning() << log;
        QMessageBox::warning(nullptr, "warning", log);
        return 0;
    }

    // log
    // Log::logger::instance().init("logs/test.log");
    // LOG_INFO(Sys::Version::fullVersion());

    const int threadCount = QThreadPool::globalInstance()->maxThreadCount();
    QThreadPool::globalInstance()->setMaxThreadCount(qMax(4, 2 * threadCount));

#ifdef ENABLE_QT_BREAKPAD
    // QtSystemExceptionHandler systemExceptionHandler(libexecPath);
#else
    // Display a backtrace once a serious signal is delivered.
    CrashHandlerSetup setupCrashHandler(AppName, OrganizationName);
#endif

    QString pluginPath = QApplication::applicationDirPath() + "/plugins/";
    PluginManager pluginManager;
    PluginManager::setPluginPaths(QStringList() << pluginPath);

    QObject::connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    QObject::connect(&app, SIGNAL(aboutToQuit()), &pluginManager, SLOT(shutdown()));

    const QList<PluginSpec *> plugins = PluginManager::plugins();
    PluginSpec *helloQtESPlugin = nullptr;

    printSpecs(plugins);

    foreach (PluginSpec *spec, plugins) {
        if (spec->name() == QLatin1String(helloQtESPluginNameC)) {
            helloQtESPlugin = spec;
            break;
        }
    }

    if (helloQtESPlugin == nullptr) {
        qCritical() << QString("Could not find %1 plugin.").arg(helloQtESPluginNameC);
        return 1;
    }

    if (!helloQtESPlugin->isEffectivelyEnabled()) {
        qCritical() << QString("%1 plugin is disabled.").arg(helloQtESPluginNameC);
        return 1;
    }

    if (helloQtESPlugin->hasError()) {
        qCritical() << QString("Failed to load %1 :").arg(helloQtESPluginNameC)
                    << helloQtESPlugin->errorString();
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

    HelloQtES::Service *helloQtESService = PluginManager::getObject<HelloQtES::Service>();
    if (helloQtESService != nullptr)
        helloQtESService->sayHello();

    // crashtest();

    // PluginManager::instance()->shutdown();
    // PluginView view;
    // view.show();

    const int r = app.exec();
    return r;
}
