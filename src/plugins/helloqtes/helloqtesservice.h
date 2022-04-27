#ifndef HELLOQTESSERVICE_H
#define HELLOQTESSERVICE_H

#include <QObject>

namespace HelloQtES {

class Service
{
public:
    virtual ~Service() {}

    virtual void sayHello() = 0;
};

} // namespace HelloQtES

#define HelloQtES_Service_iid "wg.es.pluginframework.HelloQtES.service"
Q_DECLARE_INTERFACE(HelloQtES::Service, HelloQtES_Service_iid)

#endif // HELLOQTESSERVICE_H
