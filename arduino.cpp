#include "arduino.h"
#include <QDebug>

Arduino::Arduino(QObject *parent) : QObject(parent)
{
    serial = new QSerialPort(this);
}

int Arduino::connect_arduino()
{
    qDebug() << "=== LISTE DES PORTS DISPONIBLES ===";
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Port:" << info.portName()
        << "| Vendor:" << info.vendorIdentifier()
        << "| Product:" << info.productIdentifier()
        << "| Description:" << info.description();
    }
    qDebug() << "====================================";

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if (info.vendorIdentifier() != 0 && info.productIdentifier() != 0) {
            portName = info.portName();
        }
    }

    qDebug() << "Port choisi pour connexion:" << portName;

    if (portName.isEmpty())
        return -1;

    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud9600);

    if (!serial->open(QIODevice::ReadWrite)) {
        qDebug() << "❌ Erreur ouverture port:" << serial->errorString();
        return -2;
    }

    connect(serial, &QSerialPort::readyRead, this, [this]() {
        QByteArray raw = serial->readAll();
        qDebug() << "[RAW SERIAL]:" << raw;

        QString data = QString(raw).trimmed();
        qDebug() << "[TRIMMED]:" << data;

        if (!data.isEmpty())
            emit dataReceived(data);
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
