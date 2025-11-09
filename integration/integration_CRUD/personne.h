//classe de base qui contiendra la classe adherent+employees+formateurs
#ifndef PERSONNE_H
#define PERSONNE_H
#include<QString>
class personne
{
protected:
    int id;
    QString nom;
    QString prenom;
    QString email;
    QString tel;
    QString adr;
public:
    personne();
    //get comm
    int getId() const;
    QString getNom() const;
    QString getPrenom() const;
    QString getEmail() const;
    QString getTel() const;
    QString getAdr() const;
    //setters comm
    bool setId(int id);
    bool setNom(QString nom);
    bool setPrenom(QString prenom);
    bool setEmail(QString email);
    bool setTel(QString tel);
    void setAdr(QString adr);//lazem class emp tzid el addresse
    //control de saisie
    static bool emailValide(const QString &email);
    static bool telValide(const QString &tel);
    //lazem nzid le controle du longeur
    static bool idExiste(int id);
    static bool idLen(int id);
};

#endif // PERSONNE_H
