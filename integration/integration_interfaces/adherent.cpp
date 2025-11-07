#include "adherent.h"
#include <QSqlError>
#include <qsqlquery.h>
#include <QDebug>
Adherent::Adherent()
    : id(0), nom(""), prenom(""), daten(QDate::currentDate()),
    email(""), tel(""), adr("") , sexe(""){}
Adherent::Adherent(int id, QString nom, QString prenom, QDate daten,
                   QString email, QString tel, QString adr, QString sexe)
{
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->daten = daten;
    this->email = email;
    this->tel = tel;
    this->adr = adr;
    this->sexe = sexe;
}
int Adherent::getId() const { return id; }
QString Adherent::getNom() const { return nom; }
QString Adherent::getPrenom() const { return prenom; }
QDate Adherent::getDateN() const { return daten; }
QString Adherent::getEmail() const { return email; }
QString Adherent::getTel() const { return tel; }
QString Adherent::getAdr() const { return adr; }
QString Adherent::getSexe() const { return sexe; }
bool Adherent::setId(int id)
{
    if (id > 0) { this->id = id; return true; }
    return false;
}

bool Adherent::setNom(QString nom)
{
    nom = nom.trimmed();
    if (!nom.isEmpty()) { this->nom = nom; return true; }
    return false;
}

bool Adherent::setPrenom(QString prenom)
{
    prenom = prenom.trimmed();
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
void Adherent::setSexe(QString sexe) {
    this->sexe = sexe;
}
bool Adherent::emailValide(const QString &email)
{
    const QString trimmed = email.trimmed();
    static const QRegularExpression regex(
        "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$"
        );
    return regex.match(trimmed).hasMatch();
}
bool Adherent::telValide(const QString &tel)
{
    static const QRegularExpression regex("^[259]\\d{7}$");
    return regex.match(tel.trimmed()).hasMatch();
}
bool Adherent::setEmail(QString email)
{
    email = email.trimmed();
    if (emailValide(email)) {
        this->email = email;
        return true;
    }
    return false;
}
bool Adherent::setTel(QString tel)
{
    tel = tel.trimmed();
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
bool Adherent::idExiste(int id)
{
    QSqlQuery q;
    q.prepare("SELECT COUNT(1) FROM ADHERENTS WHERE ID = :id");
    q.bindValue(":id", id);
    if (!q.exec()) {
        qDebug() << "Erreur idExiste :" << q.lastError().text();
        return false;
    }
    if (q.next()) return q.value(0).toInt() > 0;
    return false;
}
bool Adherent::idLen(int id)
{
    return id >= 10000000 && id <= 99999999;
}
bool Adherent::ajouter()
{
    qDebug() << "*****TENTATIVE AJOUT *****";
    qDebug() << "ID:" << id << "Nom:" << nom << "Prénom:" << prenom;
    qDebug() << "Téléphone:" << tel << "Email:" << email;
    qDebug() << "Sexe:" << sexe;

    if (idExiste(id)) {
        qDebug() << "ERREUR: ID" << id << "déjà utilisé dans la base!";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO ADHERENTS (ID, NOM, PRENOM, DATE_NAISS, EMAIL, TEL_ADH, ADRESSE_ADH, SEXE) "
                  "VALUES (:id, :nom, :prenom, :datenaissance, :email, :telephone, :adresse, :sexe)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":datenaissance", daten);
    query.bindValue(":email", email);
    query.bindValue(":telephone", tel);
    query.bindValue(":adresse", adr);
    query.bindValue(":sexe", sexe);
    if (!query.exec()) {
        qDebug() << "ERREUR SQL:" << query.lastError().text();
        qDebug() << "Requête SQL:" << query.lastQuery();
        return false;
    }
    qDebug() << "AJOUT RÉUSSI pour ID:" << id;
    return true;
}
bool Adherent::modifier()
{
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT NOM, PRENOM, DATE_NAISS, EMAIL, TEL_ADH, ADRESSE_ADH, SEXE FROM ADHERENTS WHERE ID = :id");
    selectQuery.bindValue(":id", id);

    if (!selectQuery.exec() || !selectQuery.next()) {
        qDebug() << "Erreur: Impossible de récupérer les données existantes pour ID" << id;
        return false;
    }

    QString oldNom = selectQuery.value(0).toString();
    QString oldPrenom = selectQuery.value(1).toString();
    QDate oldDaten = selectQuery.value(2).toDate();
    QString oldEmail = selectQuery.value(3).toString();
    QString oldTel = selectQuery.value(4).toString();
    QString oldAdr = selectQuery.value(5).toString();
    QString oldSexe = selectQuery.value(6).toString();

    QString finalNom = this->nom.isEmpty() ? oldNom : this->nom;
    QString finalPrenom = this->prenom.isEmpty() ? oldPrenom : this->prenom;
    QDate finalDaten = !this->daten.isValid() ? oldDaten : this->daten;
    QString finalEmail = this->email.isEmpty() ? oldEmail : this->email;
    QString finalTel = this->tel.isEmpty() ? oldTel : this->tel;
    QString finalAdr = this->adr.isEmpty() ? oldAdr : this->adr;
    QString finalSexe = this->sexe.isEmpty() ? oldSexe : this->sexe;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE ADHERENTS SET NOM=:nom, PRENOM=:prenom, DATE_NAISS=:daten, "
                        "EMAIL=:email, TEL_ADH=:tel, ADRESSE_ADH=:adr, SEXE=:sexe WHERE ID=:id");
    updateQuery.bindValue(":id", id);
    updateQuery.bindValue(":nom", finalNom);
    updateQuery.bindValue(":prenom", finalPrenom);
    updateQuery.bindValue(":daten", finalDaten);
    updateQuery.bindValue(":email", finalEmail);
    updateQuery.bindValue(":tel", finalTel);
    updateQuery.bindValue(":adr", finalAdr);
    updateQuery.bindValue(":sexe", finalSexe);

    if (!updateQuery.exec()) {
        qDebug() << "Erreur modification :" << updateQuery.lastError().text();
        return false;
    }

    qDebug() << "Modification réussie pour ID:" << id;
    return true;
}
QSqlQueryModel* Adherent::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT TO_CHAR(ID) AS ID, NOM, PRENOM, DATE_NAISS, EMAIL, TEL_ADH, ADRESSE_ADH, SEXE FROM ADHERENTS ORDER BY ID ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Sexe"));
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
