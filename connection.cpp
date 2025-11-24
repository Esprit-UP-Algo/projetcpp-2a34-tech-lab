#include "Connection.h"

// ⚠️ Ne PAS appeler addDatabase ici directement !
// Juste déclarer la variable :
QSqlDatabase Connection::db;

Connection::Connection() {
    // Rien ici
}

Connection::~Connection() {
    if (db.isOpen())
        db.close();
}

Connection& Connection::createInstance() {
    static Connection instance;
    return instance;
}

bool Connection::createConnection() {
    // ⚙️ Crée la connexion ici, après QApplication
    if (!db.isValid())
        QSqlDatabase db = QSqlDatabase::database();

    db.setDatabaseName("projet2025");
    db.setUserName("hiba");

    if (db.open()) {
        qDebug() << " Connexion établie";
        return true;
    } else {
        qDebug() << "Échec de la connexion :" << db.lastError().text();
        return false;
    }
}
