#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adherent.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QTextDocument>
#include <QTextCursor>
#include <QPrinter>
#include <QFileDialog>
#include <QDate>
#include <QColor>
#include <QSqlQueryModel>
#include <QTextTable>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlQueryModel* model = A.afficher();
    ui->tableView->setModel(model);
}
QString MainWindow::getSexeFromRadioButtons() {
    if (ui->garcon->isChecked()) {
        return "Garçon";
    }
    if (ui->fille->isChecked()) {
        return "Fille";
    }
    return "";
}
//les crud
void MainWindow::on_ajouter_adherent_btn_clicked()
{
    qDebug() << "*****BOUTON AJOUTER CLIQUE *****";
    int id = ui->id_adherent->text().toInt();
    QString nom = ui->nom_adherent->text();
    QString prenom = ui->prenom_adherent->text();
    QDate daten = ui->daten_adherent->date();
    QString email = ui->email_adherent->text();
    QString tel = ui->tel_adherent->text();
    QString adr = ui->adr_adherent->text();
    QString sexe = getSexeFromRadioButtons();

    qDebug() << "Valeurs récupérées - ID:" << id << "Nom:" << nom << "Prénom:" << prenom << "Sexe:" << sexe;
    if (id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID doit être > 0");
        return;
    }
    if (!Adherent::idLen(id)) {
        QMessageBox::warning(this, "Erreur", "ID doit avoir exactement 8 chiffres");
        return;
    }
    if (Adherent::idExiste(id)) {
        QMessageBox::warning(this, "Erreur", "ID déjà utilisé");
        return;
    }
    if (nom.isEmpty() || prenom.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Nom et prénom obligatoires");
        return;
    }
    if (sexe.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Sexe obligatoire");
        return;
    }

    Adherent a(id, nom, prenom, daten, email, tel, adr, sexe);
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
    qDebug() << "*****BOUTON MODIFIER CLIQUE *****";
    int id = ui->id_adherent->text().toInt();
    QString nom = ui->nom_adherent->text();
    QString prenom = ui->prenom_adherent->text();
    QDate daten = ui->daten_adherent->date();
    QString email = ui->email_adherent->text();
    QString tel = ui->tel_adherent->text();
    QString adr = ui->adr_adherent->text();
    QString sexe = getSexeFromRadioButtons();

    qDebug() << "Valeurs récupérées pour modification - ID:" << id << "Nom:" << nom << "Prénom:" << prenom << "Sexe:" << sexe;

    if (id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID doit être > 0");
        return;
    }

    if (!Adherent::idExiste(id)) {
        QMessageBox::warning(this, "Erreur", "Cet ID n'existe pas dans la base de données");
        return;
    }
    if (!nom.isEmpty() && nom.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Nom invalide");
        return;
    }

    if (!prenom.isEmpty() && prenom.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Prénom invalide");
        return;
    }

    if (!email.isEmpty() && !Adherent::emailValide(email)) {
        QMessageBox::warning(this, "Erreur", "Email invalide");
        return;
    }

    if (!tel.isEmpty() && !Adherent::telValide(tel)) {
        QMessageBox::warning(this, "Erreur", "Téléphone invalide");
        return;
    }
    Adherent a;
    a.setId(id);
    if (!nom.isEmpty()) a.setNom(nom);
    if (!prenom.isEmpty()) a.setPrenom(prenom);
    if (daten.isValid()) a.setDateN(daten);
    if (!email.isEmpty()) a.setEmail(email);
    if (!tel.isEmpty()) a.setTel(tel);
    if (!adr.isEmpty()) a.setAdr(adr);
    if (!sexe.isEmpty()) a.setSexe(sexe);
    bool test = a.modifier();

    if (test) {
        QMessageBox::information(this, "Succès", "Adhérent modifié avec succès !");
        QSqlQueryModel* model = a.afficher();
        ui->tableView->setModel(model);
        ui->id_adherent->clear();
        ui->nom_adherent->clear();
        ui->prenom_adherent->clear();
        ui->daten_adherent->setDate(QDate::currentDate());
        ui->email_adherent->clear();
        ui->tel_adherent->clear();
        ui->adr_adherent->clear();
        ui->garcon->setAutoExclusive(false);
        ui->garcon->setChecked(false);
        ui->fille->setAutoExclusive(false);
        ui->fille->setChecked(false);
        ui->garcon->setAutoExclusive(true);
        ui->fille->setAutoExclusive(true);
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification !");
    }
}

