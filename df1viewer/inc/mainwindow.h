#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QStringListModel>

#include "df1client.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow {

    public:
        explicit MainWindow(QWidget *parent = nullptr);

    private:
        Ui::MainWindow* ui;

        Df1Client *client;

        QStringListModel *modelTarget;
        QStringListModel *modelReturns;


    private slots:
        // Quand l'usager veut ce connecter a une nouvelle target
        void connectNewTarget();
        // Quand la connection avec l'usager est faite 
        void connectionNewTargetConfirm();
        // Quand le websocket que je suis connecter ce deconnecte
        void disconnectFromTarget();
        // Quand l'usager veut envoyer une commande a la target
        void sendCmdTarget();
        // Quand on recoit un message depuis la target
        void onReceivedFromTarget();

};


#endif