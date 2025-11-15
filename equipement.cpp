#include "equipement.h"
#include <QSqlError>
#include <QDebug>

Equipement::Equipement()
    : reference(0), nom(""), quantite(0), categorie(""), prix(0.0)
{}

Equipement::Equipement(int reference, QString nom, int quantite, QString categorie, double prix)
{
    this->reference = reference;
    this->nom = nom;
    this->quantite = quantite;
    this->categorie = categorie;
    this->prix = prix;
}

// Getters
int Equipement::getReference() const { return reference; }
QString Equipement::getNom() const { return nom; }
int Equipement::getQuantite() const { return quantite; }
QString Equipement::getCategorie() const { return categorie; }
double Equipement::getPrix() const { return prix; }

// Setters avec validation
bool Equipement::setReference(int reference)
{
    if (reference > 0) {
        this->reference = reference;
        return true;
    }
    return false;
}

bool Equipement::setNom(QString nom)
{
    nom = nom.trimmed();
    if (!nom.isEmpty()) {
        this->nom = nom;
        return true;
    }
    return false;
}

bool Equipement::setQuantite(int quantite)
{
    if (quantite >= 0) {
        this->quantite = quantite;
        return true;
    }
    return false;
}

bool Equipement::setCategorie(QString categorie)
{
    categorie = categorie.trimmed();
    if (!categorie.isEmpty()) {
        this->categorie = categorie;
        return true;
    }
    return false;
}

bool Equipement::setPrix(double prix)
{
    if (prix >= 0) {
        this->prix = prix;
        return true;
    }
    return false;
}

// Méthodes de validation
bool Equipement::referenceExiste(int reference)
{
    QSqlQuery q;
    q.prepare("SELECT COUNT(1) FROM EQUIPEMENTS WHERE REFERENCE = :reference");
    q.bindValue(":reference", reference);
    if (!q.exec()) {
        qDebug() << "Erreur referenceExiste :" << q.lastError().text();
        return false;
    }
    if (q.next()) return q.value(0).toInt() > 0;
    return false;
}

bool Equipement::quantiteValide(int quantite)
{
    return quantite >= 0;
}

bool Equipement::prixValide(double prix)
{
    return prix >= 0;
}

bool Equipement::nomValide(const QString &nom)
{
    return !nom.isEmpty() && nom.length() <= 50;
}

// Méthodes CRUD
bool Equipement::ajouter()
{
    qDebug() << "*****TENTATIVE AJOUT EQUIPEMENT *****";
    qDebug() << "Référence:" << reference << "Nom:" << nom << "Quantité:" << quantite;
    qDebug() << "Catégorie:" << categorie << "Prix:" << prix;

    if (referenceExiste(reference)) {
        qDebug() << "ERREUR: Référence" << reference << "déjà utilisée dans la base!";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO EQUIPEMENTS (REFERENCE, NOM, QUANTITE, CATEGORIE, PRIX) "
                  "VALUES (:reference, :nom, :quantite, :categorie, :prix)");

    query.bindValue(":reference", reference);
    query.bindValue(":nom", nom);
    query.bindValue(":quantite", quantite);
    query.bindValue(":categorie", categorie);
    query.bindValue(":prix", prix);

    if (!query.exec()) {
        qDebug() << "ERREUR SQL:" << query.lastError().text();
        qDebug() << "Requête SQL:" << query.lastQuery();
        return false;
    }
    qDebug() << "AJOUT RÉUSSI pour Référence:" << reference;
    return true;
}

bool Equipement::modifier()
{
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT NOM, QUANTITE, CATEGORIE, PRIX FROM EQUIPEMENTS WHERE REFERENCE = :reference");
    selectQuery.bindValue(":reference", reference);

    if (!selectQuery.exec() || !selectQuery.next()) {
        qDebug() << "Erreur: Impossible de récupérer les données existantes pour Référence" << reference;
        return false;
    }

    QString oldNom = selectQuery.value(0).toString();
    int oldQuantite = selectQuery.value(1).toInt();
    QString oldCategorie = selectQuery.value(2).toString();
    double oldPrix = selectQuery.value(3).toDouble();

    QString finalNom = this->nom.isEmpty() ? oldNom : this->nom;
    int finalQuantite = this->quantite == 0 ? oldQuantite : this->quantite;
    QString finalCategorie = this->categorie.isEmpty() ? oldCategorie : this->categorie;
    double finalPrix = this->prix == 0.0 ? oldPrix : this->prix;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE EQUIPEMENTS SET NOM=:nom, QUANTITE=:quantite, "
                        "CATEGORIE=:categorie, PRIX=:prix WHERE REFERENCE=:reference");

    updateQuery.bindValue(":reference", reference);
    updateQuery.bindValue(":nom", finalNom);
    updateQuery.bindValue(":quantite", finalQuantite);
    updateQuery.bindValue(":categorie", finalCategorie);
    updateQuery.bindValue(":prix", finalPrix);

    if (!updateQuery.exec()) {
        qDebug() << "Erreur modification :" << updateQuery.lastError().text();
        return false;
    }

    qDebug() << "Modification réussie pour Référence:" << reference;
    return true;
}

