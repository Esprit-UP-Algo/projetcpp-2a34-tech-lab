#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "adherent.h"
#include "employe.h"
#include "arduino.h"
#include "equipement.h"
#include "formateur.h"
#include "atelier.h"


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
void onDistanceMeasured(int distance);
    
    // --- ADHERENTS ---
    void on_ajouter_adherent_btn_clicked();
    void on_modifier_adherent_btn_clicked();
    void on_supprimer_adherent_btn_clicked();
    void on_rech_btn_clicked();
    void on_tri_up_clicked();
    void on_tri_down_clicked();
    void on_raffraichir_adherent_btn_clicked();
    void on_pdf_adherent_btn_clicked();
    void on_afficher_pie_clicked();
    void on_afficher_bar_clicked();
    void on_btn_upload_cv_clicked();
    void on_btn_recommander_clicked();
    void on_arduino_data_received(QString uid);

    void on_fonc_adherent_btn_clicked();
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


    // --- FORMATEUR ---  // AJOUTEZ CES SLOTS
    // CRUD Formateurs
    void on_ajouter_forma_btn_clicked();
    void on_modifier_forma_btn_clicked();
    void on_supprimer_forma_btn_clicked();

    // Métiers Formateurs
    void on_rech_forma_btn_clicked();
    void on_tri_up_forma_clicked();
    void on_tri_down_forma_clicked();
    void on_raffraichir_forma_btn_clicked();
    void on_pdf_forma_btn_clicked();
    void on_afficher_pie_f_clicked();
    void on_afficher_bar_f_clicked();
    // Nouveau slot pour l'envoi de SMS
    void on_envoyer_smsf_btn_clicked();

    void on_fonctionalitef_btn_clicked();




    // --- NAVIGATION STACKEDWIDGET ---
    void on_employe_clicked();
    void on_adherent_clicked();
    void on_Gformateur_clicked();
    void on_ateliers_clicked();
    void on_equipement_clicked();
    void on_fonc_equipement_btn_clicked();
    void on_afficher_pie_equipement_clicked();
    void on_afficher_bar_equipement_clicked();
    // ======================== ATELIERS  ========================
    void on_pushButton_ajouterAtelier_clicked();
    void on_pushButton_modifierAtelier_clicked();
    void on_pushButton_supprimerAteliers_clicked();
    void on_pushButton_annulerAteliers_clicked();
    void on_pushButton_rechercherAtelier_clicked();
    void on_pushButton_trierAteliers_clicked();
    void on_pushButton_calendrier_clicked();
    void on_pushButton_pdf_clicked();
    void on_btnEnvoyerMail_clicked();
    void on_btnExporterPDF_clicked();
    void on_btnFonctionalite_clicked();
    void on_fonctionalitbtn_atelier_clicked();
    void on_afficher_pie_atelier_clicked();
    void arduino_data_received(const QString &line);
private:
    Ui::MainWindow *ui;
    int monitoredReference;
    Adherent A;
    Employe E;
    Equipement Eq;
    Formateur F;
    Atelier Atmp;
    Arduino Ar;
    void initialiserUIAtelier();
    void viderFormulaireAtelier();

    QString getSexeFromRadioButtons();
    QString extractTextFromPdf(const QString &filePath);
    QString determinerProfilDepuisCv(const QString &txt);
    bool trouverAtelierPourProfil(const QString &profil, int &ref,
                                  QString &nom, QString &horaire);
    QString dernierCvTexte;
    
    // Variables pour la gestion du stock
    Arduino *arduino;
    int seuilStockMin;  // Seuil de stock minimum en cm (distance mesurée par le capteur)
    
    // Méthodes pour la gestion du stock
    void initialiserGestionStock();
    void gererAlerteStock(int distance);
    void definirSeuilStock(int seuil);
    QByteArray getCvBlobFromDB(int id);
    void afficherAteliers();


};

#endif // MAINWINDOW_H
