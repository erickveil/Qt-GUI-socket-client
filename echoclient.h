#ifndef ECHOCLIENT_H
#define ECHOCLIENT_H

#include "QMutex"
#include "QThread"
#include "QTcpServer"
#include "QTcpSocket"
#include "QVector"
#include "QString"
#include "socketthreadbase.h"

/**
 * @brief The EchoClient class
 *
 * You will notice the unfortunate case of multiple inheritance here.
 * The reason is that both client and listener make use of
 * 1. The Qt Thread library
 * 2. The common components of the custom base class
 * I made an attempt to create an inheritance chain of
 * QThread->SocketThreadBase->EchoClient
 * And the result was the mutex locks freezing the application.
 *
 * Attempt to localize the base thread functionality in either the client or server class
 * results in duplicate code.
 *
 * It appears, that multiple inheritance is unavoidable in this scenario.
 * Thanks, C++.
 */
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
