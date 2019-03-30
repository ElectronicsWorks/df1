#include "Df1.h"
#include "Df1Serial.h"

#include <QApplication>
#include <QtWebSockets/qwebsocket.h>
#include <QtWebSockets/qwebsocketserver.h>

class Df1Socket : public QObject {

	public:
		Df1Socket(quint16 port,QString comName = "ttyUSB0",QObject *parent=nullptr) :
			QObject(parent),
			m_server(new QWebSocketServer(QStringLiteral("Df1 Server"),QWebSocketServer::NonSecureMode,this))
		{
			m_slaveserial = new SlaveSerial(parent);
			//m_slaveserial.startSerial(comName);
			if(m_server->listen(QHostAddress::Any,port)) {
				qDebug() << "Df1 Server listening on port " << port;

				connect(m_server,&QWebSocketServer::newConnection,this,&Df1Socket::onNewConnection);
				connect(m_server,&QWebSocketServer::closed,this,&Df1Socket::closed);
			}
		}

	private:
		QWebSocketServer *m_server;
		QList<QWebSocket*> m_clients;
		SlaveSerial* m_slaveserial;


	Q_SIGNALS:
		void closed();

	private Q_SLOTS:
		void onNewConnection() {
			QWebSocket *socket = m_server->nextPendingConnection();

			connect(socket,&QWebSocket::textMessageReceived,this,&Df1Socket::processTextMessage);
			connect(socket,&QWebSocket::binaryMessageReceived,this,&Df1Socket::processBinaryMessage);
			connect(socket,&QWebSocket::disconnected,this,&Df1Socket::socketDisconnected);

			qDebug() << "New connection from ";

			m_clients << socket;
		}
		void processTextMessage(QString message) {

			m_slaveserial->executeCommand(message);

		}
		void processBinaryMessage(QByteArray message) {
			QWebSocket *client = qobject_cast<QWebSocket*>(sender());
			qDebug() << "Binary message received";
			client->sendBinaryMessage(QByteArray::fromStdString("DDD"));

		}
		void socketDisconnected() {
			QWebSocket *client = qobject_cast<QWebSocket*>(sender());
			qDebug() << "socketDisconnected " << client;
			if(client) {
				m_clients.removeAll(client);
				client->deleteLater();
			}
		}

};



extern word tns;
int file;

int main(int argc, char* argv[]) {
	//QApplication app(argc,argv);
	//return app.exec()
	char* respo = new char[255];
	char* msg = "N7:0=7";
	char* msg2 = "N7:0";

	int ret = read_socket(msg,respo);

	printf("Return %d %s\n",ret,respo);



}
