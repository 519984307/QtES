#ifndef HELLOQTESSERVICEIMPL_H
#define HELLOQTESSERVICEIMPL_H

#include "helloqtesservice.h"

namespace HelloQtES {

class HelloQtESServiceImplPrivate;

class HelloQtESServiceImpl : public QObject, public HelloQtES::Service
{
    Q_OBJECT
    Q_INTERFACES(HelloQtES::Service)

public:
    explicit HelloQtESServiceImpl(QObject *parent = nullptr);
    ~HelloQtESServiceImpl();

    void sayHello() override;
};

} // namespace HelloQtES

#endif // HELLOQTESSERVICEIMPL_H
