#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // ✅ Vérifier si le pilote SQLite est disponible
    if (!QSqlDatabase::isDriverAvailable("QSQLITE")) {
        qCritical() << "Pilote SQLite non disponible !";
        return -1;
    }

    // ✅ Créer et afficher la fenêtre principale
    MainWindow w;
    w.show();

    return a.exec();
}




