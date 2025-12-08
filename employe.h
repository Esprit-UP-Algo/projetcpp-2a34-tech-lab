#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QSqlTableModel>

class Employe
{
public:
    Employe();
    Employe(int id, QString nom, QString prenom, QString email, QString telephone, QString poste);

    bool ajouter();
    bool modifier();
    bool supprimer(int id);  // CORRIGÉ : avec paramètre
    QSqlTableModel* afficher();

    // Setters
    void setId(int id) { this->id = id; }
    void setNom(const QString& n) { nom = n; }
    void setPrenom(const QString& p) { prenom = p; }
    void setEmail(const QString& e) { email = e; }
    void setTelephone(const QString& t) { telephone = t; }
    void setPoste(const QString& po) { poste = po; }

    // Getters (pour modifier/supprimer)
    int getId() const { return id; }

    bool findemp(QString id);

private:
    int id;
    QString nom, prenom, email, telephone, poste;
};

#endif // EMPLOYE_H
