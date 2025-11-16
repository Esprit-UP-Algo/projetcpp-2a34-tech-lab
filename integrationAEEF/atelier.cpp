#include "atelier.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Atelier::Atelier() {
    reference = ""; nom_atelier = ""; capacite = 0;
    jour = ""; horaire = ""; duree = 0; numero_salle = 0;
}

Atelier::Atelier(QString ref, QString nom, int cap, QString j, QString h, int d, int ns) {
    setReference(ref);
    setNomAtelier(nom);
    setCapacite(cap);
    setJour(j);
    setHoraire(h);
    setDuree(d);
    setNumeroSalle(ns);
}

// === SETTERS AVEC VALIDATION ===
bool Atelier::setReference(const QString &ref) {
    QString trimmed = ref.trimmed();
    if (referenceValide(trimmed)) {
        reference = trimmed;
        return true;
    }
    return false;
}

bool Atelier::setNomAtelier(const QString &nom) {
    QString trimmed = nom.trimmed();
    if (!trimmed.isEmpty()) {
        nom_atelier = trimmed;
        return true;
    }
    return false;
}

bool Atelier::setCapacite(int cap) {
    if (cap >= 1 && cap <= 1000) {
        capacite = cap;
        return true;
    }
    return false;
}

bool Atelier::setJour(const QString &j) {
    if (jourValide(j)) {
        jour = j.trimmed();
        return true;
    }
    return false;
}

bool Atelier::setHoraire(const QString &h) {
    if (horaireValide(h)) {
        horaire = h.trimmed();
        return true;
    }
    return false;
}

bool Atelier::setDuree(int d) {
    if (d >= 1 && d <= 24) {
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

// === VALIDATIONS STATIQUES ===
bool Atelier::referenceValide(const QString &ref) {
    if (ref.length() > 10) return false;
    static const QRegularExpression re("^[A-Za-z0-9]+$");
    return re.match(ref).hasMatch();
}

bool Atelier::horaireValide(const QString &horaire) {
    static const QRegularExpression re("^([0-1]?[0-9]|2[0-3]):[0-5][0-9]$");
    return re.match(horaire.trimmed()).hasMatch();
}

bool Atelier::jourValide(const QString &jour) {
    QStringList jours = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};
    return jours.contains(jour.trimmed(), Qt::CaseInsensitive);
}

bool Atelier::referenceExiste(const QString &ref) {
    QSqlQuery q;
    q.prepare("SELECT COUNT(1) FROM ATELIER WHERE REFERENCE = :ref");
    q.bindValue(":ref", ref);
    if (!q.exec()) {
        qDebug() << "Erreur referenceExiste:" << q.lastError().text();
        return false;
    }
    return q.next() && q.value(0).toInt() > 0;
}

// === AJOUTER ===
bool Atelier::ajouter() {
    qDebug() << "*****TENTATIVE AJOUT ATELIER*****";
    qDebug() << "Ref:" << reference << "Nom:" << nom_atelier << "Cap:" << capacite;
    qDebug() << "Jour:" << jour << "Horaire:" << horaire << "Durée:" << duree << "Salle:" << numero_salle;

    if (referenceExiste(reference)) {
        qDebug() << "ERREUR: Référence" << reference << "déjà utilisée !";
        return false;
    }

    QSqlQuery query;
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
        qDebug() << "ERREUR SQL AJOUT:" << query.lastError().text();
        return false;
    }
    qDebug() << "AJOUT RÉUSSI pour référence:" << reference;
    return true;
}

// === AFFICHER ===
QSqlQueryModel* Atelier::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
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

// === MODIFIER ===
bool Atelier::modifier() {
    QSqlQuery query;
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

    if (!query.exec()) {
        qDebug() << "ERREUR MODIFICATION:" << query.lastError().text();
        return false;
    }
    qDebug() << "MODIFICATION RÉUSSIE pour référence:" << reference;
    return true;
}

// === SUPPRIMER ===
bool Atelier::supprimer(const QString &ref) {
    QSqlQuery query;
    query.prepare("DELETE FROM ATELIER WHERE REFERENCE = :ref");
    query.bindValue(":ref", ref);
    if (!query.exec()) {
        qDebug() << "ERREUR SUPPRESSION:" << query.lastError().text();
        return false;
    }
    qDebug() << "SUPPRESSION RÉUSSIE pour référence:" << ref;
    return true;
}

