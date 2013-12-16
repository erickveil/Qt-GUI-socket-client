#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include "QMutex"
#include "QThread"
#include "QTcpServer"
#include "QTcpSocket"
#include "QVector"
#include "QString"
#include "socketthreadbase.h"

class EchoServer : public SocketThreadBase, QThread
{
public:
    EchoServer(const QString &ipAddr, const ushort port ) : SocketThreadBase( ipAddr, port ) {}
    void startThread();
    void stopThread();
    Identity getIdentity() { return SERVER; }
protected:
    void run();
    void echoServer( QTcpSocket *client );
};

#endif // ECHOSERVER_H
