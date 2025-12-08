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
    ~Arduino();

    // Tentative de connexion :
    // si portName vide -> on tente de détecter via VID/PID
    // sinon on force l'ouverture du port (ex: "COM5")
    int connect_arduino(const QString &portName = QString());
    int disconnect_arduino();

    bool isConnected() const;

    // Envoi de commande simple (ajoute '\n' automatiquement)
    void envoyerCommande(const QString &commande);
    void activerAlerte();   // envoie "ALERTE:ON"
    void desactiverAlerte(); // envoie "ALERTE:OFF"

    QSerialPort* getSerial() const { return serial; }
    QString getPortName() const { return currentPortName; }

signals:
    void dataReceived(const QString &line);    // toute ligne brute non vide
    void distanceMeasured(int distanceCm);     // quand on reçoit "DISTANCE:NN"
    void erreurConnexion(const QString &message);
    void etatConnecte(bool ok);

private slots:
    void handleReadyRead();

private:
    QSerialPort *serial;
    QString currentPortName;
    QString rxBuffer;

    // Defaults pour Arduino Uno — peut être modifié si besoin
    static const quint16 arduino_uno_vendor_id;
    static const quint16 arduino_uno_product_id;
};

#endif // ARDUINO_H
