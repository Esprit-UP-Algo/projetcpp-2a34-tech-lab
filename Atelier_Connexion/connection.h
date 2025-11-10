// connection.h
#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>

class Connection
{
public:
    static Connection& createInstance();
    bool createConnect();

private:
    QSqlDatabase db;
    Connection();
    ~Connection();
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
};

#endif // CONNECTION_H
