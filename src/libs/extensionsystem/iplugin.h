
#ifndef IPLUGIN_H
#define IPLUGIN_H

#include "extensionsystem_global.h"

#include <QObject>
#include <memory>
#if QT_VERSION >= 0x050000
#    include <QtPlugin>
#endif

namespace ExtensionSystem {

namespace Internal {
class IPluginPrivate;
class PluginSpecPrivate;
} // namespace Internal

class PluginManager;
class PluginSpec;

class EXTENSIONSYSTEM_EXPORT IPlugin : public QObject
{
    Q_OBJECT

public:
    enum ShutdownFlag
    {
        SynchronousShutdown,
        AsynchronousShutdown
    };

    IPlugin();
    virtual ~IPlugin();

    virtual bool initialize(const QStringList &arguments, QString *errorString) = 0;
    virtual void extensionsInitialized() = 0;
    virtual bool delayedInitialize() { return false; }
    virtual ShutdownFlag aboutToShutdown() { return SynchronousShutdown; }
    virtual QObject *remoteCommand(const QStringList & /* options */,
                                   const QStringList & /* arguments */)
    {
        return 0;
    }

    PluginSpec *pluginSpec() const;

    void addObject(QObject *obj);
    void addAutoReleasedObject(QObject *obj);
    void removeObject(QObject *obj);

signals:
    void asynchronousShutdownFinished();

private:
    Internal::IPluginPrivate *d;

    friend class Internal::PluginSpecPrivate;
};

} // namespace ExtensionSystem

// The macros Q_EXPORT_PLUGIN, Q_EXPORT_PLUGIN2 become obsolete in Qt 5.
#if QT_VERSION >= 0x050000
#    if defined(Q_EXPORT_PLUGIN)
#        undef Q_EXPORT_PLUGIN
#        undef Q_EXPORT_PLUGIN2
#    endif
#    define Q_EXPORT_PLUGIN(plugin)
#    define Q_EXPORT_PLUGIN2(function, plugin)
#else
#    define Q_PLUGIN_METADATA(x)
#endif

#endif // IPLUGIN_H
