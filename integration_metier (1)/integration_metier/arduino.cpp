#include "arduino.h"
#include <QDebug>

const quint16 Arduino::arduino_uno_vendor_id = 9025;  // 0x2341
const quint16 Arduino::arduino_uno_product_id = 67;

Arduino::Arduino(QObject *parent)
    : QObject(parent),
    serial(new QSerialPort(this))
{
    // 🔧 CONNECT pour recevoir les données du port série
    connect(serial, &QSerialPort::readyRead, this, &Arduino::handleReadyRead);
}

Arduino::~Arduino()
{
    disconnect_arduino();
    delete serial;
}

int Arduino::connect_arduino(const QString &portName)
{
    currentPortName.clear();

    if (!portName.isEmpty()) {
        currentPortName = portName;
    } else {
        const auto ports = QSerialPortInfo::availablePorts();
        for (const QSerialPortInfo &info : ports) {
            if (info.hasVendorIdentifier() && info.hasProductIdentifier()) {
                if (info.vendorIdentifier() == arduino_uno_vendor_id &&
                    info.productIdentifier() == arduino_uno_product_id) {
                    currentPortName = info.portName();
                    break;
                }
            }
        }
    }

    if (currentPortName.isEmpty()) {
        emit erreurConnexion("Aucun port Arduino détecté");
        return -1;
    }

    if (serial->isOpen())
        serial->close();

    serial->setPortName(currentPortName);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (!serial->open(QIODevice::ReadWrite)) {
        emit erreurConnexion("Impossible d'ouvrir le port " + currentPortName + " : " + serial->errorString());
        return -2;
    }

    return 0;
}

int Arduino::disconnect_arduino()
{
    if (serial->isOpen()) {
        desactiverAlerte();
        serial->close();
        return 1;
    }
    return 0;
}

void Arduino::envoyerCommande(const QString &commande)
{
    if (serial->isOpen() && serial->isWritable()) {
        QByteArray data = (commande + '\n').toUtf8();
        qint64 bytesWritten = serial->write(data);

        if (bytesWritten == -1) {
            emit erreurConnexion("Erreur d'écriture sur le port série: " + serial->errorString());
        } else if (bytesWritten != data.size()) {
            emit erreurConnexion("Écriture partielle sur le port série");
        }
    } else {
        emit erreurConnexion("Le port série n'est pas ouvert en écriture");
    }
}

void Arduino::activerAlerte()
{
    envoyerCommande("ALERTE:ON");
}

void Arduino::desactiverAlerte()
{
    envoyerCommande("ALERTE:OFF");
}

// 🔧 SLOT **AJOUTÉ**
void Arduino::handleReadyRead()
{
    rxBuffer.append(serial->readAll());

    int endIndex;
    while ((endIndex = rxBuffer.indexOf('\n')) != -1)
    {
        QString line = rxBuffer.left(endIndex).trimmed();
        rxBuffer.remove(0, endIndex + 1);

        if (line.isEmpty())
            continue;

        emit dataReceived(line);

        // --- Gestion du capteur ---
        if (line == "suffisant") {
            emit distanceMeasured(0);   // 0 = suffisant
        }
        else if (line == "insuffisant") {
            emit distanceMeasured(1);   // 1 = insuffisant
        }
        else if (line == "ERROR_SENSOR") {
            emit erreurConnexion("Capteur HC-SR04 non détecté !");
        }
    }
}
