#ifndef DF1CLIENT_H
#define DF1CLIENT_H

#include <QObject>
#include <QtWebSockets/qwebsocket.h>

class Df1Client : public QObject {
    Q_OBJECT

    public:
        explicit Df1Client(const QUrl &url, QObject *parent = nullptr);

        void SendCommand(QString cmd);

        const QString GetTargetURL();

    Q_SIGNALS:
        void closed();
        void connected();
    
    private Q_SLOTS:
        void onConnected();
        void onTextMessageReceived(QString message);
    
    private:
        QWebSocket m_socket;
        QUrl m_url;
};


#endif