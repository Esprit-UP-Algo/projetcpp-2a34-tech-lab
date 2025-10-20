#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

class Client
{
private:
    int id;
    QString nom;
    QString prenom;
    QString email;
    QString telephone;
    QString adresse;
    QDate dateNaissance;

public:
    Client();
    Client(int id, const QString& nom, const QString& prenom, const QString& email,
           const QString& telephone, const QString& adresse, const QDate& dateNaissance);

    // Getters
    int getId() const;
    QString getNom() const;
    QString getPrenom() const;
    QString getEmail() const;
    QString getTelephone() const;
    QString getAdresse() const;
    QDate getDateNaissance() const;

    // Setters
    void setId(int id);
    void setNom(const QString& nom);
    void setPrenom(const QString& prenom);
    void setEmail(const QString& email);
    void setTelephone(const QString& telephone);
    void setAdresse(const QString& adresse);
    void setDateNaissance(const QDate& dateNaissance);

    // CRUD Operations
    bool ajouter();
    bool supprimer(int id);
    bool modifier();
    static Client* getById(int id);
    static QList<Client*> getAll();

    // Validation methods
    bool isValidEmail() const;
    bool isValidTelephone() const;
};

#endif // CLIENT_H
