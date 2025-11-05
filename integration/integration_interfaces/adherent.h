#ifndef ADHERENT_H
#define ADHERENT_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QRegularExpression>

class Adherent
{
private:
    int id;
    QString nom;
    QString prenom;
    QDate daten;
    QString email;
    QString tel;
    QString adr;

public:
    Adherent();
    Adherent(int id, QString nom, QString prenom, QDate daten,
             QString email, QString tel, QString adr);

    int getId() const;
    QString getNom() const;
    QString getPrenom() const;
    QDate getDateN() const;
    QString getEmail() const;
    QString getTel() const;
    QString getAdr() const;

    bool setId(int id);
    bool setNom(QString nom);
    bool setPrenom(QString prenom);
    bool setDateN(QDate daten);
    bool setEmail(QString email);
    bool setTel(QString tel);
    void setAdr(QString adr);

    static bool emailValide(const QString &email);
    static bool telValide(const QString &tel);
//controle de la unicite
    static bool idExiste(int id);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
   bool modifier();
};

#endif // ADHERENT_H
