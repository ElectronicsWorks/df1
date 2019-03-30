#include "Df1.h"
#include "Df1Serial.h"


word tns;

void SlaveSerial::error(const QString &s) {
    throw s;
}

void SlaveSerial::timeout(const QString &s) {

}

void SlaveSerial::startSerial(const QString &name) {
    this->m_portName = name;
    this->m_quit = true;
}

void SlaveSerial::executeCommand(const QString &cmd) {
    char* str = new char[255];
    int returnRead = read_socket(cmd.toStdString().c_str(),str);
    printf("Return %d %s\n",returnRead,str);
}

void SlaveSerial::run() {
    printf("RUNNN\n");
    QSerialPort port;
    port.setPortName(m_portName);
    port.setBaudRate(2400);
    port.setStopBits(QSerialPort::StopBits::OneStop);
    if(!port.open(QIODevice::ReadWrite)) {
        emit error(tr("Cant open %1, error code %2").arg(m_portName).arg(port.error()));
        return;
    }

    while(m_quit) {
        if(port.waitForReadyRead()) {
            QByteArray requestData = port.readAll();
            while(port.waitForReadyRead(10))
                requestData += port.readAll();
            printf("END READ\n");
        } else {
            printf("Cant read shit\n");
        }
    }

    port.close();

}


