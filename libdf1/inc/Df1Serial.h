#ifndef DF1SERIAL_H
#define DF1SERIAL_H

#include <QSerialPort>
#include <QSerialPortInfo>



inline std::vector<QString> getAvailablePorts() {
    const auto infos  = QSerialPortInfo::availablePorts();
    std::vector<QString> items;
    for(const QSerialPortInfo &info : infos) {
        items.push_back(info.portName());
    }
    return items;
}


#endif // !DF1SERIAL_H

