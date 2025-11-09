#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adherent.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlQueryModel* model = A.afficher();
    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_adherent_btn_clicked()
{
    int id = ui->id_adherent->text().toInt();
    QString nom = ui->nom_adherent->text();
    QString prenom = ui->prenom_adherent->text();
    QDate daten = ui->daten_adherent->date();
    QString email = ui->email_adherent->text();
    QString tel = ui->tel_adherent->text();
    QString adr = ui->adr_adherent->text();

    Adherent a(id, nom, prenom, daten, email, tel, adr);

    if (!a.setId(id) || !a.setNom(nom) || !a.setPrenom(prenom) ||
        !a.setDateN(daten) || !a.setEmail(email) || !a.setTel(tel)) {
        QMessageBox::warning(this, "Erreur", "Veuillez vérifier les champs !");
        return;
    }
    a.setAdr(adr);

    bool test = a.ajouter();

    if (test) {
        QMessageBox::information(this, "Succès", "Adhérent ajouté !");
        QSqlQueryModel* model = a.afficher();
        ui->tableView->setModel(model);
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout !");
    }
}

void MainWindow::on_modifier_adherent_btn_clicked()
{
    int id = ui->id_adherent->text().toInt();
    QString nom = ui->nom_adherent->text();
    QString prenom = ui->prenom_adherent->text();
    QDate daten = ui->daten_adherent->date();
    QString email = ui->email_adherent->text();
    QString tel = ui->tel_adherent->text();
    QString adr = ui->adr_adherent->text();

    Adherent a(id, nom, prenom, daten, email, tel, adr);
    if (!a.setId(id)) {
        QMessageBox::warning(this, "Erreur", "ID invalide (doit être > 0).");
        return;
    }
    if (!a.setNom(nom)) {
        QMessageBox::warning(this, "Erreur", "Nom vide.");
        return;
    }
    if (!a.setPrenom(prenom)) {
        QMessageBox::warning(this, "Erreur", "Prénom vide.");
        return;
    }
    if (!a.setDateN(daten)) {
        QMessageBox::warning(this, "Erreur", "Date invalide (ne doit pas dépasser aujourd'hui).");
        return;
    }
    if (!a.setEmail(email)) {
        QMessageBox::warning(this, "Erreur", "Email invalide.");
        return;
    }
    if (!a.setTel(tel)) {
        QMessageBox::warning(this, "Erreur", "Téléphone invalide (8 à 12 chiffres, pas de +216).");
        return;
    }
    a.setAdr(adr);

    bool test = a.modifier();

    if (test) {
        QMessageBox::information(this, "Succès", "Adhérent modifié !");
        QSqlQueryModel* model = a.afficher();
        ui->tableView->setModel(model);
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification !");
    }
}
