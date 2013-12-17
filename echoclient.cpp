#include "echoclient.h"



void EchoClient::setDone(const bool newVal)
{
    QMutexLocker lock( &mMutex );
    mDone = newVal;
}

bool EchoClient::isDone()
{
    QMutexLocker lock( &mMutex );
    return mDone;
}

/**
    Note that the QTcpSocket object must be in the run thread.  It cannot
    be a class variable.
*/
void EchoClient::run()
{
    QTcpSocket socket;
    QHostAddress hostAddr( mIP );
    socket.connectToHost( hostAddr, mPort );

    if (socket.waitForConnected( CONNECT_TIME_OUT )) {

        printf("Client connected\n");

        /*
         *Here, we must define the line, not as pulled from our constants, but from our main
         *window's text box. we must therefore get a reference to the main window to this point
         *However, the thread "run" method is called from the engine by start.
         *So there is no way to pass a reference directly to this method.
         *The class must hold the reference as a member.
         */

        QString line(mWin->textbox_contents);

        if (socket.state() == QAbstractSocket::ConnectedState){

            writeLine(&socket, line);

            // Response expectation removed for this example
            /*
            QString echoedLine = readLine( &socket );

            if (line != echoedLine) {
                printf("line and echoed line doesn't match\n");
            }
            else {
                printf("%s\n", line.toLocal8Bit().data() );
            }
            */
        }
    }
    else {
        printf("Client socket failed to connect\n");
    }

    setDone( true );
}


void EchoClient::startThread()
{
    setRunThread( true );
    start();
}

void EchoClient::stopThread()
{
}

