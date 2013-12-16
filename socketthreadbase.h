/**
  * Make sure to add
  * QT += network
  * to the *.pro file
  */

#ifndef SOCKETTHREADBASE_H
#define SOCKETTHREADBASE_H
#include "QMutex"
#include "QThread"
#include "QVector"
#include "QString"

#include <QTcpSocket>
#include <QTcpServer>
#include <QAbstractSocket>




class SocketThreadBase {

public:
    SocketThreadBase(const QString &ipAddr, const ushort port ) : mIP( ipAddr ), mPort( port )
    {
        mRunThread = false;
    }
    enum Identity {
        BAD_IDENTITY,
        SERVER,
        CLIENT
    };
    virtual void startThread() = 0;
    virtual void stopThread() = 0;
    virtual Identity getIdentity() = 0;

protected:
    QMutex mMutex;
    const QString mIP;
    const ushort mPort;

    void setRunThread( bool newVal );
    bool getRunThread();
    void run();
    QString readLine(QTcpSocket *socket );
    int waitForInput( QTcpSocket *socket );
    void writeLine( QTcpSocket *client, const QString &line );

private:
    bool mRunThread;
};

#endif // SOCKETTHREADBASE_H
