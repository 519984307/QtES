
#include "qtsinglecoreapplication.h"

#include "qtlocalpeer.h"

namespace SharedTools {

QtSingleCoreApplication::QtSingleCoreApplication(int &argc, char **argv) :
    QCoreApplication(argc, argv)
{
    peer = new QtLocalPeer(this);
    connect(peer, SIGNAL(messageReceived(QString)), SIGNAL(messageReceived(QString)));
}

QtSingleCoreApplication::QtSingleCoreApplication(const QString &appId, int &argc, char **argv) :
    QCoreApplication(argc, argv)
{
    peer = new QtLocalPeer(this, appId);
    connect(peer, SIGNAL(messageReceived(QString)), SIGNAL(messageReceived(QString)));
}

bool QtSingleCoreApplication::isRunning()
{
    return peer->isClient();
}

bool QtSingleCoreApplication::sendMessage(const QString &message, int timeout)
{
    return peer->sendMessage(message, timeout, true);
}

QString QtSingleCoreApplication::id() const
{
    return peer->applicationId();
}

} // namespace SharedTools
