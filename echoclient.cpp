#include "echoclient.h"


/**
 * @brief EchoClient::runClient
 *Sends the message and receives a response, which it emits in a signal.
 */
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

/**
 * @brief EchoClient::writeLine
 * @param socket
 * @param line
 *Writes the line to the socket with error reporting.
 */
void EchoClient::writeLine(QTcpSocket *socket, const QString &line)
{
    if (line.length() > 0) {
        socket->write( line.toLocal8Bit() );

        if (! socket->waitForBytesWritten()) {
            printf("%s: writeLine: the write to the socket failed\n", __PRETTY_FUNCTION__);
        }
    }
}

/**
 * @brief EchoClient::readLine
 * @param socket
 * @return
 *Retrieves the ack from the socket
 */
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

/**
 * @brief EchoClient::waitForInput
 * @param socket
 * @return
 * Blocks from the moment of connection until something comes back.
 *Or time out. There's that.
 */
int EchoClient::waitForInput( QTcpSocket *socket )
{
    int bytesAvail = -1;

    if (socket->waitForReadyRead( 50000 )) {
        bytesAvail = socket->bytesAvailable();
    }

    return bytesAvail;
}


void EchoClient::startClientThread()
{
    runClient();
}

