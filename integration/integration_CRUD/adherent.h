#ifndef ADHERENT_H
#define ADHERENT_H
#include "personne.h"
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QRegularExpression>

class Adherent : public personne
{
    //herite personne ou nzid aaliha el attribut daten
private:
    QDate daten;

public:
    Adherent();
    Adherent(int id, QString nom, QString prenom, QDate daten,
             QString email, QString tel, QString adr);

//attributs el zayed date de naissance
    QDate getDateN() const;
    bool setDateN(QDate daten);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
   bool modifier();
};

#endif // ADHERENT_H
