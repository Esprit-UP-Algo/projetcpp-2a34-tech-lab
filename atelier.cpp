#include "atelier.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRegularExpression>
Atelier::Atelier() {
    reference = nom_atelier = jour = horaire = "";
    capacite = capacite_max = duree = numero_salle = 0;
}
Atelier::Atelier(QString ref, QString nom, int cap, int cap_max, QString j, QString h, int d, int ns) {
    setReference(ref);
    setNomAtelier(nom);
    setCapacite(cap);
    setCapaciteMax(cap_max);
    setJour(j);
    setHoraire(h);
    setDuree(d);
    setNumeroSalle(ns);
}
bool Atelier::setReference(const QString &ref)
{
    QString r = ref.trimmed();

    if (r.length() < 3 || r.length() > 10) {
        return false;
    }

    bool ok;
    qint64 num = r.toLongLong(&ok);
    if (!ok || num < 0) {
        return false; // contient autre chose que des chiffres
    }
    reference = r;   // On garde exactement ce que l'utilisateur a tapé
    return true;
}
bool Atelier::setNomAtelier(const QString &nom) {
    if (nom.length() >= 3 && nom.length() <= 50) {
        nom_atelier = nom;
        return true;
    }
    return false;
}
bool Atelier::setCapacite(int cap) {
    if (cap >= 0 && cap <= 1000) {
        capacite = cap;
        return true;
    }
    return false;
}
bool Atelier::setCapaciteMax(int cm) {
    if (cm >= 10 && cm <= 500) {
        capacite_max = cm;
        return true;
    }
    return false;
}
bool Atelier::setJour(const QString &j) {
    QStringList jours = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};
    if (jours.contains(j, Qt::CaseInsensitive)) {
        jour = j;
        return true;
    }
    return false;
}
bool Atelier::setHoraire(const QString &h) {
    QRegularExpression re("^([0-1]?[0-9]|2[0-3]):[0-5][0-9]$");
    if (re.match(h).hasMatch()) {
        horaire = h;
        return true;
    }
    return false;
}
bool Atelier::setDuree(int d) {
    if (d >= 1 && d <= 10) {
        duree = d;
        return true;
    }
    return false;
}
bool Atelier::setNumeroSalle(int ns) {
    if (ns >= 1 && ns <= 999) {
        numero_salle = ns;
        return true;
    }
    return false;
}
bool Atelier::ajouter() {
    if (referenceExiste(reference)) return false;

    QSqlQuery query;
    query.prepare(
        "INSERT INTO ATELIER (REFERENCE, NOM_ATELIER, CAPACITE, CAPACITE_MAX, JOUR, DUREE, NUM_SALLE, HORAIRE) "
        "VALUES (:ref, :nom, :cap, :cap_max, :jour, :duree, :salle, :horaire)"
        );
    query.bindValue(":ref", reference);
    query.bindValue(":nom", nom_atelier);
    query.bindValue(":cap", capacite);
    query.bindValue(":cap_max", capacite_max);
    query.bindValue(":jour", jour);
    query.bindValue(":duree", duree);
    query.bindValue(":salle", numero_salle);
    query.bindValue(":horaire", horaire);

    return query.exec();
}
QSqlQueryModel* Atelier::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT REFERENCE, NOM_ATELIER, CAPACITE, CAPACITE_MAX, JOUR, DUREE, NUM_SALLE, HORAIRE FROM ATELIER ORDER BY REFERENCE");

    model->setHeaderData(0, Qt::Horizontal, "Référence");
    model->setHeaderData(1, Qt::Horizontal, "Nom d'atelier");
    model->setHeaderData(2, Qt::Horizontal, "Capacité");
    model->setHeaderData(3, Qt::Horizontal, "Capacité Max");
    model->setHeaderData(4, Qt::Horizontal, "Jour");
    model->setHeaderData(5, Qt::Horizontal, "Durée");
    model->setHeaderData(6, Qt::Horizontal, "Salle");
    model->setHeaderData(7, Qt::Horizontal, "Horaire");
    return model;
}
bool Atelier::modifier() {
    QSqlQuery query;
    query.prepare(
        "UPDATE ATELIER SET NOM_ATELIER=:nom, CAPACITE=:cap, CAPACITE_MAX=:cap_max, "
        "JOUR=:jour, DUREE=:duree, NUM_SALLE=:salle, HORAIRE=:horaire WHERE REFERENCE=:ref"
        );
    query.bindValue(":ref", reference);
    query.bindValue(":nom", nom_atelier);
    query.bindValue(":cap", capacite);
    query.bindValue(":cap_max", capacite_max);
    query.bindValue(":jour", jour);
    query.bindValue(":duree", duree);
    query.bindValue(":salle", numero_salle);
    query.bindValue(":horaire", horaire);
    return query.exec();
}
bool Atelier::supprimer(const QString &ref) {
    QSqlQuery query;
    query.prepare("DELETE FROM ATELIER WHERE REFERENCE = :ref");
    query.bindValue(":ref", ref);
    return query.exec();
}
QSqlQueryModel* Atelier::trier(const QString &critere, const QString &ordre) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QString sql = "SELECT REFERENCE, NOM_ATELIER, CAPACITE, CAPACITE_MAX, JOUR, DUREE, NUM_SALLE, HORAIRE FROM ATELIER";
    if (critere == "jour") sql += " ORDER BY JOUR " + ordre;
    else if (critere == "horaire") sql += " ORDER BY HORAIRE " + ordre;
    else if (critere == "capacité") sql += " ORDER BY CAPACITE " + ordre;
    else if (critere == "salle") sql += " ORDER BY NUM_SALLE " + ordre;
    else sql += " ORDER BY REFERENCE";
    model->setQuery(sql);
    return model;
}
bool Atelier::referenceExiste(const QString &ref) {
    QSqlQuery query;
    query.prepare("SELECT REFERENCE FROM ATELIER WHERE REFERENCE = :ref");
    query.bindValue(":ref", ref);
    query.exec();
    return query.next();
}
bool Atelier::referenceValide(const QString &ref) {
    QRegularExpression re("^[A-Z]{3}[0-9]{3}$");
    return re.match(ref).hasMatch();
}
bool Atelier::horaireValide(const QString &horaire) {
    QRegularExpression re("^([0-1]?[0-9]|2[0-3]):[0-5][0-9]$");
    return re.match(horaire).hasMatch();
}
bool Atelier::jourValide(const QString &jour) {
    QStringList jours = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};
    return jours.contains(jour, Qt::CaseInsensitive);
}
QMap<QString, int> Atelier::statistiquesJour()
{
    QMap<QString, int> stats;
    QSqlQuery q;

    q.prepare("SELECT JOUR, COUNT(*) FROM ATELIER GROUP BY JOUR");

    if (q.exec()) {
        while (q.next()) {
            QString jour = q.value(0).toString();
            int count = q.value(1).toInt();
            stats[jour] = count;
        }
    }

    return stats;
}
QMap<QString, int> Atelier::statistiquesCapacite()
{
    QMap<QString, int> stats;
    QSqlQuery q("SELECT CAPACITE, COUNT(*) FROM ATELIER GROUP BY CAPACITE");

    while (q.next()) {
        QString capacite = q.value(0).toString();
        int count = q.value(1).toInt();
        stats[capacite] = count;
    }

    return stats;
}
