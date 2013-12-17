#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "echoclient.h"
#include "unistd.h"
#include <QMessageBox>

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
    QString textbox_contents=this->ui->tb_msg->text();

    bool ok;
    const QString IP = this->ui->tb_ip->text();
    const ushort port = this->ui->tb_port->text().toUShort(&ok);

    if (!ok)
    {
        QMessageBox msgBox;
        msgBox.setText("The port is not valid.");
        msgBox.exec();
        return;
    }

    EchoClient client(IP, port, textbox_contents );
    client.startThread();

    while (! client.isDone()) {
        usleep( 100000 );
    }
}
