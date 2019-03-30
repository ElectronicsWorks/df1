#ifndef DF1SERIAL_H
#define DF1SERIAL_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QThread>



inline std::vector<QString> getAvailablePorts() {
    const auto infos  = QSerialPortInfo::availablePorts();
    std::vector<QString> items;
    for(const QSerialPortInfo &info : infos) {
        items.push_back(info.portName());
    }
    return items;
}

class SlaveSerial : public QThread
{

    public:
        explicit SlaveSerial(QObject *parent = nullptr) {

        }
        virtual ~SlaveSerial() {};
        void startSerial(const QString &name);


        void executeCommand(const QString &cmd);

    Q_SIGNALS:
        void request(const QString &s);
        void error(const QString &s);
        void timeout(const QString &s);


        void commandResult(const QString &s);

    private:
        void run() override;

        QString m_portName;
        QString m_response;
        int m_waitTimeout = 0;
        bool m_quit = false;
};


#endif // !DF1SERIAL_H

