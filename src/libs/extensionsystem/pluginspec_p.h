
#ifndef PLUGINSPEC_P_H
#define PLUGINSPEC_P_H

#include "iplugin.h"
#include "pluginspec.h"

#include <QObject>
#include <QStringList>
#include <QXmlStreamReader>

namespace ExtensionSystem {

class IPlugin;
class PluginManager;

namespace Internal {

class EXTENSIONSYSTEM_EXPORT PluginSpecPrivate : public QObject
{
    Q_OBJECT

public:
    PluginSpecPrivate(PluginSpec *spec);

    bool read(const QString &fileName);
    bool provides(const QString &pluginName, const QString &version) const;
    bool resolveDependencies(const QList<PluginSpec *> &specs);
    bool loadLibrary();
    bool initializePlugin();
    bool initializeExtensions();
    bool delayedInitialize();
    IPlugin::ShutdownFlag stop();
    void kill();

    QString name;
    QString version;
    QString compatVersion;
    bool experimental;
    bool disabledByDefault;
    QString vendor;
    QString copyright;
    QString license;
    QString description;
    QString url;
    QString category;
    QList<PluginDependency> dependencies;
    bool enabledInSettings;
    bool disabledIndirectly;
    bool forceEnabled;
    bool forceDisabled;

    QString location;
    QString filePath;
    QStringList arguments;

    QHash<PluginDependency, PluginSpec *> dependencySpecs;
    PluginSpec::PluginArgumentDescriptions argumentDescriptions;
    IPlugin *plugin;

    PluginSpec::State state;
    bool hasError;
    QString errorString;

    static bool isValidVersion(const QString &version);
    static int versionCompare(const QString &version1, const QString &version2);

    void disableIndirectlyIfDependencyDisabled();

private:
    PluginSpec *q;

    bool reportError(const QString &err);
    void readPluginSpec(QXmlStreamReader &reader);
    void readDependencies(QXmlStreamReader &reader);
    void readDependencyEntry(QXmlStreamReader &reader);
    void readArgumentDescriptions(QXmlStreamReader &reader);
    void readArgumentDescription(QXmlStreamReader &reader);
    bool readBooleanValue(QXmlStreamReader &reader, const char *key);

    static QRegExp &versionRegExp();
};

} // namespace Internal
} // namespace ExtensionSystem

#endif // PLUGINSPEC_P_H
