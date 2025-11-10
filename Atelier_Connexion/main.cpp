#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Connection& c = Connection::createInstance();
    if (c.createConnect()) {
        MainWindow w;
        w.show();
        QMessageBox::information(nullptr, "Connexion", "Base connectée.");
        return a.exec();
    } else {
        QMessageBox::critical(nullptr, "Erreur", "Connexion échouée.");
        return -1;
    }
}
