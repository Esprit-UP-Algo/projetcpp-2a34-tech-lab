#include "employe.h"
#include <QSqlQuery>
#include <QSqlError>

Employe::Employe() : id(0) {}
Employe::Employe(int id, QString nom, QString prenom, QString email, QString telephone, QString poste)
    : id(id), nom(nom), prenom(prenom), email(email), telephone(telephone), poste(poste) {}

// AJOUTER
bool Employe::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO employe (id, nom, prenom, email, telephone, poste) "
                  "VALUES (:id, :nom, :prenom, :email, :telephone, :poste)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":poste", poste);
    return query.exec();
}

// MODIFIER
bool Employe::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE employe SET nom=:nom, prenom=:prenom, email=:email, "
                  "telephone=:telephone, poste=:poste WHERE id=:id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":poste", poste);
    return query.exec();
}

// SUPPRIMER → CORRIGÉ
bool Employe::supprimer(int id)  // id est un paramètre
{
    QSqlQuery query;
    query.prepare("DELETE FROM employe WHERE id = :id");
    query.bindValue(":id", id);  // id du paramètre
    return query.exec();
}

// AFFICHER
QSqlTableModel* Employe::afficher()
{
    QSqlTableModel* model = new QSqlTableModel();
    model->setTable("employe");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prénom");
    model->setHeaderData(3, Qt::Horizontal, "Email");
    model->setHeaderData(4, Qt::Horizontal, "Téléphone");
    model->setHeaderData(5, Qt::Horizontal, "Poste");

    return model;
}
