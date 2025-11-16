// connection.cpp
#include "connection.h"

Connection::Connection()
{
    db = QSqlDatabase::addDatabase("QODBC");
}

Connection::~Connection()
{
    if (db.isOpen()) db.close();
}

Connection& Connection::createInstance()
{
    static Connection instance;
    return instance;
}

bool Connection::createConnect()
{
    db.setDatabaseName("Sources_Projet24");
    db.setUserName("zeineb");
    db.setPassword("zeineb25");

    if (db.open()) {
        qDebug() << "Connexion établie";
        return true;
    }
    qDebug() << "Échec connexion:" << db.lastError().text();
    return false;
}
