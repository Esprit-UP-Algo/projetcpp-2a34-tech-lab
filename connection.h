#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

class Connection
{
private:
    static QSqlDatabase db;
    Connection(); // constructeur privé

public:
    ~Connection();
    static Connection& createInstance();
    static bool createConnection();
};

#endif // CONNECTION_H


