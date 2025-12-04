#ifndef ADHERENT_H
#define ADHERENT_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QRegularExpression>

class Adherent
{
private:
    int id;
    QString nom;
    QString prenom;
    QDate daten;
    QString email;
    QString tel;
    QString adr;
    QString sexe;
    QString cv_path;
    QByteArray cvFile;

public:
    Adherent();
    Adherent(int id, QString nom, QString prenom, QDate daten,
             QString email, QString tel, QString adr, QString sexe);
    int getId() const;
    QString getNom() const;
    QString getPrenom() const;
    QDate getDateN() const;
    QString getEmail() const;
    QString getTel() const;
    QString getAdr() const;
    QString getSexe() const;
    QByteArray getCvFile() const { return cvFile; }
    bool setId(int id);
    bool setNom(QString nom);
    bool setPrenom(QString prenom);
    bool setDateN(QDate daten);
    bool setEmail(QString email);
    bool setTel(QString tel);
    void setAdr(QString adr);
    void setSexe(QString sexe);
    void setCvFile(const QByteArray &data) { cvFile = data; }
    static bool emailValide(const QString &email);
    static bool telValide(const QString &tel);
    static bool idExiste(int id);
    static bool idLen(int id);
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* trier(const QString &critere, const QString &ordre );
    QSqlQueryModel* rechercher(const QString &critere, const QString &valeur);
    bool supprimer(int id);
    bool modifier();
    QMap<QString, int> statistiques(const QString &critere);

};

#endif // ADHERENT_H
