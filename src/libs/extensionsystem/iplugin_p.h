
#ifndef IPLUGIN_P_H
#define IPLUGIN_P_H

#include "iplugin.h"

#include <QString>

namespace ExtensionSystem {

class PluginManager;
class PluginSpec;

namespace Internal {

class IPluginPrivate
{
public:
    PluginSpec *pluginSpec;

    QList<QObject *> addedObjectsInReverseOrder;
};

} // namespace Internal
} // namespace ExtensionSystem

#endif // IPLUGIN_P_H
