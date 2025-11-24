#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "formateur.h"



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










    // Nouveau slot pour l'envoi de SMS
    void on_envoyer_sms_btn_clicked();













    // Navigation entre interfaces
    void on_employe_btn_clicked();
    void on_adherents_btn_clicked();
    void on_formateurs_btn_clicked();
    void on_ateliers_btn_clicked();
    void on_equipement_btn_clicked();
    void on_fonctionalite_btn_clicked();
    void on_pushButton_32_clicked();
private:


    Ui::MainWindow *ui;
    Formateur F;  // Changé de Adherent A à Formateur F
};
#endif // MAINWINDOW_H
