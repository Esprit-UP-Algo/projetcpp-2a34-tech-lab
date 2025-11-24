#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "formateur.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QTextDocument>
#include <QPrinter>
#include <QFileDialog>
#include <QDate>
#include <QDir>
#include <QTableWidget>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Afficher les formateurs au démarrage
    QSqlQueryModel* model = Formateur::afficher();
    ui->tableView_formateurs->setModel(model);
}

// CRUD Formateurs
void MainWindow::on_ajouter_formateur_btn_clicked()
{
    qDebug() << "*****BOUTON AJOUTER FORMATEUR CLIQUE *****";

    int idf = ui->id_formateur->text().toInt();
    QString nomf = ui->nom_formateur->text();
    QString emailf = ui->email_formateur->text();
    QString mdpf = ui->mdp_formateur->text();
    QString specialite = ui->specialite_formateur->text();
    QString telf = ui->tel_formateur->text();
    QString adressef = ui->adresse_formateur->text();

    qDebug() << "Valeurs récupérées - ID:" << idf << "Nom:" << nomf << "Email:" << emailf;

    // Validations
    if (idf <= 0) {
        QMessageBox::warning(this, "Erreur", "ID doit être > 0");
        return;
    }

    if (!Formateur::idLen(idf)) {
        QMessageBox::warning(this, "Erreur", "ID doit avoir exactement 8 chiffres");
        return;
    }

    if (Formateur::idExiste(idf)) {
        QMessageBox::warning(this, "Erreur", "ID déjà utilisé");
        return;
    }

    if (nomf.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Nom obligatoire");
        return;
    }

    if (emailf.isEmpty() || !Formateur::emailValide(emailf)) {
        QMessageBox::warning(this, "Erreur", "Email invalide");
        return;
    }

    if (mdpf.isEmpty() || !Formateur::mdpValide(mdpf)) {
        QMessageBox::warning(this, "Erreur", "Mot de passe doit avoir entre 6 et 8 caractères");
        return;
    }

    if (specialite.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Spécialité obligatoire");
        return;
    }

    if (telf.isEmpty() || !Formateur::telValide(telf)) {
        QMessageBox::warning(this, "Erreur", "Téléphone invalide. Doit commencer par 2, 5 ou 9 et avoir 8 chiffres");
        return;
    }

    Formateur f(idf, nomf, emailf, mdpf, specialite, telf, adressef);
    bool test = f.ajouter();

    if (test) {
        QMessageBox::information(this, "Succès", "Formateur ajouté !");
        QSqlQueryModel* model = Formateur::afficher();
        ui->tableView_formateurs->setModel(model);

        // Vider les champs après ajout réussi
        ui->id_formateur->clear();
        ui->nom_formateur->clear();
        ui->email_formateur->clear();
        ui->mdp_formateur->clear();
        ui->specialite_formateur->clear();
        ui->tel_formateur->clear();
        ui->adresse_formateur->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout !");
    }
}

