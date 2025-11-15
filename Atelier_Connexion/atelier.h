#ifndef ATELIER_H
#define ATELIER_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QMap>
#include <QRegularExpression>

class Atelier {
private:
    QString reference;
    QString nom_atelier;
    int capacite;
    QString jour;
    QString horaire;
    int duree;
    int numero_salle;

public:
    Atelier();
    Atelier(QString ref, QString nom, int cap, QString j, QString h, int d, int ns);

    // Getters
    QString getReference() const { return reference; }
    QString getNomAtelier() const { return nom_atelier; }
    int getCapacite() const { return capacite; }
    QString getJour() const { return jour; }
    QString getHoraire() const { return horaire; }
    int getDuree() const { return duree; }
    int getNumeroSalle() const { return numero_salle; }

    // Setters avec validation (comme ton ami)
    bool setReference(const QString &ref);
    bool setNomAtelier(const QString &nom);
    bool setCapacite(int cap);
    bool setJour(const QString &j);
    bool setHoraire(const QString &h);
    bool setDuree(int d);
    bool setNumeroSalle(int ns);

    // Validation statique
    static bool referenceExiste(const QString &ref);
    static bool referenceValide(const QString &ref);
    static bool horaireValide(const QString &horaire);
    static bool jourValide(const QString &jour);

    // CRUD
    bool ajouter();
    QSqlQueryModel* afficher();
    bool modifier();
    bool supprimer(const QString &ref);

    // Métier
    QSqlQueryModel* rechercher(const QString &critere, const QString &valeur);
    QSqlQueryModel* trier(const QString &critere, const QString &ordre);
    QMap<QString, int> statistiquesParJour();
};

#endif // ATELIER_H
