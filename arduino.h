#ifndef ARDUINO_H
#define ARDUINO_H
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
class Arduino : public QObject
{
    Q_OBJECT
private:
    QSerialPort *serial;
    QString portName;
public:
    Arduino(QObject *parent = nullptr);

    int connect_arduino();
    int disconnect_arduino();
    QString getPortName() const { return portName; }
signals:
    void dataReceived(QString);
};

#endif // ARDUINO_H
