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
    EchoClient(const QString &ipAddr, const ushort port, MainWindow* win ) : SocketThreadBase( ipAddr, port ) {
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
    static const char *mStrings[];
    static const uint mNumStrings;
    bool mDone;
    MainWindow* mWin;
};


#endif // ECHOCLIENT_H
