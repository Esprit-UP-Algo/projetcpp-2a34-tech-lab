#include "formateur.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QRegularExpression>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>

Formateur::Formateur()
    : idf(0), nomf(""), emailf(""), mdpf(""), specialite(""), telf(""), adressef("") {}

Formateur::Formateur(int idf, QString nomf, QString emailf, QString mdpf,
                     QString specialite, QString telf, QString adressef)
{
    this->idf = idf;
    this->nomf = nomf;
    this->emailf = emailf;
    this->mdpf = mdpf;
    this->specialite = specialite;
    this->telf = telf;
    this->adressef = adressef;
}

// Getters
int Formateur::getIdf() const { return idf; }
QString Formateur::getNomf() const { return nomf; }
QString Formateur::getEmailf() const { return emailf; }
QString Formateur::getMdpf() const { return mdpf; }
QString Formateur::getSpecialite() const { return specialite; }
QString Formateur::getTelf() const { return telf; }
QString Formateur::getAdressef() const { return adressef; }

// Setters
bool Formateur::setIdf(int idf)
{
    if (idf > 0) {
        this->idf = idf;
        return true;
    }
    return false;
}

bool Formateur::setNomf(QString nomf)
{
    nomf = nomf.trimmed();
    if (!nomf.isEmpty()) {
        this->nomf = nomf;
        return true;
    }
    return false;
}

bool Formateur::setEmailf(QString emailf)
{
    emailf = emailf.trimmed();
    if (emailValide(emailf)) {
        this->emailf = emailf;
        return true;
    }
    return false;
}

void Formateur::setMdpf(QString mdpf)
{
    this->mdpf = mdpf;
}

void Formateur::setSpecialite(QString specialite)
{
    this->specialite = specialite;
}

bool Formateur::setTelf(QString telf)
{
    telf = telf.trimmed();
    if (telValide(telf)) {
        this->telf = telf;
        return true;
    }
    return false;
}

void Formateur::setAdressef(QString adressef)
{
    this->adressef = adressef;
}

// Validation methods
bool Formateur::emailValide(const QString &emailf)
{
    const QString trimmed = emailf.trimmed();
    static const QRegularExpression regex(
        "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$"
        );
    return regex.match(trimmed).hasMatch();
}

bool Formateur::telValide(const QString &telf)
{
    static const QRegularExpression regex("^[259]\\d{7}$");
    return regex.match(telf.trimmed()).hasMatch();
}

bool Formateur::mdpValide(const QString &mdpf)
{
    return mdpf.length() >= 6 && mdpf.length() <= 8;
}

// Database operations
bool Formateur::idExiste(int idf)
{
    QSqlQuery q;
    q.prepare("SELECT COUNT(1) FROM FORMATEUR WHERE IDF = :id");
    q.bindValue(":id", idf);
    if (!q.exec()) {
        qDebug() << "Erreur idExiste :" << q.lastError().text();
        return false;
    }
    if (q.next()) return q.value(0).toInt() > 0;
    return false;
}

bool Formateur::idLen(int idf)
{
    return idf >= 10000000 && idf <= 99999999;
}

bool Formateur::ajouter()
{
    qDebug() << "*****TENTATIVE AJOUT FORMATEUR *****";
    qDebug() << "ID:" << idf << "Nom:" << nomf << "Email:" << emailf;
    qDebug() << "Spécialité:" << specialite << "Téléphone:" << telf;

    if (idExiste(idf)) {
        qDebug() << "ERREUR: ID" << idf << "déjà utilisé dans la base!";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO FORMATEUR (IDF, NOMF, EMAILF, MDPF, SPECIALITE, TELF, ADRESSEF) "
                  "VALUES (:id, :nom, :email, :mdp, :specialite, :tel, :adresse)");

    query.bindValue(":id", idf);
    query.bindValue(":nom", nomf);
    query.bindValue(":email", emailf);
    query.bindValue(":mdp", mdpf);
    query.bindValue(":specialite", specialite);
    query.bindValue(":tel", telf);
    query.bindValue(":adresse", adressef);

    if (!query.exec()) {
        qDebug() << "ERREUR SQL:" << query.lastError().text();
        qDebug() << "Requête SQL:" << query.lastQuery();
        return false;
    }
    qDebug() << "AJOUT RÉUSSI pour ID:" << idf;
    return true;
}

