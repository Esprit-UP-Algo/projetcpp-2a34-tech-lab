#ifndef ATELIER_H
#define ATELIER_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Atelier {
private:
    QString reference;
    QString nom_atelier;
    int capacite;
    QString jour;
    QString horaire;
    QString duree;
    QString numero_salle;

public:
    // Constructeurs
    Atelier();
    Atelier(QString, QString, int, QString, QString, QString, QString);

    // Getters
    QString getReference() const { return reference; }
    QString getNomAtelier() const { return nom_atelier; }
    int getCapacite() const { return capacite; }
    QString getJour() const { return jour; }
    QString getHoraire() const { return horaire; }
    QString getDuree() const { return duree; }
    QString getNumeroSalle() const { return numero_salle; }

    // Setters
    void setReference(QString r) { reference = r; }
    void setNomAtelier(QString n) { nom_atelier = n; }
    void setCapacite(int c) { capacite = c; }
    void setJour(QString j) { jour = j; }
    void setHoraire(QString h) { horaire = h; }
    void setDuree(QString d) { duree = d; }
    void setNumeroSalle(QString ns) { numero_salle = ns; }

    // CRUD Operations
    bool ajouter();
    bool modifier();
    bool supprimer(QString);
    QSqlQueryModel* afficher();
};

#endif
