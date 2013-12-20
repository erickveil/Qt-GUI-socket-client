#ifndef ECHOCLIENT_H
#define ECHOCLIENT_H

#include "QMutex"
#include "QThread"
#include "QTcpServer"
#include "QTcpSocket"
#include "QVector"
#include "QString"

/**
 * @brief The EchoClient class
 */
class EchoClient : public QObject
{
    Q_OBJECT

public:
    EchoClient(const QString &ipAddr, const ushort port,  QString input ){
        send_data=input;
        this->port=port;
        this->ip=ipAddr;
        runClient();
    }

signals:
    void socketResponse(QString resp);

protected:
    void runClient();
    QString readLine(QTcpSocket *socket );
    void writeLine( QTcpSocket *client, const QString &line );
    int waitForInput( QTcpSocket *socket );

private:
    static const unsigned int CONNECT_TIME_OUT = 5 * 1000; // 5 seconds
    QString send_data;
    QString ip;
    ushort port;
};


#endif // ECHOCLIENT_H
