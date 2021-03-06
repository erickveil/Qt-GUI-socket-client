#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "echoclient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    EchoClient *managed_client;
    QThread *client_thread;

private slots:
    void on_bu_send_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
