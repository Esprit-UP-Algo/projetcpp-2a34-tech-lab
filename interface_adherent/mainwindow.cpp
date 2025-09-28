#include "mainwindow.h"
#include "ui_mainwindow.h"
/*
 adherent index 2
atelier index 4
equipement index 5
formateur index 6/3
employe index 1
index 0 dashboard*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui->stackedWidget->setCurrentIndex(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
