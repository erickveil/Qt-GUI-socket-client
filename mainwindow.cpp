#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "echoclient.h"
#include "unistd.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bu_send_clicked()
{
    // place the data from the textbox into a public place so it can be used
    this->textbox_contents=this->ui->tb_msg->text();

    // fire off the client, which will depend on that data being accessible
    const QString IP = "127.0.0.3";
    const ushort port = 9999;

    EchoClient client(IP, port, this );
    client.startThread();

    while (! client.isDone()) {
        usleep( 100000 );
    }
}