bool Formateur::modifier()
{
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT NOMF, EMAILF, MDPF, SPECIALITE, TELF, ADRESSEF FROM FORMATEUR WHERE IDF = :id");
    selectQuery.bindValue(":id", idf);

    if (!selectQuery.exec() || !selectQuery.next()) {
        qDebug() << "Erreur: Impossible de récupérer les données existantes pour ID" << idf;
        return false;
    }

    QString oldNom = selectQuery.value(0).toString();
    QString oldEmail = selectQuery.value(1).toString();
    QString oldMdp = selectQuery.value(2).toString();
    QString oldSpecialite = selectQuery.value(3).toString();
    QString oldTel = selectQuery.value(4).toString();
    QString oldAdresse = selectQuery.value(5).toString();

    QString finalNom = this->nomf.isEmpty() ? oldNom : this->nomf;
    QString finalEmail = this->emailf.isEmpty() ? oldEmail : this->emailf;
    QString finalMdp = this->mdpf.isEmpty() ? oldMdp : this->mdpf;
    QString finalSpecialite = this->specialite.isEmpty() ? oldSpecialite : this->specialite;
    QString finalTel = this->telf.isEmpty() ? oldTel : this->telf;
    QString finalAdresse = this->adressef.isEmpty() ? oldAdresse : this->adressef;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE FORMATEUR SET NOMF=:nom, EMAILF=:email, MDPF=:mdp, "
                        "SPECIALITE=:specialite, TELF=:tel, ADRESSEF=:adresse WHERE IDF=:id");
    updateQuery.bindValue(":id", idf);
    updateQuery.bindValue(":nom", finalNom);
    updateQuery.bindValue(":email", finalEmail);
    updateQuery.bindValue(":mdp", finalMdp);
    updateQuery.bindValue(":specialite", finalSpecialite);
    updateQuery.bindValue(":tel", finalTel);
    updateQuery.bindValue(":adresse", finalAdresse);

    if (!updateQuery.exec()) {
        qDebug() << "Erreur modification :" << updateQuery.lastError().text();
        return false;
    }

    qDebug() << "Modification réussie pour ID:" << idf;
    return true;
}

QSqlQueryModel* Formateur::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT TO_CHAR(IDF) AS IDF, NOMF, EMAILF, MDPF, SPECIALITE, TELF, ADRESSEF FROM FORMATEUR ORDER BY IDF ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Mot de passe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Spécialité"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));
    return model;
}

bool Formateur::supprimer(int idf)
{
    QSqlQuery query;
    query.prepare("DELETE FROM FORMATEUR WHERE IDF = :id");
    query.bindValue(":id", idf);

    if (!query.exec()) {
        qDebug() << "Erreur suppression :" << query.lastError().text();
        return false;
    }
    return true;
}

// Recherche
QSqlQueryModel* Formateur::rechercher(const QString &critere, const QString &valeur)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString whereClause;
    QString searchValue = valeur.trimmed();

    if (critere == "ID") {
        whereClause = "IDF = " + searchValue;
    } else if (critere == "Nom") {
        whereClause = "UPPER(NOMF) LIKE UPPER('%" + searchValue + "%')";
    } else if (critere == "Spécialité") {
        whereClause = "UPPER(SPECIALITE) LIKE UPPER('%" + searchValue + "%')";
    } else {
        whereClause = "IDF = " + searchValue;
    }

    QString queryStr = "SELECT TO_CHAR(IDF) AS IDF, NOMF, EMAILF, MDPF, SPECIALITE, TELF, ADRESSEF FROM FORMATEUR WHERE " + whereClause + " ORDER BY IDF ASC";

    qDebug() << "Requête de recherche:" << queryStr;
    model->setQuery(queryStr);

    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors de la recherche:" << model->lastError().text();
        return model;
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Mot de passe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Spécialité"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Adresse"));

    qDebug() << "Recherche réussie - Critère:" << critere << "Valeur:" << valeur << "Résultats:" << model->rowCount();
    return model;
}

