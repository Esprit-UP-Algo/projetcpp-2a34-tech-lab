#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connection.h"
#include "adherent.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_rech_btn_clicked();
    void on_pdf_adherent_btn_clicked();
    void on_del_adherent_btn_clicked();
    void on_trier_btn_clicked();
    void on_acc_btn_clicked();
    void on_fonc_btn_clicked();
    void on_employe_btn_clicked();
    void on_adherents_btn_clicked();
    void on_formateurs_btn_clicked();
    void on_ateliers_btn_clicked();
    void on_equipement_btn_clicked();
    void on_ajouter_adherent_btn_clicked();
    void on_modifier_adherent_btn_clicked();
    void on_annuler_adherent_btn_clicked();

private:
    Ui::MainWindow *ui;
    Adherent Adh;
    void refreshTable();
};

#endif // MAINWINDOW_H