void MainWindow::on_supprimer_adherent_btn_clicked()
{
    int id = ui->id_adherent->text().toInt();

    if (id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un ID valide pour supprimer");
        return;
    }

    if (!Adherent::idExiste(id)) {
        QMessageBox::warning(this, "Erreur", "Cet ID n'existe pas dans la base de données");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer l'adhérent ID: " + QString::number(id) + " ?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }

    Adherent a;
    bool test = a.supprimer(id);

    if (test) {
        QMessageBox::information(this, "Succès", "Adhérent supprimé avec succès !");
        QSqlQueryModel* model = a.afficher();
        ui->tableView->setModel(model);
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression !");
    }
}
//les metiers
void MainWindow::on_rech_btn_clicked()
{
    QString critere = ui->comboBox_recherche->currentText();
    QString valeur = ui->LineEdit_rech_adh->text().trimmed();

    if (valeur.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir une valeur à rechercher");
        return;
    }

    if (critere == "ID") {
        bool ok;
        int id = valeur.toInt(&ok);
        if (!ok || id <= 0) {
            QMessageBox::warning(this, "Erreur", "ID doit être un nombre positif");
            ui->LineEdit_rech_adh->clear();
            ui->LineEdit_rech_adh->setFocus();
            return;
        }
    } else if (critere == "Téléphone") {
        if (!Adherent::telValide(valeur) && valeur.length() > 0) {
            QMessageBox::warning(this, "Erreur", "Format de téléphone invalide. Doit commencer par 2, 5 ou 9 et avoir 8 chiffres");
            ui->LineEdit_rech_adh->clear();
            ui->LineEdit_rech_adh->setFocus();
            return;
        }
    }
    QSqlQueryModel* model = A.rechercher(critere, valeur);

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Recherche", "Aucun résultat trouvé pour " + critere + ": " + valeur);
    } else {
        QMessageBox::information(this, "Recherche", QString::number(model->rowCount()) + " résultat(s) trouvé(s)");
        ui->tableView->setModel(model);
    }
    ui->LineEdit_rech_adh->clear();
}
void MainWindow::on_tri_up_clicked()
{
    QString critere = ui->comboBox_tri->currentText();
    QString ordre = "ASC";
    QSqlQueryModel* model = A.trier(critere, ordre);
    ui->tableView->setModel(model);
    QMessageBox::information(this, "Tri", "Données triées par " + critere + " (Croissant)");
}

void MainWindow::on_tri_down_clicked()
{
    QString critere = ui->comboBox_tri->currentText();
    QString ordre = "DESC";
    QSqlQueryModel* model = A.trier(critere, ordre);
    ui->tableView->setModel(model);
    QMessageBox::information(this, "Tri", "Données triées par " + critere + " (Décroissant)");
}

//exportation en pdf
void MainWindow::on_pdf_adherent_btn_clicked()
{
    QSqlQueryModel* model = A.afficher();
    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Export PDF", "Aucune donnée à exporter");
        return;
    }

    QString content;
    content += "LISTE DES ADHÉRENTS\n";
    content += "===================\n\n";
    content += "Exporté le : " + QDate::currentDate().toString("dd/MM/yyyy") + "\n";
    content += "Nombre d'adhérents : " + QString::number(model->rowCount()) + "\n\n";

    for (int row = 0; row < model->rowCount(); ++row) {
        content += "▪ Adhérent " + QString::number(row + 1) + ":\n";

        QString nom = model->data(model->index(row, 1)).toString();
        QString prenom = model->data(model->index(row, 2)).toString();
        QString daten = model->data(model->index(row, 3)).toString();
        QString email = model->data(model->index(row, 4)).toString();
        QString tel = model->data(model->index(row, 5)).toString();
        QString adr = model->data(model->index(row, 6)).toString();

        content += "   Nom : " + nom + " " + prenom + "\n";
        content += "   Date de naissance : " + daten + "\n";
        content += "   Email : " + email + "\n";
        content += "   Téléphone : " + tel + "\n";
        content += "   Adresse : " + adr + "\n\n";
    }

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Exporter en PDF",
                                                    QDir::homePath() + "/adherents_" + QDate::currentDate().toString("yyyyMMdd") + ".pdf",
                                                    "Fichiers PDF (*.pdf)");

    if (!fileName.isEmpty()) {
        QTextDocument document;
        document.setPlainText(content);

        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);

        document.print(&printer);
        QMessageBox::information(this, "Succès", "PDF généré avec succès !\n" + fileName);
    }
}
void MainWindow::on_raffraichir_adherent_btn_clicked()
{
    QSqlQueryModel* model = A.afficher();
    ui->tableView->setModel(model);
    QMessageBox::information(this, "Rafraîchissement", "Liste des adhérents actualisée");
}
//destrc
MainWindow::~MainWindow()
{
    delete ui;
}
