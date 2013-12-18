#include "echoserver.h"
#include "unistd.h"

/**
 * @brief EchoServer::echoServer
 * @param client
 * Removed the loop, do not see a reason for it.
 */
void EchoServer::echoServer(QTcpSocket *client )
{
    QString line;
        line = readLine( client );
        emit receivedLine(line);

        if (line.length() > 0) {
            writeLine( client, line );
        }
}


/**
  Note that Qt requires that the QTcpServer be in the same thread it is used in.
  So it cannot be declared as a class variable.  It must be in the run thread.

  Removed the ip reference and replaces with any QHostAddress connection.
*/
void EchoServer::run()
{
    QTcpServer server;

    if (server.listen(QHostAddress::Any, mPort)) {
        printf("EchoServer::run: listen() succeeded\n");
        while (server.isListening() && getRunThread()) {

            if (server.waitForNewConnection(100)) {
                printf("EchoServer::run: got a TCP connection\n");
                QTcpSocket *client = server.nextPendingConnection();
                echoServer( client );

            }
            else {
                usleep( 100000 );
            }
        }
    }
    else {
        printf("EchoServer::run: listen operation failed\nport:%d\n",mPort);

    }
}

void EchoServer::startThread()
{
    setRunThread( true );
    start();
}

void EchoServer::stopThread()
{
    setRunThread( false );
}

