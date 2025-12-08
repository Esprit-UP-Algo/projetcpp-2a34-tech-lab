#include "employe.h"
#include <QSqlError>
#include <qsqlquery.h>
#include <QDebug>
Employe::Employe()
    : id(0), nom(""), prenom(""), email(""), tel(""), poste(""), mdp("") {}

Employe::Employe(int id, QString nom, QString prenom,
                 QString email, QString tel,
                 QString poste, QString mdp)
{
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->email = email;
    this->tel = tel;
    this->poste = poste;
    this->mdp = mdp;
}

// ======================
// VALIDATION
// ======================

bool Employe::emailValide(const QString &email)
{
    static const QRegularExpression regex(
        "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$"
        );
    return regex.match(email.trimmed()).hasMatch();
}

bool Employe::telValide(const QString &tel)
{
    static const QRegularExpression regex("^[259]\\d{7}$");
    return regex.match(tel.trimmed()).hasMatch();
}

bool Employe::idExiste(int id)
{
    QSqlQuery q;
    q.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE ID = :id");
    q.bindValue(":id", id);
    q.exec();

    if (q.next())
        return q.value(0).toInt() > 0;

    return false;
}

// ======================
// CRUD
// ======================

bool Employe::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYES (ID, NOM, PRENOM, EMAIL, TEL, POSTE, MDP) "
                  "VALUES (:id, :nom, :prenom, :email, :tel, :poste, :mdp)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":tel", tel);
    query.bindValue(":poste", poste);
    query.bindValue(":mdp", mdp);

    return query.exec();
}

bool Employe::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYES SET NOM=:nom, PRENOM=:prenom, EMAIL=:email, "
                  "TEL=:tel, POSTE=:poste, MDP=:mdp WHERE ID=:id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":tel", tel);
    query.bindValue(":poste", poste);
    query.bindValue(":mdp", mdp);

    return query.exec();
}

bool Employe::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYES WHERE ID = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QSqlQueryModel* Employe::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID, NOM, PRENOM, EMAIL, TEL, POSTE, MDP "
                    "FROM EMPLOYES ORDER BY ID ASC");
    return model;
}

// ======================
//    RECHERCHE
// ======================

QSqlQueryModel* Employe::rechercher(const QString &critere, const QString &valeur)
{
    QString v = valeur.trimmed();
    QString where;

    if (critere == "ID")
        where = "ID = " + v;

    else if (critere == "Nom")
        where = "UPPER(NOM) LIKE UPPER('%" + v + "%')";

    else if (critere == "Téléphone")
        where = "TEL LIKE '%" + v + "%'";

    else if (critere == "Poste")
        where = "UPPER(POSTE) LIKE UPPER('%" + v + "%')";

    else
        where = "1=1";

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID, NOM, PRENOM, EMAIL, TEL, POSTE, MDP "
                    "FROM EMPLOYES WHERE " + where);

    return model;
}

// ======================
//        TRI
// ======================

QSqlQueryModel* Employe::trier(const QString &critere, const QString &ordre)
{
    QString colonne;

    if (critere == "ID") colonne = "ID";
    else if (critere == "Nom") colonne = "NOM";
    else if (critere == "Poste") colonne = "POSTE";
    else colonne = "ID";

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID, NOM, PRENOM, EMAIL, TEL, POSTE, MDP "
                    "FROM EMPLOYES ORDER BY " + colonne + " " + ordre);
    return model;
}
