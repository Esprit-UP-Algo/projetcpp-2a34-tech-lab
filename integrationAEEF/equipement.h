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

    // Getters
    int getReference() const;
    QString getNom() const;
    int getQuantite() const;
    QString getCategorie() const;
    double getPrix() const;

    // Setters avec validation
    bool setReference(int reference);
    bool setNom(QString nom);
    bool setQuantite(int quantite);
    bool setCategorie(QString categorie);
    bool setPrix(double prix);

    // Méthodes de validation
    static bool referenceExiste(int reference);
    static bool quantiteValide(int quantite);
    static bool prixValide(double prix);
    static bool nomValide(const QString &nom);

    // Méthodes CRUD
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* trier(const QString &critere, const QString &ordre);
    QSqlQueryModel* rechercher(const QString &critere, const QString &valeur);
    bool supprimer(int reference);
    bool modifier();
};

#endif // EQUIPEMENT_H
