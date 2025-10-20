#ifndef ADHERENT_H
#define ADHERENT_H

#include <QString>
#include <QSqlQueryModel>

class Adherent
{
private:
    int id_adherent;
    QString nom;
    QString prenom;
    QString date_naissance;
    QString email;
    QString telephone;
    QString adresse;

public:

    Adherent();
    Adherent(int, QString, QString, QString, QString, QString, QString);
    int getId() const;
    QString getNom() const;
    QString getPrenom() const;
    QString getDateNaissance() const;
    QString getEmail() const;
    QString getTelephone() const;
    QString getAdresse() const;

    void setId(int);
    void setNom(QString);
    void setPrenom(QString);
    void setDateNaissance(QString);
    void setEmail(QString);
    void setTelephone(QString);
    void setAdresse(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool modifier(int);
    bool supprimer(int);
};

#endif // ADHERENT_H
