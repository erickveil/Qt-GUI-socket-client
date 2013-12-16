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

        QHostAddress hostAddr = socket.localAddress();
        QString addr = "";

        if (hostAddr != QHostAddress::Null) {
            addr = hostAddr.toString();
        }

        printf("Client connected");

        if (addr.length() > 0) {
            // Changed from ASCII conversion and fixed typo on token
            printf(" on address %s:%d", addr.toLocal8Bit().data(), socket.localPort() );
        }

        printf("\n");
        int ix = 0;

        /*
         *Here, we must define the line, not as pulled from our constants, but from our main
         *window's text box. we must therefore get a reference to the main window to this point
         */

        while (
               (socket.state() == QAbstractSocket::ConnectedState) &&
               (ix < mNumStrings)
               ) {
            QString line( mStrings[ix] );
            writeLine(&socket, line);
            QString echoedLine = readLine( &socket );

            if (echoedLine.length() > 0) {

                if (line != echoedLine) {
                    printf("line and echoed line doesn't match\n");
                }
                else {
                    printf("%s\n", line.toLocal8Bit().data() );
                }

            }
            ix++;
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


const char *EchoClient::mStrings[] = {
  "    'Twas brillig, and the slithy toves\r",
  "        Did gyre and gimble in the wabe:\r",
  "    All mimsy were the borogoves,\r",
  "        And the mome raths outgrabe.\r",
  " \r",
  "    \"Beware the Jabberwock, my son!\r",
  "        The jaws that bite, the claws that catch!\r",
  "    Beware the Jubjub bird, and shun\r",
  "        The frumious Bandersnatch!\"\r",
  " \r",
  "    He took his vorpal sword in hand: \r",
  "        Long time the manxome foe he sought--\r",
  "    So rested he by the Tumtum tree, \r",
  "        And stood awhile in thought. \r",
  " \r",
  "    And, as in uffish thought he stood,\r",
  "        The Jabberwock, with eyes of flame,\r",
  "    Came whiffling through the tulgey wood,\r",
  "        And burbled as it came!\r",
  " \r",
  "    One, two!  One, two!  And through and through\r",
  "        The vorpal blade went snicker-snack!\r",
  "    He left it dead, and with its head\r",
  "        He went galumphing back. \r",
  " \r",
  "    \"And hast thou slain the Jabberwock?\r",
  "        Come to my arm, my beamish boy!\r",
  "    O frabjous day! Callooh!  Callay!\"\r",
  "        He chortled in his joy.\r",
  " \r",
  "    'Twas brillig, and the slithy toves\r",
  "        Did gyre and gimble in the wabe:\r",
  "    All mimsy were the borogoves, \r",
    "        And the mome raths outgrabe\r"
};

const uint EchoClient::mNumStrings = sizeof EchoClient::mStrings / sizeof( *EchoClient::mStrings );
