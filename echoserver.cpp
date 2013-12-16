#include "echoserver.h"
#include "unistd.h"


void EchoServer::echoServer(QTcpSocket *client )
{
    QString line;
    do {
        line = readLine( client );

        if (line.length() > 0) {
            writeLine( client, line );
        }

    } while (line.length() > 0);
}


/**
  Note that Qt requires that the QTcpServer be in the same thread it is used in.
  So it cannot be declared as a class variable.  It must be in the run thread.
*/
void EchoServer::run()
{
    QHostAddress serverAddr( mIP );
    QTcpServer server;

    if (server.listen(serverAddr, mPort)) {
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
        printf("EchoServer::run: listen operation failed\n");
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
