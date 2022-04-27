#ifndef CORESERVICEIMPL_H
#define CORESERVICEIMPL_H

#include "coreservice.h"

namespace Core {

class CoreServiceImplPrivate;

class CoreServiceImpl : public QObject, public Core::Service
{
    Q_OBJECT
    Q_INTERFACES(Core::Service)

public:
    explicit CoreServiceImpl(QObject *parent = nullptr);
    ~CoreServiceImpl();

};

} // namespace Core

#endif // CORESERVICEIMPL_H
