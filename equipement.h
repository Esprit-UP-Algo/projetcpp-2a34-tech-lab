#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QRegularExpression>

class Equipement
{
private:
    int reference;
    QString nom;
    int quantite;
    QString categorie;
    double prix;

public:
    Equipement();
    Equipement(int reference, QString nom, int quantite, QString categorie, double prix);

    int getReference() const;
    QString getNom() const;
    int getQuantite() const;
    QString getCategorie() const;
    double getPrix() const;

    bool setReference(int reference);
    bool setNom(QString nom);
    bool setQuantite(int quantite);
    bool setCategorie(QString categorie);
    bool setPrix(double prix);


    static bool referenceExiste(int reference);
    static bool quantiteValide(int quantite);
    static bool prixValide(double prix);
    static bool nomValide(const QString &nom);

    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* trier(const QString &critere, const QString &ordre);
    QSqlQueryModel* rechercher(const QString &critere, const QString &valeur);
    bool supprimer(int reference);
    bool modifier();
    QMap<QString, double> statistiques(QString critere);
};

#endif // EQUIPEMENT_H
