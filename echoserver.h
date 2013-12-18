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
   // Q_OBJECT
public:
    EchoServer(const QString &ipAddr, const ushort port ) : SocketThreadBase( ipAddr, port )
    {    }
    void startThread();
    void stopThread();
    Identity getIdentity() { return SERVER; }


protected:
    void run();
    void echoServer( QTcpSocket *client );

//signals:
//    void receivedLine();
};

#endif // ECHOSERVER_H
