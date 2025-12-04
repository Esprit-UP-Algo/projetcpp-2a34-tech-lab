#include "arduino.h"

Arduino::Arduino(QObject *parent) : QObject(parent)
{
    serial = new QSerialPort(this);
}
int Arduino::connect_arduino()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if (info.vendorIdentifier() != 0 && info.productIdentifier() != 0) {
            portName = info.portName();
        }
    }
    if (portName.isEmpty())
        return -1;
    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud9600);
    if (!serial->open(QIODevice::ReadWrite))
        return -2;
    connect(serial, &QSerialPort::readyRead, this, [this]() {
        QString data = serial->readAll();
        emit dataReceived(data.trimmed());
    });
    return 1;
}

int Arduino::disconnect_arduino()
{
    if (serial->isOpen()) {
        serial->close();
        return 1;
    }
    return 0;
}
