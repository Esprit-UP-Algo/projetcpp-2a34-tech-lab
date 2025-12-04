#ifndef FORMATEUR_H
#define FORMATEUR_H

#include <QString>
#include <QSqlQueryModel>
#include <QDate>

class Formateur
{
private:
    int idf;
    QString nomf;
    QString emailf;
    QString mdpf;
    QString specialite;
    QString telf;
    QString adressef;

public:
    Formateur();
    Formateur(int idf, QString nomf, QString emailf, QString mdpf,
              QString specialite, QString telf, QString adressef);


    int getIdf() const;
    QString getNomf() const;
    QString getEmailf() const;
    QString getMdpf() const;
    QString getSpecialite() const;
    QString getTelf() const;
    QString getAdressef() const;


    bool setIdf(int idf);
    bool setNomf(QString nomf);
    bool setEmailf(QString emailf);
    void setMdpf(QString mdpf);
    void setSpecialite(QString specialite);
    bool setTelf(QString telf);
    void setAdressef(QString adressef);

    static bool emailValide(const QString &emailf);
    static bool telValide(const QString &telf);
    static bool mdpValide(const QString &mdpf);

    static bool idExiste(int idf);
    static bool idLen(int idf);
    bool ajouter();
    bool modifier();
    static QSqlQueryModel* afficher();
    static bool supprimer(int idf);


    static QSqlQueryModel* rechercher(const QString &critere, const QString &valeur);
    static QSqlQueryModel* trier(const QString &critere, const QString &ordre);


    QMap<QString, int> statistiques(const QString &critere);


    static bool envoyerSMS(const QString &telephone, const QString &message);
};

#endif // FORMATEUR_H
