#include "client.h"

Client::Client() : id(0) {}

Client::Client(int id, const QString& nom, const QString& prenom, const QString& email,
               const QString& telephone, const QString& adresse, const QDate& dateNaissance)
    : id(id), nom(nom), prenom(prenom), email(email), telephone(telephone),
    adresse(adresse), dateNaissance(dateNaissance) {}

// Getters implementation
int Client::getId() const { return id; }
QString Client::getNom() const { return nom; }
QString Client::getPrenom() const { return prenom; }
QString Client::getEmail() const { return email; }
QString Client::getTelephone() const { return telephone; }
QString Client::getAdresse() const { return adresse; }
QDate Client::getDateNaissance() const { return dateNaissance; }

// Setters implementation
void Client::setId(int id) { this->id = id; }
void Client::setNom(const QString& nom) { this->nom = nom; }
void Client::setPrenom(const QString& prenom) { this->prenom = prenom; }
void Client::setEmail(const QString& email) { this->email = email; }
void Client::setTelephone(const QString& telephone) { this->telephone = telephone; }
void Client::setAdresse(const QString& adresse) { this->adresse = adresse; }
void Client::setDateNaissance(const QDate& dateNaissance) { this->dateNaissance = dateNaissance; }

// CRUD: Create (Ajouter)
bool Client::ajouter() {
    QSqlQuery query;

    query.prepare("INSERT INTO clients (nom, prenom, email, telephone, adresse, date_naissance) "
                  "VALUES (:nom, :prenom, :email, :telephone, :adresse, :date_naissance)");

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":adresse", adresse);
    query.bindValue(":date_naissance", dateNaissance);

    if (query.exec()) {
        id = query.lastInsertId().toInt();
        return true;
    } else {
        qDebug() << "Erreur lors de l'ajout du client:" << query.lastError().text();
        return false;
    }
}

// CRUD: Delete (Supprimer)
bool Client::supprimer(int id) {
    QSqlQuery query;

    query.prepare("DELETE FROM clients WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erreur lors de la suppression du client:" << query.lastError().text();
        return false;
    }
}

// CRUD: Update (Modifier)
bool Client::modifier() {
    QSqlQuery query;

    query.prepare("UPDATE clients SET nom = :nom, prenom = :prenom, email = :email, "
                  "telephone = :telephone, adresse = :adresse, date_naissance = :date_naissance "
                  "WHERE id = :id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":adresse", adresse);
    query.bindValue(":date_naissance", dateNaissance);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erreur lors de la modification du client:" << query.lastError().text();
        return false;
    }
}

// CRUD: Read - Get by ID
Client* Client::getById(int id) {
    QSqlQuery query;

    query.prepare("SELECT * FROM clients WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        return new Client(
            query.value("id").toInt(),
            query.value("nom").toString(),
            query.value("prenom").toString(),
            query.value("email").toString(),
            query.value("telephone").toString(),
            query.value("adresse").toString(),
            query.value("date_naissance").toDate()
            );
    }

    return nullptr;
}

// CRUD: Read - Get all clients
QList<Client*> Client::getAll() {
    QList<Client*> clients;
    QSqlQuery query("SELECT * FROM clients ORDER BY nom, prenom");

    while (query.next()) {
        Client* client = new Client(
            query.value("id").toInt(),
            query.value("nom").toString(),
            query.value("prenom").toString(),
            query.value("email").toString(),
            query.value("telephone").toString(),
            query.value("adresse").toString(),
            query.value("date_naissance").toDate()
            );
        clients.append(client);
    }

    return clients;
}

// Validation methods
bool Client::isValidEmail() const {
    return email.contains('@') && email.contains('.');
}

bool Client::isValidTelephone() const {
    // Simple validation - you can enhance this with regex
    return telephone.length() >= 8;
}
