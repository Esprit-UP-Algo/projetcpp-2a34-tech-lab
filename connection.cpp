#include "connection.h"

Connection::Connection() : connected(false)
{
}

Connection& Connection::getInstance()
{
    static Connection instance;
    return instance;
}

bool Connection::connect()
{
    // Éviter les connexions multiples
    if (connected && db.isOpen()) {
        qDebug() << "Déjà connecté à la base de données";
        return true;
    }

    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projet_2A2526");
    db.setUserName("yassine");
    db.setPassword("esprit22");

    if (db.open()) {
        connected = true;
        qDebug() << "✅ FÉLICITATIONS! Connexion réussie à la base de données Oracle";
        qDebug() << "Driver:" << db.driverName();
        qDebug() << "Base de données:" << db.databaseName();

        // Tester la connexion avec une requête simple
        QSqlQuery query;
        if (query.exec("SELECT sys_context('USERENV', 'SESSION_USER') FROM dual") && query.next()) {
            qDebug() << "Utilisateur connecté:" << query.value(0).toString();
        } else {
            qDebug() << "Test de requête échoué:" << query.lastError().text();
        }

    } else {
        connected = false;
        QString error = db.lastError().text();
        qDebug() << "❌ Erreur de connexion:" << error;

        // Message d'erreur plus détaillé
        QMessageBox::critical(nullptr, "Erreur de connexion",
                              "Impossible de se connecter à la base de données.\n"
                              "Erreur: " + error + "\n\n"
                                            "Vérifiez:\n"
                                            "• Le nom de la source de données ODBC\n"
                                            "• Le nom d'utilisateur et mot de passe\n"
                                            "• Que le service Oracle est démarré");
    }

    return connected;
}

void Connection::disconnect()
{
    if (db.isOpen()) {
        db.close();
        connected = false;
        qDebug() << "Déconnexion de la base de données";
    }
}

bool Connection::isConnected() const
{
    return connected && db.isOpen();
}
