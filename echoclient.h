#ifndef ECHOCLIENT_H
#define ECHOCLIENT_H

#include "QMutex"
#include "QThread"
#include "QTcpServer"
#include "QTcpSocket"
#include "QVector"
#include "QString"
#include "socketthreadbase.h"
#include "mainwindow.h"

class EchoClient : public SocketThreadBase, QThread
{
public:
    EchoClient(const QString &ipAddr, const ushort port,  QString input ) : SocketThreadBase( ipAddr, port ) {
        mDone = false;
        send_data=input;
    }
    void startThread();
    void stopThread();
    bool isDone();
    Identity getIdentity() { return CLIENT; }

protected:
    void run();
    void setDone( const bool newVal );

private:
    static const unsigned int CONNECT_TIME_OUT = 5 * 1000; // 5 seconds
    bool mDone;
    QString send_data;
};


#endif // ECHOCLIENT_H
