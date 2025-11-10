#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "atelier.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Configuration du tableau
    ui->TableWidget->setColumnCount(7);
    ui->TableWidget->setHorizontalHeaderLabels({
        "Référence", "Nom d'atelier", "Capacité", "Jour",
        "Durée", "Numéro de salle", "Horaire"
    });

    // Validateurs
    ui->LineEdit_cap->setValidator(new QIntValidator(1, 1000, this));
    ui->LineEdit_d->setValidator(new QIntValidator(1, 24, this));
    ui->LineEdit_ns->setValidator(new QIntValidator(1, 999, this));

    // Affichage initial
    afficherAteliers();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::afficherAteliers()
{
    ui->TableWidget->setRowCount(0);
    QSqlQueryModel* model = Atmp.afficher();

    if (model) {
        for (int i = 0; i < model->rowCount(); ++i) {
            int row = ui->TableWidget->rowCount();
            ui->TableWidget->insertRow(row);
            for (int col = 0; col < 7; ++col) {
                ui->TableWidget->setItem(row, col,
                                         new QTableWidgetItem(model->record(i).value(col).toString()));
            }
        }
        delete model;
    }
    ui->TableWidget->resizeColumnsToContents();
}

// === RECHERCHE ===
void MainWindow::on_pushButton_rechercher_clicked()
{
    QString valeur = ui->lineEdit_recherche->text().trimmed();
    if (valeur.isEmpty()) {
        afficherAteliers();
        return;
    }

    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    bool isNumber = false;
    int num = valeur.toInt(&isNumber);
    QString sql;

    if (isNumber && num > 0) {
        sql = "SELECT REFERENCE, NOM_ATELIER, CAPACITE, JOUR, DUREE, NUM_SALLE, HORAIRE "
              "FROM ATELIER WHERE NUM_SALLE = :val ORDER BY REFERENCE";
        query.prepare(sql);
        query.bindValue(":val", num);
    } else {
        sql = "SELECT REFERENCE, NOM_ATELIER, CAPACITE, JOUR, DUREE, NUM_SALLE, HORAIRE "
              "FROM ATELIER "
              "WHERE LOWER(NOM_ATELIER) LIKE LOWER(:val) "
              " OR LOWER(JOUR) LIKE LOWER(:val) "
              "ORDER BY REFERENCE";
        query.prepare(sql);
        query.bindValue(":val", "%" + valeur + "%");
    }

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, "Référence");
        model->setHeaderData(1, Qt::Horizontal, "Nom d'atelier");
        model->setHeaderData(2, Qt::Horizontal, "Capacité");
        model->setHeaderData(3, Qt::Horizontal, "Jour");
        model->setHeaderData(4, Qt::Horizontal, "Durée");
        model->setHeaderData(5, Qt::Horizontal, "Numéro de salle");
        model->setHeaderData(6, Qt::Horizontal, "Horaire");

        ui->TableWidget->setRowCount(0);
        for (int i = 0; i < model->rowCount(); ++i) {
            int row = ui->TableWidget->rowCount();
            ui->TableWidget->insertRow(row);
            for (int col = 0; col < 7; ++col) {
                ui->TableWidget->setItem(row, col,
                                         new QTableWidgetItem(model->record(i).value(col).toString()));
            }
        }
        delete model;
        ui->TableWidget->resizeColumnsToContents();
    } else {
        QMessageBox::warning(this, "Erreur", "Recherche échouée : " + query.lastError().text());
    }
}

// === TRI ===
void MainWindow::on_pushButton_trier_clicked()
{
    QString critere = ui->comboBox_trier->currentText();
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    QString sql = "SELECT REFERENCE, NOM_ATELIER, CAPACITE, JOUR, DUREE, NUM_SALLE, HORAIRE FROM ATELIER";

    if (critere == "jour") {
        sql += " ORDER BY "
               "CASE JOUR "
               "WHEN 'Lundi' THEN 1 "
               "WHEN 'Mardi' THEN 2 "
               "WHEN 'Mercredi' THEN 3 "
               "WHEN 'Jeudi' THEN 4 "
               "WHEN 'Vendredi' THEN 5 "
               "WHEN 'Samedi' THEN 6 "
               "WHEN 'Dimanche' THEN 7 "
               "END";
    } else if (critere == "capacité") {
        sql += " ORDER BY CAPACITE DESC";
    } else if (critere == "horaire") {
        sql += " ORDER BY HORAIRE DESC";
    } else {
        sql += " ORDER BY REFERENCE DESC";
    }

    if (query.exec(sql)) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, "Référence");
        model->setHeaderData(1, Qt::Horizontal, "Nom d'atelier");
        model->setHeaderData(2, Qt::Horizontal, "Capacité");
        model->setHeaderData(3, Qt::Horizontal, "Jour");
        model->setHeaderData(4, Qt::Horizontal, "Durée");
        model->setHeaderData(5, Qt::Horizontal, "Numéro de salle");
        model->setHeaderData(6, Qt::Horizontal, "Horaire");

        ui->TableWidget->setRowCount(0);
        for (int i = 0; i < model->rowCount(); ++i) {
            int row = ui->TableWidget->rowCount();
            ui->TableWidget->insertRow(row);
            for (int col = 0; col < 7; ++col) {
                ui->TableWidget->setItem(row, col,
                                         new QTableWidgetItem(model->record(i).value(col).toString()));
            }
        }
        delete model;
        ui->TableWidget->resizeColumnsToContents();
    } else {
        QMessageBox::warning(this, "Erreur", "Tri échoué : " + query.lastError().text());
    }
}

