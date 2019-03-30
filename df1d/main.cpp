#include "Df1.h"
#include "Df1Serial.h"

#include <QApplication>
#include <QtWebSockets/qwebsocket.h>
#include <QtWebSockets/qwebsocketserver.h>


#include <QMutex>

#include <qmdnsengine/server.h>
#include <qmdnsengine/service.h>
#include <qmdnsengine/hostname.h>
#include <qmdnsengine/provider.h>


class Df1ServiceAdvertiser : public QObject {

	private:
		QMdnsEngine::Server m_server;
		QMdnsEngine::Hostname m_hostname;
		QMdnsEngine::Provider *m_provider;


	public:
		Df1ServiceAdvertiser(QString name,quint16 port,QObject *parent = nullptr) : 
			QObject(parent),
			m_server(),
			m_hostname(&m_server),
			m_provider(nullptr)
		{
			QMdnsEngine::Service service;
			service.setName(name.toUtf8());
			service.setType("_test._tcp._local.");
			service.setPort(port);
			m_provider = new QMdnsEngine::Provider(&m_server,&m_hostname,this);
			m_provider->update(service);
		}
};


class Df1Socket : public QObject {

	public:
		Df1Socket(quint16 port,QString comName = "ttyUSB0",QObject *parent=nullptr) :
			QObject(parent),
			m_server(new QWebSocketServer(QStringLiteral("Df1 Server"),QWebSocketServer::NonSecureMode,this))
		{
			//m_slaveserial = new SlaveSerial(parent);
			initialize(comName.toStdString().c_str());
			if(m_server->listen(QHostAddress::Any,port)) {
				qDebug() << "Df1 Server listening on port " << port;

				connect(m_server,&QWebSocketServer::newConnection,this,&Df1Socket::onNewConnection);
				connect(m_server,&QWebSocketServer::closed,this,&Df1Socket::closed);
			}

			advertiser = new Df1ServiceAdvertiser("Df1 Service",port,parent);
		}

	private:
		QWebSocketServer *m_server;
		QList<QWebSocket*> m_clients;

		SlaveSerial* m_slaveserial;
		Df1ServiceAdvertiser* advertiser;

		QMutex m_mutexSerial;


	Q_SIGNALS:
		void closed() {
			qDebug() << "Closing shop";
		}

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
			QWebSocket *client = qobject_cast<QWebSocket*>(sender());

			char* response = new char[255];

			client->sendTextMessage("Sending your message "+message);

			m_mutexSerial.lock();
			client->sendTextMessage("Got mutex");
			int ret = read_socket(message.toStdString().c_str(),response);
			if(ret) {
				client->sendTextMessage(response);
			} else {
				client->sendTextMessage("Error ");
			}
			
			m_mutexSerial.unlock();
			delete response;

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
	QApplication app(argc,argv);
	quint16 port = 4500;
	Df1Socket socket(port);

	return app.exec();
}
