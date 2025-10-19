#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

class Connection
{
public:
    Connection();
    bool connect();
    void disconnect();
    bool isConnected() const;
    static Connection& getInstance();

private:
    QSqlDatabase db;
    bool connected;
};

#endif // CONNECTION_H
