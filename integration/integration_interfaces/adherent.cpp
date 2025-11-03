#include "adherent.h"
#include <QSqlError>
#include <qsqlquery.h>
#include <QDebug>

Adherent::Adherent()
    : id(0), nom(""), prenom(""), daten(QDate::currentDate()),
    email(""), tel(""), adr("") {}

Adherent::Adherent(int id, QString nom, QString prenom, QDate daten,
                   QString email, QString tel, QString adr)
{
    setId(id);
    setNom(nom);
    setPrenom(prenom);
    setDateN(daten);
    setEmail(email);
    setTel(tel);
    setAdr(adr);
}
int Adherent::getId() const { return id; }
QString Adherent::getNom() const { return nom; }
QString Adherent::getPrenom() const { return prenom; }
QDate Adherent::getDateN() const { return daten; }
QString Adherent::getEmail() const { return email; }
QString Adherent::getTel() const { return tel; }
QString Adherent::getAdr() const { return adr; }

bool Adherent::setId(int id)
{
    if (id > 0) { this->id = id; return true; }
    return false;
}

bool Adherent::setNom(QString nom)
{
    if (!nom.isEmpty()) { this->nom = nom; return true; }
    return false;
}

bool Adherent::setPrenom(QString prenom)
{
    if (!prenom.isEmpty()) { this->prenom = prenom; return true; }
    return false;
}

bool Adherent::setDateN(QDate daten)
{
    if (daten.isValid() && daten <= QDate::currentDate()) {
        this->daten = daten;
        return true;
    }
    return false;
}


bool Adherent::setEmail(QString email)
{
    if (emailValide(email)) {
        this->email = email;
        return true;
    }
    return false;
}

bool Adherent::setTel(QString tel)
{
    if (telValide(tel)) {
        this->tel = tel;
        return true;
    }
    return false;
}

void Adherent::setAdr(QString adr)
{
    this->adr = adr;
}
bool Adherent::emailValide(const QString &email)
{
    QString trimmed = email.trimmed();
    static const QRegularExpression regex(
        "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$"
        );
    return regex.match(trimmed).hasMatch();
}
bool Adherent::telValide(const QString &tel)
{
    static const QRegularExpression regex("^\\d{8,12}$"); // 8 à 12 chiffres
    return regex.match(tel).hasMatch();
};
bool Adherent::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO ADHERENTS (ID, NOM, PRENOM, DATEN, EMAIL, TEL, ADR) "
                  "VALUES (:id, :nom, :prenom, :datenaissance, :email, :telephone, :adresse)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":datenaissance", daten);
    query.bindValue(":email", email);
    query.bindValue(":telephone", tel);
    query.bindValue(":adresse", adr);

    if (!query.exec()) {
        qDebug() << "Erreur ajout :" << query.lastError().text();
        return false;
    }
    return true;
}

bool Adherent::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE ADHERENTS SET NOM=:nom, PRENOM=:prenom, DATEN=:daten, "
                  "EMAIL=:email, TEL=:tel, ADR=:adr WHERE ID=:id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":daten", daten);
    query.bindValue(":email", email);
    query.bindValue(":tel", tel);
    query.bindValue(":adr", adr);

    if (!query.exec()) {
        qDebug() << "Erreur modification :" << query.lastError().text();
        return false;
    }
    return true;
}
QSqlQueryModel* Adherent::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID, NOM, PRENOM, DATEN, EMAIL, TEL, ADR FROM ADHERENTS ORDER BY ID ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
    return model;
}

bool Adherent::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM ADHERENTS WHERE ID = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur suppression :" << query.lastError().text();
        return false;
    }
    return true;
}


