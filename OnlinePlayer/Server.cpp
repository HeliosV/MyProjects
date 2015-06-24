#include "Server.h"
#include <iostream>
#include "MainWnd.h"
#include <QTcpServer>
#include <QtNetwork>
#include <QMessageBox>
#include <QWebFrame>
#include <QWebElement>


Server::Server(MainWindow &w) : widget(w)
{
    server_status = 0;
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newuser()));
    if (!tcpServer->listen(QHostAddress::Any, 33333) && server_status==0) {
        qDebug() << QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
    } else {
        server_status=1;
        qDebug() << "Server starts";
    }
    
}


void Server::newuser()
{
    if(server_status==1){
        qDebug() << "You have new connection";
        QTcpSocket* clientSocket = tcpServer->nextPendingConnection();
        int idusersocs = clientSocket->socketDescriptor();
        SClients[idusersocs]=clientSocket;
        connect(SClients[idusersocs],SIGNAL(readyRead()), this, SLOT(readClient()));
        connect(SClients[idusersocs],SIGNAL(readyRead()), this, SLOT(readAnswer()));
    }
    
}


void Server::readAnswer()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    QByteArray data = clientSocket->readAll();
    //QString text(data);
    clientSocket->write(data);
    //qDebug() << text;
}


void Server::stopServ()
{
    if(server_status==1){
        foreach(int i,SClients.keys()){
            QTextStream os(SClients[i]);
            os.setAutoDetectUnicode(true);
            os << QDateTime::currentDateTime().toString() << "\n";
            SClients[i]->close();
            SClients.remove(i);
        }
        tcpServer->close();
        qDebug() << "Server stopped";
        server_status=0;
    }
}


void Server::readClient()
{
    
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    QNetworkReply* reply = (QNetworkReply*)sender();
    QString html;
    html = "<html>";
    html.append("<head>");
    html.append("</head>");
    html.append("<body>");
    html.append("<form action=127.0.0.1 method=POST>");
    html.append("<p>");
    html.append("<input name=btn_play type=submit id=1 value=play>");
    html.append("<input name=btn_pause type=submit id=2 value=pause>");
    html.append("<input name=btn_next type=submit id=3 value=next>");
    html.append("<input name=btn_prev type=submit id=4 value=prev>");
    html.append("<input name=btn_stop type=submit id=5 value=stop>");
    html.append("</p>");
    html.append("</form>");
    html.append("</body>");
    html.append("</html>");
    
    int idusersocs=clientSocket->socketDescriptor();
    QTextStream os(clientSocket);
    os.setAutoDetectUnicode(true);
    os << "HTTP/1.1 200 OK\r\n"
          "Content-Type: text/html; charset=\"utf-8\"\r\n"
          "\r\n"
       << html << "\n";
    QList<QString> content;
//    QString current = "->";
    int current_index = widget.tableWidget->currentRow();
    for(int i = 0; i < widget.tableWidget->count(); i++)
    {
        widget.f1 = widget.fileName.at(i);
        QFileInfo fi(widget.f1);
        content.push_back(fi.fileName());
        if (i == current_index + 1)
            os << "<p style=color:red>" << content.at(i) << "</p>";
        else
            os << "<p>" << content.at(i) << "</p>";
    }



    QByteArray data = reply->readAll();
    QString str(data);

    if (str.contains("btn_play=play"))
        widget.player->play();
    else if (str.contains("btn_stop=stop"))
        widget.player->stop();
    else if (str.contains("btn_pause=pause"))
        widget.player->pause();
    else if (str.contains("btn_next=next"))
        widget.next();
    else if (str.contains("btn_prev=prev"))
        widget.previous();

    clientSocket->close();
    
    SClients.remove(idusersocs);
}


void Server::serviceRequestFinished(QNetworkReply *reply)
{
    reply->deleteLater();
    
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        QString text(data);
        //qDebug() << text;
    }
    else
    {
        return;
    }
}






