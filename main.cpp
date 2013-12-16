#include "mainwindow.h"
#include <QApplication>
#include "echoserver.h"
#include "echoclient.h"
#include "unistd.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    // Moving this off to a slot

    //const QString IP =     "127.0.0.3";
    //const ushort port = 9999;

    //EchoServer server(IP, port );
    //EchoClient client(IP, port );

    //server.startThread();
    //client.startThread();

    //while (! client.isDone()) {
    //    usleep( 100000 );
    //}



    return a.exec();
}
