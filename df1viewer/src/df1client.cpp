#include "df1client.h"


Df1Client::Df1Client(const QUrl &url,QObject *parent) :
    QObject(parent) {

    connect(&m_socket,&QWebSocket::connected,this,&Df1Client::onConnected);
    connect(&m_socket,&QWebSocket::disconnected, this,&Df1Client::closed);

    m_socket.open(QUrl(url));

}

const QString Df1Client::GetTargetURL() {
    return m_socket.peerAddress().toString();
}

void Df1Client::SendCommand(QString cmd) {
    m_socket.sendTextMessage(cmd);
}


void Df1Client::onConnected() {
    qDebug() << "Connected to target";
    connect(&m_socket,&QWebSocket::textMessageReceived,this,&Df1Client::onTextMessageReceived);
    this->connected();
}

void Df1Client::onTextMessageReceived(QString message) {

}