QSqlQueryModel* Equipement::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT TO_CHAR(REFERENCE) AS REFERENCE, NOM, QUANTITE, CATEGORIE, PRIX FROM EQUIPEMENTS ORDER BY REFERENCE ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantité"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Catégorie"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));

    return model;
}

bool Equipement::supprimer(int reference)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EQUIPEMENTS WHERE REFERENCE = :reference");
    query.bindValue(":reference", reference);

    if (!query.exec()) {
        qDebug() << "Erreur suppression :" << query.lastError().text();
        return false;
    }
    return true;
}

// Recherche
QSqlQueryModel* Equipement::rechercher(const QString &critere, const QString &valeur)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QString whereClause;
    QString searchValue = valeur.trimmed();

    // Déterminer la clause WHERE selon le critère
    if (critere == "ID") {
        whereClause = "REFERENCE = " + searchValue;
    }
    else if (critere == "Nom") {
        whereClause = "UPPER(NOM) LIKE UPPER('%" + searchValue + "%')";
    }
    else if (critere == "Catégorie") {
        whereClause = "UPPER(CATEGORIE) LIKE UPPER('%" + searchValue + "%')";
    }
    else if (critere == "Quantité") {
        whereClause = "QUANTITE = " + searchValue;
    }
    else {
        whereClause = "REFERENCE = " + searchValue; // Défaut
    }

    // Construction de la requête SQL
    QString queryStr = "SELECT TO_CHAR(REFERENCE) AS REFERENCE, NOM, QUANTITE, CATEGORIE, PRIX FROM EQUIPEMENTS WHERE " + whereClause + " ORDER BY REFERENCE ASC";

    qDebug() << "=== RECHERCHE EQUIPEMENT ===";
    qDebug() << "Critère:" << critere;
    qDebug() << "Valeur:" << searchValue;
    qDebug() << "Requête SQL:" << queryStr;

    model->setQuery(queryStr);

    if (model->lastError().isValid()) {
        qDebug() << "ERREUR SQL:" << model->lastError().text();
        return model;
    }

    // Définition des en-têtes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Référence"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Quantité"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Catégorie"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));

    qDebug() << "Résultats trouvés:" << model->rowCount();
    qDebug() << "=== FIN RECHERCHE EQUIPEMENT ===";

    return model;
}

// Tri
QSqlQueryModel* Equipement::trier(const QString &critere, const QString &ordre)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString queryStr;

    if (critere == "ID") {
        queryStr = "SELECT TO_CHAR(REFERENCE) AS REFERENCE, NOM, QUANTITE, CATEGORIE, PRIX FROM EQUIPEMENTS ORDER BY REFERENCE " + ordre;
    } else if (critere == "Nom") {
        queryStr = "SELECT TO_CHAR(REFERENCE) AS REFERENCE, NOM, QUANTITE, CATEGORIE, PRIX FROM EQUIPEMENTS ORDER BY NOM " + ordre;
    } else if (critere == "Catégorie") {
        queryStr = "SELECT TO_CHAR(REFERENCE) AS REFERENCE, NOM, QUANTITE, CATEGORIE, PRIX FROM EQUIPEMENTS ORDER BY CATEGORIE " + ordre;
    } else if (critere == "Quantité") {
        queryStr = "SELECT TO_CHAR(REFERENCE) AS REFERENCE, NOM, QUANTITE, CATEGORIE, PRIX FROM EQUIPEMENTS ORDER BY QUANTITE " + ordre;
    } else if (critere == "Prix") {
        queryStr = "SELECT TO_CHAR(REFERENCE) AS REFERENCE, NOM, QUANTITE, CATEGORIE, PRIX FROM EQUIPEMENTS ORDER BY PRIX " + ordre;
    } else {
        queryStr = "SELECT TO_CHAR(REFERENCE) AS REFERENCE, NOM, QUANTITE, CATEGORIE, PRIX FROM EQUIPEMENTS ORDER BY REFERENCE ASC";
    }

    model->setQuery(queryStr);
    if (model->lastError().isValid()) {
        qDebug() << "ERREUR SQL dans trier():" << model->lastError().text();
    } else {
        qDebug() << "Requête exécutée avec succès";
        qDebug() << "Nombre de résultats:" << model->rowCount();
    }
    return model;
}
