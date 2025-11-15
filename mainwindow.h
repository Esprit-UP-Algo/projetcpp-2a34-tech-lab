#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "adherent.h"
#include "employe.h"
#include "equipement.h"
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
    // --- ADHERENTS ---
    void on_ajouter_adherent_btn_clicked();
    void on_modifier_adherent_btn_clicked();
    void on_supprimer_adherent_btn_clicked();
    void on_rech_btn_clicked();
    void on_tri_up_clicked();
    void on_tri_down_clicked();
    void on_raffraichir_adherent_btn_clicked();
    void on_pdf_adherent_btn_clicked();

    //   EMPLOYES********
    void on_ajouter_employe_btn_clicked();
    void on_modifier_employe_btn_clicked();
    void on_supprimer_employe_btn_clicked();
    void on_rafraichir_employe_btn_clicked();
    void on_rech_employe_btn_clicked();
    void on_tri_up_employe_btn_clicked();
    void on_tri_down_employe_btn_clicked();
    void on_pdf_employe_btn_clicked();

    // --- EQUIPEMENTS ---  // AJOUTEZ CES SLOTS
    void on_ajouter_equipement_btn_clicked();
    void on_modifier_equipement_btn_clicked();
    void on_supprimer_equipement_btn_clicked();
    void on_rafraichir_equipement_btn_clicked();
    void on_rech_equipement_btn_clicked();
    void on_tri_up_equipement_clicked();
    void on_tri_down_equipement_clicked();
    void on_pdf_equipement_btn_clicked();
    void load_equipement_data();
    void clear_equipement_form();

    // --- NAVIGATION STACKEDWIDGET ---
    void on_employe_clicked();
    void on_adherent_clicked();
    /*void on_formateurs_clicked();
    void on_ateliers_clicked();*/
    void on_equipement_clicked();


private:
    Ui::MainWindow *ui;

    Adherent A;
    Employe E;
    Equipement Eq;
    QString getSexeFromRadioButtons();
};

#endif // MAINWINDOW_H
