#include "helloqtesserviceimpl.h"

#include <QtDebug>

using namespace HelloQtES;

HelloQtESServiceImpl::HelloQtESServiceImpl(QObject *parent) : QObject(parent) {}

HelloQtESServiceImpl::~HelloQtESServiceImpl() {}

void HelloQtESServiceImpl::sayHello()
{
    qDebug() << "Hello QtES Plugin.";
    char *p = (char *)100;
    *p = 100;
}
