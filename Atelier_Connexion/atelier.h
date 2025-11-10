#ifndef ATELIER_H
#define ATELIER_H

#include <QString>
#include <QSqlQueryModel>
#include <QMap>

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
    Atelier(QString, QString, int, QString, QString, int, int);

    // Getters & Setters
    QString getReference() const { return reference; }
    QString getNomAtelier() const { return nom_atelier; }
    int getCapacite() const { return capacite; }
    QString getJour() const { return jour; }
    QString getHoraire() const { return horaire; }
    int getDuree() const { return duree; }
    int getNumeroSalle() const { return numero_salle; }

    void setReference(QString r) { reference = r; }
    void setNomAtelier(QString n) { nom_atelier = n; }
    void setCapacite(int c) { capacite = c; }
    void setJour(QString j) { jour = j; }
    void setHoraire(QString h) { horaire = h; }
    void setDuree(int d) { duree = d; }
    void setNumeroSalle(int ns) { numero_salle = ns; }

    // CRUD
    bool ajouter(QString *errorMsg = nullptr);
    QSqlQueryModel* afficher();
    bool modifier();
    bool supprimer(QString ref);

    // STATISTIQUES
    QMap<QString, int> statistiquesParJour();
};

#endif // ATELIER_H
