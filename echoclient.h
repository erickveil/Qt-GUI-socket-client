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
    EchoClient(const QString &ipAddr, const ushort port, const MainWindow* win ) : SocketThreadBase( ipAddr, port ) {
        mDone = false;
        mWin = win;
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
    const MainWindow* mWin;
};


#endif // ECHOCLIENT_H