void MainWindow::on_modifier_formateur_btn_clicked()
{
    qDebug() << "*****BOUTON MODIFIER FORMATEUR CLIQUE *****";

    int idf = ui->id_formateur->text().toInt();
    QString nomf = ui->nom_formateur->text();
    QString emailf = ui->email_formateur->text();
    QString mdpf = ui->mdp_formateur->text();
    QString specialite = ui->specialite_formateur->text();
    QString telf = ui->tel_formateur->text();
    QString adressef = ui->adresse_formateur->text();

    qDebug() << "Valeurs récupérées pour modification - ID:" << idf << "Nom:" << nomf;

    if (idf <= 0) {
        QMessageBox::warning(this, "Erreur", "ID doit être > 0");
        return;
    }

    if (!Formateur::idExiste(idf)) {
        QMessageBox::warning(this, "Erreur", "Cet ID n'existe pas dans la base de données");
        return;
    }

    // Validations des champs modifiés
    if (!emailf.isEmpty() && !Formateur::emailValide(emailf)) {
        QMessageBox::warning(this, "Erreur", "Email invalide");
        return;
    }

    if (!mdpf.isEmpty() && !Formateur::mdpValide(mdpf)) {
        QMessageBox::warning(this, "Erreur", "Mot de passe doit avoir entre 6 et 8 caractères");
        return;
    }

    if (!telf.isEmpty() && !Formateur::telValide(telf)) {
        QMessageBox::warning(this, "Erreur", "Téléphone invalide");
        return;
    }

    Formateur f;
    f.setIdf(idf);
    if (!nomf.isEmpty()) f.setNomf(nomf);
    if (!emailf.isEmpty()) f.setEmailf(emailf);
    if (!mdpf.isEmpty()) f.setMdpf(mdpf);
    if (!specialite.isEmpty()) f.setSpecialite(specialite);
    if (!telf.isEmpty()) f.setTelf(telf);
    if (!adressef.isEmpty()) f.setAdressef(adressef);

    bool test = f.modifier();

    if (test) {
        QMessageBox::information(this, "Succès", "Formateur modifié avec succès !");
        QSqlQueryModel* model = Formateur::afficher();
        ui->tableView_formateurs->setModel(model);

        // Vider les champs après modification
        ui->id_formateur->clear();
        ui->nom_formateur->clear();
        ui->email_formateur->clear();
        ui->mdp_formateur->clear();
        ui->specialite_formateur->clear();
        ui->tel_formateur->clear();
        ui->adresse_formateur->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification !");
    }
}

void MainWindow::on_supprimer_formateur_btn_clicked()
{
    int idf = ui->id_formateur->text().toInt();

    if (idf <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un ID valide pour supprimer");
        return;
    }

    if (!Formateur::idExiste(idf)) {
        QMessageBox::warning(this, "Erreur", "Cet ID n'existe pas dans la base de données");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer le formateur ID: " + QString::number(idf) + " ?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }

    bool test = Formateur::supprimer(idf);

    if (test) {
        QMessageBox::information(this, "Succès", "Formateur supprimé avec succès !");
        QSqlQueryModel* model = Formateur::afficher();
        ui->tableView_formateurs->setModel(model);

        // Vider les champs après suppression
        ui->id_formateur->clear();
        ui->nom_formateur->clear();
        ui->email_formateur->clear();
        ui->mdp_formateur->clear();
        ui->specialite_formateur->clear();
        ui->tel_formateur->clear();
        ui->adresse_formateur->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression !");
    }
}




















// Nouvelle fonction pour l'envoi de SMS
void MainWindow::on_envoyer_sms_btn_clicked()
{
    qDebug() << "***** BOUTON ENVOYER SMS CLIQUE *****";

    QString telephone = ui->lineEdit_tel_sms->text().trimmed();
    QString message = ui->textEdit_message_sms->toPlainText().trimmed();

    qDebug() << "Téléphone saisi:" << telephone;
    qDebug() << "Message saisi:" << message;

    // Validations
    if (telephone.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un numéro de téléphone");
        ui->lineEdit_tel_sms->setFocus();
        return;
    }

    if (message.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un message");
        ui->textEdit_message_sms->setFocus();
        return;
    }

    if (!Formateur::telValide(telephone)) {
        QMessageBox::warning(this, "Erreur",
                             "Numéro de téléphone invalide.\n"
                             "Doit commencer par 2, 5 ou 9 et avoir 8 chiffres");
        ui->lineEdit_tel_sms->clear();
        ui->lineEdit_tel_sms->setFocus();
        return;
    }

    // Confirmation avant envoi
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation d'envoi",
                                  "Êtes-vous sûr de vouloir envoyer ce SMS au numéro:\n"
                                      + telephone + " ?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }

    // Envoi du SMS
    bool test = Formateur::envoyerSMS(telephone, message);

    if (test) {
        QMessageBox::information(this, "Succès", "SMS envoyé avec succès !");

        // Vider les champs après envoi réussi
        ui->lineEdit_tel_sms->clear();
        ui->textEdit_message_sms->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'envoi du SMS !");
    }
}










