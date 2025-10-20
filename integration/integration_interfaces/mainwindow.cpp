#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "connection.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QSqlQueryModel>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refreshTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshTable()
{

    QSqlQueryModel *model = Adh.afficher();

    if (model) {

        ui->table_adherent->clear();
        ui->table_adherent->setRowCount(0);
        ui->table_adherent->setColumnCount(model->columnCount());
        QStringList headers;
        for (int col = 0; col < model->columnCount(); ++col) {
            headers << model->headerData(col, Qt::Horizontal).toString();
        }
        ui->table_adherent->setHorizontalHeaderLabels(headers);

        for (int row = 0; row < model->rowCount(); ++row) {
            ui->table_adherent->insertRow(row);
            for (int col = 0; col < model->columnCount(); ++col) {
                QTableWidgetItem *item = new QTableWidgetItem(
                    model->data(model->index(row, col)).toString());
                ui->table_adherent->setItem(row, col, item);
            }
        }

        delete model;
    }
}
void MainWindow::on_ajouter_adherent_btn_clicked()
{
    int id = ui->id_adherent->text().toInt();
    QString nom = ui->nom_adherent->text();
    QString prenom = ui->prenom_adherent->text();
    QString date_naissance = ui->daten_adherent->text();
    QString email = ui->email_adherent->text();
    QString telephone = ui->tel_adherent->text();
    QString adresse = ui->adresse_adherent->text();

    Adherent A(id, nom, prenom, date_naissance, email, telephone, adresse);
    bool test = A.ajouter();

    if(test) {
        refreshTable(); // ACTUALISER
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\nClick Cancel to exit."), QMessageBox::Cancel);
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_modifier_adherent_btn_clicked()
{
    int id = ui->id_adherent->text().toInt();
    QString nom = ui->nom_adherent->text();
    QString prenom = ui->prenom_adherent->text();
    QString date_naissance = ui->daten_adherent->text();
    QString email = ui->email_adherent->text();
    QString telephone = ui->tel_adherent->text();
    QString adresse = ui->adresse_adherent->text();

    Adherent A(id, nom, prenom, date_naissance, email, telephone, adresse);
    bool test = A.modifier(id);

    if(test) {
        refreshTable();
        QMessageBox::information(this, "Succès", "Adhérent modifié avec succès!");
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la modification!");
    }
}

// SUPPRIMER ADHERENT
void MainWindow::on_del_adherent_btn_clicked()
{
    int id = ui->id_adherent->text().toInt();
    bool test = Adh.supprimer(id);

    if(test) {
        refreshTable(); // ACTUALISER
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée\nClick Cancel to exit."), QMessageBox::Cancel);
    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}

// ANNULER
void MainWindow::on_annuler_adherent_btn_clicked()
{
    ui->id_adherent->clear();
    ui->nom_adherent->clear();
    ui->prenom_adherent->clear();
    ui->daten_adherent->clear();
    ui->email_adherent->clear();
    ui->tel_adherent->clear();
    ui->adresse_adherent->clear();
}

void MainWindow::on_rech_btn_clicked()
{
    // Recherche...
}

void MainWindow::on_pdf_adherent_btn_clicked()
{
    qDebug() << "Génération PDF adhérent...";
}

void MainWindow::on_trier_btn_clicked()
{
    qDebug() << "Tri des adhérents...";
}

void MainWindow::on_acc_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_fonc_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_employe_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_adherents_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    refreshTable();
}

void MainWindow::on_formateurs_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_ateliers_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_equipement_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}
