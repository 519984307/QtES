
#ifndef PLUGINSPEC_H
#define PLUGINSPEC_H

#include "extensionsystem_global.h"

#include <QString>
#include <QList>
#include <QHash>

QT_BEGIN_NAMESPACE
class QStringList;
QT_END_NAMESPACE

namespace ExtensionSystem {

namespace Internal {
    class PluginSpecPrivate;
    class PluginManagerPrivate;
}

class IPlugin;

struct EXTENSIONSYSTEM_EXPORT PluginDependency
{
    enum Type {
        Required,
        Optional
    };

    PluginDependency() : type(Required) {}

    QString name;
    QString version;
    Type type;
    bool operator==(const PluginDependency &other) const;

    QString toString() const;
};

uint qHash(const ExtensionSystem::PluginDependency &value);

struct EXTENSIONSYSTEM_EXPORT PluginArgumentDescription
{
    QString name;
    QString parameter;
    QString description;
};

class EXTENSIONSYSTEM_EXPORT PluginSpec
{
public:
    enum State { Invalid, Read, Resolved, Loaded, Initialized, Running, Stopped, Deleted};

    ~PluginSpec();

    // information from the xml file, valid after 'Read' state is reached
    QString name() const;
    QString version() const;
    QString compatVersion() const;
    QString vendor() const;
    QString copyright() const;
    QString license() const;
    QString description() const;
    QString url() const;
    QString category() const;
    bool isExperimental() const;
    bool isDisabledByDefault() const;
    bool isEnabledInSettings() const;
    bool isEffectivelyEnabled() const;
    bool isDisabledIndirectly() const;
    bool isForceEnabled() const;
    bool isForceDisabled() const;
    QList<PluginDependency> dependencies() const;

    typedef QList<PluginArgumentDescription> PluginArgumentDescriptions;
    PluginArgumentDescriptions argumentDescriptions() const;

    // other information, valid after 'Read' state is reached
    QString location() const;
    QString filePath() const;

    void setEnabled(bool value);
    void setDisabledByDefault(bool value);
    void setDisabledIndirectly(bool value);
    void setForceEnabled(bool value);
    void setForceDisabled(bool value);

    QStringList arguments() const;
    void setArguments(const QStringList &arguments);
    void addArgument(const QString &argument);

    bool provides(const QString &pluginName, const QString &version) const;

    // dependency specs, valid after 'Resolved' state is reached
    QHash<PluginDependency, PluginSpec *> dependencySpecs() const;

    // linked plugin instance, valid after 'Loaded' state is reached
    IPlugin *plugin() const;

    // state
    State state() const;
    bool hasError() const;
    QString errorString() const;

private:
    PluginSpec();

    Internal::PluginSpecPrivate *d;
    friend class Internal::PluginManagerPrivate;
    friend class Internal::PluginSpecPrivate;
};

} // namespace ExtensionSystem

#endif // PLUGINSPEC_H

