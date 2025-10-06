#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile styleFile(":/style.css");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        app.setStyleSheet(styleSheet);
        qDebug() << "Style CSS chargé avec succès!";
    } else {
        qDebug() << "Erreur: Impossible de charger style.css";
    }

    MainWindow SSC;
    SSC.show();

    return app.exec();
}
