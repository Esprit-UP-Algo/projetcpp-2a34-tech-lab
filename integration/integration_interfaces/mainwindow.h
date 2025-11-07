#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void on_ajouter_adherent_btn_clicked();
    void on_modifier_adherent_btn_clicked();
    void on_supprimer_adherent_btn_clicked();

private:
    Ui::MainWindow *ui;
    Adherent A;

    QString getSexeFromRadioButtons();
};

#endif // MAINWINDOW_H
