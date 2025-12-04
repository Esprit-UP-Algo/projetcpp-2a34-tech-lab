#ifndef ATELIER_H
#define ATELIER_H

#include <QString>
#include <QSqlQueryModel>
#include <QRegularExpression>

class Atelier {
private:
    QString reference;
    QString nom_atelier;
    int capacite;
    int capacite_max;
    QString jour;
    QString horaire;
    int duree;
    int numero_salle;
public:
    Atelier();
    Atelier(QString ref, QString nom, int cap, int cap_max, QString j, QString h, int d, int ns);
    QString getReference() const { return reference; }
    QString getNomAtelier() const { return nom_atelier; }
    int getCapacite() const { return capacite; }
    int getCapaciteMax() const { return capacite_max; }
    QString getJour() const { return jour; }
    QString getHoraire() const { return horaire; }
    int getDuree() const { return duree; }
    int getNumeroSalle() const { return numero_salle; }
    bool setReference(const QString &ref);
    bool setNomAtelier(const QString &nom);
    bool setCapacite(int cap);
    bool setCapaciteMax(int cm);
    bool setJour(const QString &j);
    bool setHoraire(const QString &h);
    bool setDuree(int d);
    bool setNumeroSalle(int ns);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool modifier();
    bool supprimer(const QString &ref);
    QSqlQueryModel* trier(const QString &critere, const QString &ordre);
    static bool referenceValide(const QString &ref);
    static bool horaireValide(const QString &horaire);
    static bool jourValide(const QString &jour);
    static bool referenceExiste(const QString &ref);
    QMap<QString, int> statistiquesJour();
    QMap<QString, int> statistiquesCapacite();

};

#endif // ATELIER_H