// Tri
QSqlQueryModel* Formateur::trier(const QString &critere, const QString &ordre)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString queryStr;

    if (critere == "ID") {
        queryStr = "SELECT TO_CHAR(IDF) AS IDF, NOMF, EMAILF, MDPF, SPECIALITE, TELF, ADRESSEF FROM FORMATEUR ORDER BY IDF " + ordre;
    } else if (critere == "Nom") {
        queryStr = "SELECT TO_CHAR(IDF) AS IDF, NOMF, EMAILF, MDPF, SPECIALITE, TELF, ADRESSEF FROM FORMATEUR ORDER BY NOMF " + ordre;
    } else if (critere == "Spécialité") {
        queryStr = "SELECT TO_CHAR(IDF) AS IDF, NOMF, EMAILF, MDPF, SPECIALITE, TELF, ADRESSEF FROM FORMATEUR ORDER BY SPECIALITE " + ordre;
    } else {
        queryStr = "SELECT TO_CHAR(IDF) AS IDF, NOMF, EMAILF, MDPF, SPECIALITE, TELF, ADRESSEF FROM FORMATEUR ORDER BY IDF ASC";
    }

    model->setQuery(queryStr);

    if (model->lastError().isValid()) {
        qDebug() << "ERREUR SQL dans trier():" << model->lastError().text();
    } else {
        qDebug() << "Requête exécutée avec succès";
        qDebug() << "Nombre de résultats:" << model->rowCount();
    }

    return model;
}
// Nouvelle méthode pour envoyer un SMS
bool Formateur::envoyerSMS(const QString &telephone, const QString &message)
{
    qDebug() << "*****TENTATIVE ENVOI SMS *****";
    qDebug() << "Téléphone:" << telephone;
    qDebug() << "Message:" << message;

    // Validation du numéro de téléphone
    if (!telValide(telephone)) {
        qDebug() << "ERREUR: Numéro de téléphone invalide";
        return false;
    }

    // Validation du message
    if (message.trimmed().isEmpty()) {
        qDebug() << "ERREUR: Message vide";
        return false;
    }

    // Ici, vous pouvez intégrer avec un service SMS comme Twilio, Nexmo, etc.
    // Pour cet exemple, nous allons simuler l'envoi et montrer deux approches

    // APPROCHE 1: Utilisation d'un service SMS externe (exemple avec commande curl)
    /*
    QProcess process;
    QString command = "curl";
    QStringList arguments;
    arguments << "-X" << "POST"
              << "https://api.twilio.com/2010-04-01/Accounts/{VOTRE_COMPTE}/Messages.json"
              << "--data-urlencode" << "From=+1234567890"
              << "--data-urlencode" << "To=+216" + telephone
              << "--data-urlencode" << "Body=" + message
              << "-u" << "{VOTRE_COMPTE_SID}:{VOTRE_AUTH_TOKEN}";

    process.start(command, arguments);
    process.waitForFinished();

    if (process.exitCode() == 0) {
        qDebug() << "SMS envoyé avec succès via service externe";
        return true;
    } else {
        qDebug() << "Erreur envoi SMS:" << process.readAllStandardError();
        return false;
    }
    */

    // APPROCHE 2: Simulation (pour test)
    // Dans un vrai projet, remplacez ceci par l'intégration avec votre fournisseur SMS

    qDebug() << "SIMULATION: SMS envoyé à +216" << telephone;
    qDebug() << "Contenu:" << message;
    qDebug() << "Statut: ENVOYÉ";

    // Pour les besoins de démonstration, nous retournons true
    // En production, retournez le résultat réel de l'API SMS
    return true;
}






//stat
QMap<QString, int> Formateur::statistiques(const QString &critere)
{
    QMap<QString, int> stats;
    QSqlQuery query;

    // Normaliser le critère pour éviter les problèmes :
    // "Spécialité", "specialite", "SPECIALITÉ", etc.
    QString c = critere.toLower();

    // Supprimer les accents
    c.replace("é", "e");
    c.replace("è", "e");
    c.replace("ê", "e");

    qDebug() << "Critère reçu:" << critere << " | Normalisé:" << c;

    // ---------------------------------------------
    //  CRITÈRE : SPECIALITE
    // ---------------------------------------------
    if (c == "specialite") {
        query.prepare("SELECT SPECIALITE, COUNT(*) FROM FORMATEUR GROUP BY SPECIALITE");
    }
    else {
        qDebug() << "ERREUR: Critère non reconnu ->" << critere;
        return stats; // Retourne vide -> pas de crash
    }

    // Exécution de la requête
    if (!query.exec()) {
        qDebug() << "Erreur SQL statistiques :" << query.lastError().text();
        return stats;
    }

    // Lecture des résultats
    while (query.next()) {
        QString label = query.value(0).toString();
        int count = query.value(1).toInt();
        stats[label] = count;
    }

    qDebug() << "STATISTIQUES OBTENUES:" << stats;

    return stats;
}










