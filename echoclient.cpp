#include "echoclient.h"



void EchoClient::runClient()
{
    QTcpSocket socket;
    QHostAddress hostAddr( ip );
    socket.connectToHost( hostAddr, port );

    if (socket.waitForConnected( CONNECT_TIME_OUT )) {

        printf("%s: Client connected\n", __PRETTY_FUNCTION__);

        QString line(send_data);

        if (socket.state() == QAbstractSocket::ConnectedState){

            writeLine(&socket, line);
            QString echoedLine = readLine( &socket );
            printf("%s: sent line:%s\n", __PRETTY_FUNCTION__, line.toLocal8Bit().data() );
            emit socketResponse(echoedLine);
        }
    }
    else {
        printf("%s: Client socket failed to connect\n", __PRETTY_FUNCTION__);
    }
}

void EchoClient::writeLine(QTcpSocket *socket, const QString &line)
{
    if (line.length() > 0) {
        socket->write( line.toLocal8Bit() );

        if (! socket->waitForBytesWritten()) {
            printf("%s: writeLine: the write to the socket failed\n", __PRETTY_FUNCTION__);
        }
    }
}

QString EchoClient::readLine(QTcpSocket *socket )
{
    QString line = "";
    int bytesAvail = waitForInput( socket );

    if (bytesAvail > 0) {
        int cnt = 0;
        bool endOfLine = false;
        bool endOfStream = false;

        while (cnt < bytesAvail && (!endOfLine) && (!endOfStream)) {
            char ch;
            int bytesRead = socket->read(&ch, sizeof(ch));

            if (bytesRead == sizeof(ch)) {
                cnt++;
                line.append( ch );
                if (ch == '\r') {
                    endOfLine = true;
                }
            }
            else {
                endOfStream = true;
            }
        }
    }
    return line;
}

int EchoClient::waitForInput( QTcpSocket *socket )
{
    int bytesAvail = -1;

    if (socket->waitForReadyRead( 100 )) {
        bytesAvail = socket->bytesAvailable();
    }

    return bytesAvail;
}

