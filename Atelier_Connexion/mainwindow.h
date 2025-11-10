#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "atelier.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_annuler_clicked();
    void on_pushButton_rechercher_clicked();
    void on_pushButton_trier_clicked();
    void on_pushButton_stat_clicked();  // NOUVEAU

private:
    Ui::MainWindow *ui;
    Atelier Atmp;

    void afficherAteliers();
    bool validerChamps();
    bool validerReference(const QString &ref);
    bool validerNom(const QString &nom);
    bool validerCapacite(const QString &cap);
    bool validerJour(const QString &jour);
    bool validerHoraire(const QString &horaire);
    bool validerDuree(const QString &duree);
    bool validerNumeroSalle(const QString &num);
};

#endif // MAINWINDOW_H