// Métiers Formateurs
void MainWindow::on_rech_formateur_btn_clicked()
{
    // Récupérer le critère depuis un QComboBox
    QString critere = ui->comboBox_recherche_formateur->currentText(); // Doit contenir "ID", "Nom", "Spécialité"
    QString valeur = ui->LineEdit_rech_formateur->text().trimmed();

    if (valeur.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir une valeur à rechercher");
        return;
    }

    // Validation spécifique pour l'ID
    if (critere == "ID") {
        bool ok;
        int idf = valeur.toInt(&ok);
        if (!ok || idf <= 0) {
            QMessageBox::warning(this, "Erreur", "ID doit être un nombre positif");
            ui->LineEdit_rech_formateur->clear();
            ui->LineEdit_rech_formateur->setFocus();
            return;
        }
    }

    QSqlQueryModel* model = Formateur::rechercher(critere, valeur);

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Recherche", "Aucun résultat trouvé pour " + critere + ": " + valeur);
    } else {
        QMessageBox::information(this, "Recherche", QString::number(model->rowCount()) + " résultat(s) trouvé(s)");
        ui->tableView_formateurs->setModel(model);
    }
    ui->LineEdit_rech_formateur->clear();
}
void MainWindow::on_tri_up_formateur_clicked()
{
    QString critere = ui->comboBox_tri_formateur->currentText();
    QString ordre = "ASC";
    QSqlQueryModel* model = Formateur::trier(critere, ordre);
    ui->tableView_formateurs->setModel(model);
    QMessageBox::information(this, "Tri", "Données triées par " + critere + " (Croissant)");
}

void MainWindow::on_tri_down_formateur_clicked()
{
    QString critere = ui->comboBox_tri_formateur->currentText();
    QString ordre = "DESC";
    QSqlQueryModel* model = Formateur::trier(critere, ordre);
    ui->tableView_formateurs->setModel(model);
    QMessageBox::information(this, "Tri", "Données triées par " + critere + " (Décroissant)");
}

void MainWindow::on_raffraichir_formateur_btn_clicked()
{
    QSqlQueryModel* model = Formateur::afficher();
    ui->tableView_formateurs->setModel(model);
    QMessageBox::information(this, "Rafraîchissement", "Liste des formateurs actualisée");
}

void MainWindow::on_pdf_formateur_btn_clicked()
{
    QSqlQueryModel* model = Formateur::afficher();
    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Export PDF", "Aucune donnée à exporter");
        return;
    }

    QString content;
    content += "LISTE DES FORMATEURS\n";
    content += "===================\n\n";
    content += "Exporté le : " + QDate::currentDate().toString("dd/MM/yyyy") + "\n";
    content += "Nombre de formateurs : " + QString::number(model->rowCount()) + "\n\n";

    for (int row = 0; row < model->rowCount(); ++row) {
        content += "▪ Formateur " + QString::number(row + 1) + ":\n";

        QString idf = model->data(model->index(row, 0)).toString();
        QString nomf = model->data(model->index(row, 1)).toString();
        QString emailf = model->data(model->index(row, 2)).toString();
        QString specialite = model->data(model->index(row, 4)).toString();
        QString telf = model->data(model->index(row, 5)).toString();
        QString adressef = model->data(model->index(row, 6)).toString();

        content += "   ID : " + idf + "\n";
        content += "   Nom : " + nomf + "\n";
        content += "   Email : " + emailf + "\n";
        content += "   Spécialité : " + specialite + "\n";
        content += "   Téléphone : " + telf + "\n";
        content += "   Adresse : " + adressef + "\n\n";
    }

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Exporter en PDF",
                                                    QDir::homePath() + "/formateurs_" + QDate::currentDate().toString("yyyyMMdd") + ".pdf",
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

// Navigation entre interfaces (inchangé)
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

void MainWindow::on_fonctionalite_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_pushButton_32_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


MainWindow::~MainWindow()
{
    delete ui;
}
