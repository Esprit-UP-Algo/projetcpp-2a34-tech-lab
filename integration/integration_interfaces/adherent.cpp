#include "adherent.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// Constructeurs
Adherent::Adherent()
    : id_adherent(0), nom(""), prenom(""), date_naissance(""), email(""), telephone(""), adresse("")
{}

Adherent::Adherent(int id, QString n, QString p, QString dn, QString e, QString t, QString a)
    : id_adherent(id), nom(n), prenom(p), date_naissance(dn), email(e), telephone(t), adresse(a)
{}

// Getters
int Adherent::getId() const { return id_adherent; }
QString Adherent::getNom() const { return nom; }
QString Adherent::getPrenom() const { return prenom; }
QString Adherent::getDateNaissance() const { return date_naissance; }
QString Adherent::getEmail() const { return email; }
QString Adherent::getTelephone() const { return telephone; }
QString Adherent::getAdresse() const { return adresse; }

// Setters
void Adherent::setId(int id) { id_adherent = id; }
void Adherent::setNom(QString n) { nom = n; }
void Adherent::setPrenom(QString p) { prenom = p; }
void Adherent::setDateNaissance(QString dn) { date_naissance = dn; }
void Adherent::setEmail(QString e) { email = e; }
void Adherent::setTelephone(QString t) { telephone = t; }
void Adherent::setAdresse(QString a) { adresse = a; }

// CRUD - AJOUTER
bool Adherent::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO ADHERENTS (ID, NOM, PRENOM, DATEN_ADH, TEL_ADH, ADDRESSE_ADH, EMAIL) "
                  "VALUES (:id, :nom, :prenom, :date_naissance, :telephone, :adresse, :email)");

    query.bindValue(":id", id_adherent);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date_naissance", date_naissance);
    query.bindValue(":telephone", telephone);
    query.bindValue(":adresse", adresse);
    query.bindValue(":email", email);

    qDebug() << "Tentative d'ajout - ID:" << id_adherent << "Nom:" << nom << "Prénom:" << prenom;

    if (query.exec()) {
        qDebug() << "✅ Ajout réussi dans ADHERENTS!";
        return true;
    } else {
        qDebug() << "❌ Erreur SQL:" << query.lastError().text();
        return false;
    }
}

// CRUD - AFFICHER
QSqlQueryModel* Adherent::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("SELECT ID, NOM, PRENOM, DATEN_ADH, TEL_ADH, ADDRESSE_ADH, EMAIL FROM ADHERENTS");

    if (model->lastError().isValid()) {
        qDebug() << "❌ Erreur affichage:" << model->lastError().text();
    } else {
        qDebug() << "✅ Affichage réussi, lignes:" << model->rowCount();
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date de naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Email"));

    return model;
}

// CRUD - MODIFIER
bool Adherent::modifier(int id)
{
    QSqlQuery query;

    query.prepare("UPDATE ADHERENTS SET NOM=:nom, PRENOM=:prenom, DATEN_ADH=:date_naissance, "
                  "TEL_ADH=:telephone, ADDRESSE_ADH=:adresse, EMAIL=:email WHERE ID=:id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date_naissance", date_naissance);
    query.bindValue(":telephone", telephone);
    query.bindValue(":adresse", adresse);
    query.bindValue(":email", email);

    qDebug() << "Tentative modification - ID:" << id;

    if (query.exec()) {
        qDebug() << "✅ Modification réussie!";
        return true;
    } else {
        qDebug() << "❌ Erreur modification:" << query.lastError().text();
        return false;
    }
}

// CRUD - SUPPRIMER
bool Adherent::supprimer(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM ADHERENTS WHERE ID=:id");
    query.bindValue(":id", id);

    qDebug() << "Tentative suppression - ID:" << id;

    if (query.exec()) {
        qDebug() << "✅ Suppression réussie!";
        return true;
    } else {
        qDebug() << "❌ Erreur suppression:" << query.lastError().text();
        return false;
    }
}
