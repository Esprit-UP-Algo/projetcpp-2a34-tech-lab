#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "adherent.h"
#include "employe.h"
#include "equipement.h"
#include "formateur.h"
#include "atelier.h"
#include <QSqlQueryModel>
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

    //---Formateurs--//

    // CRUD Formateurs
    void on_ajouter_formateur_btn_clicked();
    void on_modifier_formateur_btn_clicked();
    void on_supprimer_formateur_btn_clicked();

    // Métiers Formateurs
    void on_rech_formateur_btn_clicked();
    void on_tri_up_formateur_clicked();
    void on_tri_down_formateur_clicked();
    void on_raffraichir_formateur_btn_clicked();
    void on_pdf_formateur_btn_clicked();



    // --- ATELIERS ---  //
    void on_ajouter_atelier_btn_clicked();
    void on_modifier_atelier_btn_clicked();
    void on_supprimer_atelier_btn_clicked();
    void on_rafraichir_atelier_btn_clicked();
    void on_rech_atelier_btn_clicked();
    void on_tri_up_atelier_clicked();
    void on_tri_down_atelier_clicked();
    void on_stats_atelier_btn_clicked();
    void on_tableView_ateliers_clicked(const QModelIndex &index);













    // --- NAVIGATION STACKEDWIDGET ---
    void on_employe_clicked();
    void on_adherent_clicked();
    void on_Gformateur_clicked();
    void on_ateliers_clicked();
    void on_equipement_clicked();



private:
    Ui::MainWindow *ui;

    Adherent A;
    Employe E;
    Equipement Eq;
    Formateur F;
    QString getSexeFromRadioButtons();
    Atelier At;
    QSqlQueryModel *modelAteliers;
};

#endif // MAINWINDOW_H
