#ifndef CORESERVICE_H
#define CORESERVICE_H

#include <QObject>

namespace Core {

class Service
{
public:
    virtual ~Service() {}
};

} // namespace Core

#define Core_Service_iid "wg.es.pluginframework.Core.service"
Q_DECLARE_INTERFACE(Core::Service, Core_Service_iid)

#endif // CORESERVICE_H