// === AJOUT D'ATELIER (FONCTIONNEL) ===
void MainWindow::on_pushButton_ajouter_clicked()
{
    // Récupérer les champs
    QString ref = ui->lineEdit_ref->text().trimmed();
    QString nom = ui->LineEdit_nom->text().trimmed();
    QString capStr = ui->LineEdit_cap->text().trimmed();
    QString jour = ui->LineEdit_j->text().trimmed();
    QString horaire = ui->LineEdit_h->text().trimmed();
    QString dureeStr = ui->LineEdit_d->text().trimmed();
    QString salleStr = ui->LineEdit_ns->text().trimmed();

    // Vérifier si tous les champs sont remplis
    if (ref.isEmpty() || nom.isEmpty() || capStr.isEmpty() || jour.isEmpty() ||
        horaire.isEmpty() || dureeStr.isEmpty() || salleStr.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs sont obligatoires !");
        return;
    }

    // Convertir et valider les nombres
    bool ok;
    int cap = capStr.toInt(&ok);
    if (!ok || cap < 1 || cap > 1000) {
        QMessageBox::warning(this, "Erreur", "Capacité invalide (1 à 1000).");
        return;
    }

    int duree = dureeStr.toInt(&ok);
    if (!ok || duree < 1 || duree > 24) {
        QMessageBox::warning(this, "Erreur", "Durée invalide (1 à 24).");
        return;
    }

    int salle = salleStr.toInt(&ok);
    if (!ok || salle < 1 || salle > 999) {
        QMessageBox::warning(this, "Erreur", "Numéro de salle invalide (1 à 999).");
        return;
    }

    // Valider le jour
    QStringList joursValides = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};
    if (!joursValides.contains(jour, Qt::CaseInsensitive)) {
        QMessageBox::warning(this, "Erreur", "Jour invalide ! Utilisez : Lundi, Mardi, etc.");
        return;
    }

    // Valider l'horaire (HH:MM)
    QRegularExpression re("^([0-1]?[0-9]|2[0-3]):[0-5][0-9]$");
    if (!re.match(horaire).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Horaire invalide ! Format : HH:MM (ex: 09:30)");
        return;
    }

    // Valider la référence
    if (ref.length() > 10 || !QRegularExpression("^[A-Za-z0-9]+$").match(ref).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Référence : max 10 caractères, lettres/chiffres uniquement.");
        return;
    }

    // Créer l'objet Atelier
    Atelier nouvelAtelier(ref, nom, cap, jour, horaire, duree, salle);

    // Ajouter dans la base
    QString errorMsg;
    if (nouvelAtelier.ajouter(&errorMsg)) {
        afficherAteliers();  // Rafraîchir le tableau
        QMessageBox::information(this, "Succès", "Atelier ajouté avec succès !");

        // Vider les champs
        ui->lineEdit_ref->clear();
        ui->LineEdit_nom->clear();
        ui->LineEdit_cap->clear();
        ui->LineEdit_j->clear();
        ui->LineEdit_h->clear();
        ui->LineEdit_d->clear();
        ui->LineEdit_ns->clear();
        ui->lineEdit_ref->setFocus();
    } else {
        QMessageBox::critical(this, "Échec", "Erreur lors de l'ajout :\n" + errorMsg);
    }
}

// === STATISTIQUES EN POURCENTAGE ===
void MainWindow::on_pushButton_stat_clicked()
{
    QMap<QString, int> stats = Atmp.statistiquesParJour();

    if (stats.isEmpty()) {
        ui->label_stat->setText("<font color='red'><b>Aucun atelier dans la base de données.</b></font>");
        return;
    }

    int total = 0;
    for (int count : stats.values()) total += count;

    QString result = "<div style='font-size:14px; text-align:center;'>"
                     "<b>Répartition des ateliers par jour :</b><br><br>";

    QStringList joursOrdre = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};

    for (const QString &jour : joursOrdre) {
        int count = stats.value(jour, 0);
        double pourcentage = total > 0 ? (count * 100.0 / total) : 0.0;
        result += QString("<b>%1</b> : %2 atelier(s) → <span style='color:blue; font-weight:bold;'>%3 %</span><br>")
                      .arg(jour)
                      .arg(count)
                      .arg(pourcentage, 0, 'f', 1);
    }

    result += QString("<br><b>Total :</b> %1 atelier(s)</div>").arg(total);

    ui->label_stat->setText(result);
    ui->label_stat->setAlignment(Qt::AlignCenter);
    ui->label_stat->setWordWrap(true);
}

// === FONCTIONS VIDES (à compléter plus tard) ===
void MainWindow::on_pushButton_modifier_clicked() { /* À implémenter */ }
void MainWindow::on_pushButton_supprimer_clicked() { /* À implémenter */ }
void MainWindow::on_pushButton_annuler_clicked() { /* À implémenter */ }
