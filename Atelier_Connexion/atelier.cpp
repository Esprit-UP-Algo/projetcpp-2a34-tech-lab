#include "atelier.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

Atelier::Atelier() {
    reference = ""; nom_atelier = ""; capacite = 0;
    jour = ""; horaire = ""; duree = 0; numero_salle = 0;
}

Atelier::Atelier(QString ref, QString nom, int cap, QString j, QString h, int d, int ns) {
    reference = ref; nom_atelier = nom; capacite = cap;
    jour = j; horaire = h; duree = d; numero_salle = ns;
}

bool Atelier::ajouter(QString *errorMsg) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) { if (errorMsg) *errorMsg = "Base non connectée."; return false; }
    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO ATELIER (REFERENCE, NOM_ATELIER, CAPACITE, JOUR, DUREE, NUM_SALLE, HORAIRE) "
        "VALUES (:ref, :nom, :cap, :jour, :duree, :salle, :horaire)"
        );
    query.bindValue(":ref", reference);
    query.bindValue(":nom", nom_atelier);
    query.bindValue(":cap", capacite);
    query.bindValue(":jour", jour);
    query.bindValue(":duree", duree);
    query.bindValue(":salle", numero_salle);
    query.bindValue(":horaire", horaire);
    if (!query.exec()) {
        if (errorMsg) *errorMsg = query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* Atelier::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT REFERENCE, NOM_ATELIER, CAPACITE, JOUR, DUREE, NUM_SALLE, HORAIRE FROM ATELIER ORDER BY REFERENCE");
    model->setHeaderData(0, Qt::Horizontal, "Référence");
    model->setHeaderData(1, Qt::Horizontal, "Nom d'atelier");
    model->setHeaderData(2, Qt::Horizontal, "Capacité");
    model->setHeaderData(3, Qt::Horizontal, "Jour");
    model->setHeaderData(4, Qt::Horizontal, "Durée");
    model->setHeaderData(5, Qt::Horizontal, "Numéro de salle");
    model->setHeaderData(6, Qt::Horizontal, "Horaire");
    return model;
}

bool Atelier::modifier() {
    QSqlQuery query(QSqlDatabase::database());
    query.prepare(
        "UPDATE ATELIER SET NOM_ATELIER=:nom, CAPACITE=:cap, JOUR=:jour, "
        "DUREE=:duree, NUM_SALLE=:salle, HORAIRE=:horaire WHERE REFERENCE=:ref"
        );
    query.bindValue(":ref", reference);
    query.bindValue(":nom", nom_atelier);
    query.bindValue(":cap", capacite);
    query.bindValue(":jour", jour);
    query.bindValue(":duree", duree);
    query.bindValue(":salle", numero_salle);
    query.bindValue(":horaire", horaire);
    return query.exec();
}

bool Atelier::supprimer(QString ref) {
    QSqlQuery query(QSqlDatabase::database());
    query.prepare("DELETE FROM ATELIER WHERE REFERENCE = :ref");
    query.bindValue(":ref", ref);
    return query.exec();
}

QMap<QString, int> Atelier::statistiquesParJour()
{
    QMap<QString, int> stats;
    QSqlQuery query;
    QString sql = "SELECT JOUR, COUNT(*) FROM ATELIER GROUP BY JOUR ORDER BY "
                  "CASE JOUR "
                  "WHEN 'Lundi' THEN 1 "
                  "WHEN 'Mardi' THEN 2 "
                  "WHEN 'Mercredi' THEN 3 "
                  "WHEN 'Jeudi' THEN 4 "
                  "WHEN 'Vendredi' THEN 5 "
                  "WHEN 'Samedi' THEN 6 "
                  "WHEN 'Dimanche' THEN 7 "
                  "END";

    if (query.exec(sql)) {
        while (query.next()) {
            stats[query.value(0).toString()] = query.value(1).toInt();
        }
    } else {
        qDebug() << "Erreur SQL stats:" << query.lastError().text();
    }
    return stats;
}
