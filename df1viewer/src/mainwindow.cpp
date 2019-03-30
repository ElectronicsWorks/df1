#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : 
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    client(nullptr)
{
    ui->setupUi(this);
    ui->txtAddr->setText("ws://127.0.0.1:4500");


    ui->listReturn->insertItem(0,"DDDD");

    connect(ui->btnConnect,&QPushButton::pressed,this,&MainWindow::connectNewTarget);
    connect(ui->btnDisconnect,&QPushButton::pressed,this,&MainWindow::disconnectFromTarget);
    connect(ui->btnEnvoyer,&QPushButton::pressed, this, &MainWindow::sendCmdTarget);

}


void MainWindow::connectNewTarget() {
    const QString addr = ui->txtAddr->text();
    if(addr.isNull() || addr.isEmpty()) {
        qDebug() << "Bad addr " << addr;
        return;
    }
    disconnectFromTarget();
    client = new Df1Client(QUrl(addr),this);

    connect(client,&Df1Client::connected,this,&MainWindow::connectionNewTargetConfirm);
}

void MainWindow::connectionNewTargetConfirm() {
    qDebug() << "Your connected bro dog";
    ui->gbDf1->setEnabled(true);
    ui->lblDf1Name->setText(client->GetTargetURL());
}

void MainWindow::disconnectFromTarget() {
    qDebug() << "Disconnected from target gros big";
    if(client) {
        client->disconnect();
        delete client;
    }
    ui->gbDf1->setEnabled(false);
}

void MainWindow::sendCmdTarget() {

}

void MainWindow::onReceivedFromTarget() {

}