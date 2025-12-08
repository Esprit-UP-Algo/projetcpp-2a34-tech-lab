#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QRegularExpression>

class Employe
{
public:
    Employe();
    Employe(int id, QString nom, QString prenom,
            QString email, QString tel,
            QString poste, QString mdp);

    // GETTERS
    int getId() const { return id; }
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    QString getEmail() const { return email; }
    QString getTel() const { return tel; }
    QString getPoste() const { return poste; }
    QString getMdp() const { return mdp; }

    // SETTERS
    void setId(int id) { this->id = id; }
    void setNom(QString n) { nom = n; }
    void setPrenom(QString p) { prenom = p; }
    void setEmail(QString e) { email = e; }
    void setTel(QString t) { tel = t; }
    void setPoste(QString po) { poste = po; }
    void setMdp(QString mp) { mdp = mp; }

    // VALIDATION
    static bool emailValide(const QString &email);
    static bool telValide(const QString &tel);
    static bool idExiste(int id);

    // CRUD
    bool ajouter();
    bool modifier();
    bool supprimer(int id);
    QSqlQueryModel* afficher();

    // MÉTIERS
    QSqlQueryModel* rechercher(const QString &critere, const QString &valeur);
    QSqlQueryModel* trier(const QString &critere, const QString &ordre);

private:
    int id;
    QString nom;
    QString prenom;
    QString email;
    QString tel;
    QString poste;
    QString mdp;
};

#endif // EMPLOYE_H