// === RECHERCHER ===
QSqlQueryModel* Atelier::rechercher(const QString &critere, const QString &valeur) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QString whereClause;
    QString searchValue = valeur.trimmed();

    if (critere == "Référence") {
        whereClause = "REFERENCE = '" + searchValue + "'";
    } else if (critere == "Nom") {
        whereClause = "UPPER(NOM_ATELIER) LIKE UPPER('%" + searchValue + "%')";
    } else if (critere == "Salle") {
        whereClause = "NUM_SALLE = " + searchValue;
    } else {
        whereClause = "1=1";
    }

    QString sql = "SELECT REFERENCE, NOM_ATELIER, CAPACITE, JOUR, DUREE, NUM_SALLE, HORAIRE "
                  "FROM ATELIER WHERE " + whereClause + " ORDER BY REFERENCE";

    qDebug() << "=== RECHERCHE ATELIER ===";
    qDebug() << "Critère:" << critere << "Valeur:" << searchValue;
    qDebug() << "SQL:" << sql;

    model->setQuery(sql);
    if (model->lastError().isValid()) {
        qDebug() << "ERREUR SQL RECHERCHE:" << model->lastError().text();
    } else {
        qDebug() << "Résultats trouvés:" << model->rowCount();
    }

    model->setHeaderData(0, Qt::Horizontal, "Référence");
    model->setHeaderData(1, Qt::Horizontal, "Nom d'atelier");
    model->setHeaderData(2, Qt::Horizontal, "Capacité");
    model->setHeaderData(3, Qt::Horizontal, "Jour");
    model->setHeaderData(4, Qt::Horizontal, "Durée");
    model->setHeaderData(5, Qt::Horizontal, "Numéro de salle");
    model->setHeaderData(6, Qt::Horizontal, "Horaire");

    return model;
}

// === TRIER ===
QSqlQueryModel* Atelier::trier(const QString &critere, const QString &ordre) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QString sql = "SELECT REFERENCE, NOM_ATELIER, CAPACITE, JOUR, DUREE, NUM_SALLE, HORAIRE FROM ATELIER";

    if (critere == "jour") {
        sql += " ORDER BY CASE JOUR WHEN 'Lundi' THEN 1 WHEN 'Mardi' THEN 2 WHEN 'Mercredi' THEN 3 "
               "WHEN 'Jeudi' THEN 4 WHEN 'Vendredi' THEN 5 WHEN 'Samedi' THEN 6 WHEN 'Dimanche' THEN 7 END " + ordre;
    } else if (critere == "capacité") {
        sql += " ORDER BY CAPACITE " + ordre;
    } else if (critere == "horaire") {
        sql += " ORDER BY HORAIRE " + ordre;
    } else {
        sql += " ORDER BY REFERENCE " + ordre;
    }

    model->setQuery(sql);
    if (model->lastError().isValid()) {
        qDebug() << "ERREUR TRI:" << model->lastError().text();
    }

    model->setHeaderData(0, Qt::Horizontal, "Référence");
    model->setHeaderData(1, Qt::Horizontal, "Nom d'atelier");
    model->setHeaderData(2, Qt::Horizontal, "Capacité");
    model->setHeaderData(3, Qt::Horizontal, "Jour");
    model->setHeaderData(4, Qt::Horizontal, "Durée");
    model->setHeaderData(5, Qt::Horizontal, "Numéro de salle");
    model->setHeaderData(6, Qt::Horizontal, "Horaire");

    return model;
}

// === STATISTIQUES ===
QMap<QString, int> Atelier::statistiquesParJour() {
    QMap<QString, int> stats;
    QSqlQuery query;
    QString sql = "SELECT JOUR, COUNT(*) FROM ATELIER GROUP BY JOUR ORDER BY "
                  "CASE JOUR WHEN 'Lundi' THEN 1 WHEN 'Mardi' THEN 2 WHEN 'Mercredi' THEN 3 "
                  "WHEN 'Jeudi' THEN 4 WHEN 'Vendredi' THEN 5 WHEN 'Samedi' THEN 6 WHEN 'Dimanche' THEN 7 END";
    if (query.exec(sql)) {
        while (query.next()) {
            stats[query.value(0).toString()] = query.value(1).toInt();
        }
    } else {
        qDebug() << "Erreur SQL stats:" << query.lastError().text();
    }
    return stats;
}
