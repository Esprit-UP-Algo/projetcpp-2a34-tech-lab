#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class Arduino : public QObject
{
    Q_OBJECT
public:
    explicit Arduino(QObject *parent = nullptr);
    int connect_arduino();
    int disconnect_arduino();
    QString getPortName() const { return portName; }

signals:
    void dataReceived(QString data);

private:
    QSerialPort *serial;
    QString portName;
};

#endif // ARDUINO_H
