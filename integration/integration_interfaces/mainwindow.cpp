#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rech_btn_clicked()
{

}


void MainWindow::on_pdf_adherent_btn_clicked()
{

}


void MainWindow::on_del_adherent_btn_clicked()
{

}


void MainWindow::on_trier_btn_clicked()
{

}


void MainWindow::on_acc_btn_clicked()
{

}


void MainWindow::on_fonc_btn_clicked()
{

}


void MainWindow::on_employe_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_adherents_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
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

