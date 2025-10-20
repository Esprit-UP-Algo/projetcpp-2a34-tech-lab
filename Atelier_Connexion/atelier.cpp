#include "atelier.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

Atelier::Atelier() {}

Atelier::Atelier(QString ref, QString nom, int cap, QString j,
                 QString h, QString d, QString ns) {
    reference = ref;
    nom_atelier = nom;
    capacite = cap;
    jour = j;
    horaire = h;
    duree = d;
    numero_salle = ns;
}

// CREATE
bool Atelier::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO Atelier (reference, nom_atelier, capacite, "
                  "jour, horaire, duree, numero_salle) "
                  "VALUES (:ref, :nom, :cap, :jour, :horaire, :duree, :salle)");

    query.bindValue(":ref", reference);
    query.bindValue(":nom", nom_atelier);
    query.bindValue(":cap", capacite);
    query.bindValue(":jour", jour);
    query.bindValue(":horaire", horaire);
    query.bindValue(":duree", duree);
    query.bindValue(":salle", numero_salle);

    if (!query.exec()) {
        qDebug() << "Erreur ajout:" << query.lastError().text();
        return false;
    }
    return true;
}

// READ
QSqlQueryModel* Atelier::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Atelier ORDER BY reference");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom d'atelier"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Capacité"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Jour"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Horaire"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Durée"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Numéro de salle"));

    return model;
}

// UPDATE
bool Atelier::modifier() {
    QSqlQuery query;
    query.prepare("UPDATE Atelier SET nom_atelier=:nom, capacite=:cap, "
                  "jour=:jour, horaire=:horaire, duree=:duree, "
                  "numero_salle=:salle WHERE reference=:ref");

    query.bindValue(":ref", reference);
    query.bindValue(":nom", nom_atelier);
    query.bindValue(":cap", capacite);
    query.bindValue(":jour", jour);
    query.bindValue(":horaire", horaire);
    query.bindValue(":duree", duree);
    query.bindValue(":salle", numero_salle);

    if (!query.exec()) {
        qDebug() << "Erreur modification:" << query.lastError().text();
        return false;
    }
    return true;
}

// DELETE
bool Atelier::supprimer(QString ref) {
    QSqlQuery query;
    query.prepare("DELETE FROM Atelier WHERE reference=:ref");
    query.bindValue(":ref", ref);

    if (!query.exec()) {
        qDebug() << "Erreur suppression:" << query.lastError().text();
        return false;
    }
    return true;
}
