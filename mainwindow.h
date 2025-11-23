#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "adherent.h"
#include "employe.h"
#include "arduino.h"

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
    void on_afficher_pie_clicked();
    void on_afficher_bar_clicked();
    void on_btn_upload_cv_clicked();
    void on_btn_recommander_clicked();
    void on_arduino_data_received(QString uid);
    void on_adherent_clicked();
    void on_fonc_adherent_btn_clicked();

    void on_ajouter_employe_btn_clicked();
    void on_modifier_employe_btn_clicked();
    void on_supprimer_employe_btn_clicked();
    void on_rafraichir_employe_btn_clicked();
    void on_rech_employe_btn_clicked();
    void on_tri_up_employe_btn_clicked();
    void on_tri_down_employe_btn_clicked();
    void on_pdf_employe_btn_clicked();
    void on_employe_clicked();

private:
    Ui::MainWindow *ui;

    Adherent A;
    Employe E;
    Arduino Ar;

    QString getSexeFromRadioButtons();
    QString extractTextFromPdf(const QString &filePath);
    QString determinerProfilDepuisCv(const QString &txt);
    bool trouverAtelierPourProfil(const QString &profil, int &ref,
                                  QString &nom, QString &horaire);
    QString dernierCvTexte;
    QByteArray getCvBlobFromDB(int id);


};

#endif // MAINWINDOW_H
