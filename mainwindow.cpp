#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adherent.h"
#include "employe.h"

#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QTextDocument>
#include <QPrinter>
#include <QFileDialog>

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>

#include <QDate>
#include <QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ADHERENTS
    QSqlQueryModel* model = A.afficher();
    ui->tableView->setModel(model);
    // Initialisation dans le constructeur
    QSqlQueryModel* modelE = E.afficher();
    ui->tab_employe->setModel(modelE);
    // Page par défaut (par ex: employé)
    ui->stackedWidget->setCurrentIndex(0);
}
//************************ADHERENT************************
/*****************************************
*************µµµµµµµµµµµµµµµµµµµµµµµ*****HELA µµµµµµ***********/
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
//metiers adhdrents
//*****************


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


//*****************
void MainWindow::on_adherent_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_employe_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


//********************************************************************
/*******************hiba*************************************/

void MainWindow::on_ajouter_employe_btn_clicked()
{
    int id = ui->id_employe->text().toInt();
    QString nom = ui->nom_employe->text();
    QString prenom = ui->prenom_employe->text();
    QString email = ui->email_employe->text();
    QString tel = ui->tel_employe->text();
    QString poste = ui->poste_employe->text();
    QString mdp = ui->mdp_employe->text();

    if (id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID invalide !");
        return;
    }

    Employe emp(id, nom, prenom, email, tel, poste, mdp);

    if (emp.ajouter()) {
        QMessageBox::information(this, "Succès", "Employé ajouté !");
        ui->tab_employe->setModel(E.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout !");
    }
}

void MainWindow::on_modifier_employe_btn_clicked()
{
    int id = ui->id_employe->text().toInt();
    QString nom = ui->nom_employe->text();
    QString prenom = ui->prenom_employe->text();
    QString email = ui->email_employe->text();
    QString tel = ui->tel_employe->text();
    QString poste = ui->poste_employe->text();
    QString mdp = ui->mdp_employe->text();

    if (id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID invalide !");
        return;
    }

    Employe emp(id, nom, prenom, email, tel, poste, mdp);

    if (emp.modifier()) {
        QMessageBox::information(this, "Succès", "Employé modifié !");
        ui->tab_employe->setModel(E.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification !");
    }
}

void MainWindow::on_supprimer_employe_btn_clicked()
{
    int id = ui->id_employe->text().toInt();

    if (id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID invalide !");
        return;
    }

    QMessageBox::StandardButton reply =
        QMessageBox::question(this, "Confirmation",
                              "Supprimer employé ID: " + QString::number(id) + " ?",
                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No)
        return;

    if (E.supprimer(id)) {
        QMessageBox::information(this, "Succès", "Employé supprimé !");
        ui->tab_employe->setModel(E.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression !");
    }
}

void MainWindow::on_rafraichir_employe_btn_clicked()
{
    ui->tab_employe->setModel(E.afficher());
}

void MainWindow::on_rech_employe_btn_clicked()
{
    QString critere = ui->rech_employe_options->currentText();
    QString valeur = ui->lineEdit->text().trimmed();

    if (valeur.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Entrez une valeur !");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    QString query;

    if (critere == "ID")
        query = "SELECT * FROM EMPLOYES WHERE ID = " + valeur;
    else if (critere == "Nom")
        query = "SELECT * FROM EMPLOYES WHERE UPPER(NOM) LIKE UPPER('%" + valeur + "%')";
    else if (critere == "Prénom")
        query = "SELECT * FROM EMPLOYES WHERE UPPER(PRENOM) LIKE UPPER('%" + valeur + "%')";
    else if (critere == "Poste")
        query = "SELECT * FROM EMPLOYES WHERE UPPER(POSTE) LIKE UPPER('%" + valeur + "%')";

    model->setQuery(query);
    ui->tab_employe->setModel(model);
}

void MainWindow::on_tri_up_employe_btn_clicked()
{
    QString critere = ui->trier_employe_options->currentText();

    QString champ;
    if (critere == "ID") champ = "ID";
    else if (critere == "Nom") champ = "NOM";
    else if (critere == "Poste") champ = "POSTE";

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYES ORDER BY " + champ + " ASC");
    ui->tab_employe->setModel(model);
}

void MainWindow::on_tri_down_employe_btn_clicked()
{
    QString critere = ui->trier_employe_options->currentText();

    QString champ;
    if (critere == "ID") champ = "ID";
    else if (critere == "Nom") champ = "NOM";
    else if (critere == "Poste") champ = "POSTE";

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYES ORDER BY " + champ + " DESC");
    ui->tab_employe->setModel(model);
}
void MainWindow::on_pdf_employe_btn_clicked()
{
    QSqlQueryModel* model = E.afficher();  // FIXED

    if (model->rowCount() == 0) {
        QMessageBox::warning(this, "PDF", "Aucun employé à exporter !");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Exporter PDF",
                                                    QDir::homePath() + "/employes.pdf",
                                                    "PDF (*.pdf)");

    if (fileName.isEmpty())
        return;

    QTextDocument doc;
    QString text = "LISTE DES EMPLOYÉS\n\n";

    for (int i = 0; i < model->rowCount(); i++) {
        text += "ID: " + model->data(model->index(i, 0)).toString() + "\n";
        text += "Nom: " + model->data(model->index(i, 1)).toString() + "\n";
        text += "Prénom: " + model->data(model->index(i, 2)).toString() + "\n";
        text += "Email: " + model->data(model->index(i, 3)).toString() + "\n";
        text += "Téléphone: " + model->data(model->index(i, 4)).toString() + "\n";
        text += "Poste: " + model->data(model->index(i, 5)).toString() + "\n";
        text += "---------------------------\n";
    }

    doc.setPlainText(text);

    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    doc.print(&printer);

    QMessageBox::information(this, "PDF", "PDF généré !");
}


//destrc
MainWindow::~MainWindow()
{
    delete ui;
}

