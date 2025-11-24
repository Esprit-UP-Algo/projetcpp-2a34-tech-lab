#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();   // ✅ Déclaration du destructeur


private slots:
    void on_btnAjouter_clicked();
    void on_btnSupprimer_clicked();
    void on_btnModifier_clicked();
    void on_btnEnvoyerMail_clicked();
    void on_btnRechercher_clicked();
    void on_btnExporterPDF_clicked();
    void on_btnFonctionalite_clicked();
    void on_btnMotDePasseOublie_clicked();






private:
    Ui::MainWindow *ui;
    QSqlTableModel *model;

    void creerTable();
    void afficherEmployes();
    Qt::SortOrder ordreTri = Qt::AscendingOrder;
    void appliquerTri();




};



#endif // MAINWINDOW_H

