#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QDialog>
#include <QNetworkReply>
#include "MainWnd.h"

class MainWindow;

class Server : public QDialog
{
    Q_OBJECT

public: 
    Server(MainWindow& w);
    ~Server(){}

private slots:
    void newuser();
    void stopServ();
    void readClient();
    void readAnswer();
    void serviceRequestFinished(QNetworkReply* reply);



private:
    QTcpServer *tcpServer;
    int server_status;
    QMap<int,QTcpSocket *> SClients;
    QString str;
    //MainWindow *w;
    MainWindow& widget;

};

#endif // SERVER_H
