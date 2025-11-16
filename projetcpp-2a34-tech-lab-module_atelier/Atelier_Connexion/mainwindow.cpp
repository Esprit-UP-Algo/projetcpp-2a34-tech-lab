#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QTableWidgetItem>
#include <QSqlRecord>  // AJOUTÉ ICI

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Config tableau
    ui->TableWidget->setColumnCount(7);
    ui->TableWidget->setHorizontalHeaderLabels({
        "Référence", "Nom d'atelier", "Capacité", "Jour", "Durée", "Numéro de salle", "Horaire"
    });

    // Validateurs
    ui->LineEdit_cap->setValidator(new QIntValidator(1, 1000, this));
    ui->LineEdit_d->setValidator(new QIntValidator(1, 24, this));
    ui->LineEdit_ns->setValidator(new QIntValidator(1, 999, this));

    // Affichage initial
    afficherAteliers();

    // Double-clic pour modifier
    connect(ui->TableWidget, &QTableWidget::itemDoubleClicked, this, [this](QTableWidgetItem *item) {
        int row = item->row();
        ui->lineEdit_ref->setText(ui->TableWidget->item(row, 0)->text());
        ui->LineEdit_nom->setText(ui->TableWidget->item(row, 1)->text());
        ui->LineEdit_cap->setText(ui->TableWidget->item(row, 2)->text());
        ui->LineEdit_j->setText(ui->TableWidget->item(row, 3)->text());
        ui->LineEdit_d->setText(ui->TableWidget->item(row, 4)->text());
        ui->LineEdit_ns->setText(ui->TableWidget->item(row, 5)->text());
        ui->LineEdit_h->setText(ui->TableWidget->item(row, 6)->text());
        ui->lineEdit_ref->setEnabled(false);
    });
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::afficherAteliers() {
    ui->TableWidget->setRowCount(0);
    QSqlQueryModel* model = Atmp.afficher();
    for (int i = 0; i < model->rowCount(); ++i) {
        ui->TableWidget->insertRow(i);
        for (int col = 0; col < 7; ++col) {
            ui->TableWidget->setItem(i, col, new QTableWidgetItem(model->record(i).value(col).toString()));
        }
    }
    delete model;
    ui->TableWidget->resizeColumnsToContents();
}

// === AJOUTER ===
void MainWindow::on_pushButton_ajouter_clicked() {
    Atelier a;
    if (!a.setReference(ui->lineEdit_ref->text()) ||
        !a.setNomAtelier(ui->LineEdit_nom->text()) ||
        !a.setCapacite(ui->LineEdit_cap->text().toInt()) ||
        !a.setJour(ui->LineEdit_j->text()) ||
        !a.setHoraire(ui->LineEdit_h->text()) ||
        !a.setDuree(ui->LineEdit_d->text().toInt()) ||
        !a.setNumeroSalle(ui->LineEdit_ns->text().toInt())) {
        QMessageBox::warning(this, "Erreur", "Données invalides ! Vérifiez tous les champs.");
        return;
    }

    if (a.ajouter()) {
        afficherAteliers();
        QMessageBox::information(this, "Succès", "Atelier ajouté !");
        on_pushButton_annuler_clicked();
    } else {
        QMessageBox::critical(this, "Échec", "Impossible d'ajouter l'atelier.");
    }
}

// === MODIFIER ===
void MainWindow::on_pushButton_modifier_clicked() {
    int row = ui->TableWidget->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Sélection", "Sélectionnez un atelier.");
        return;
    }

    Atelier a;
    a.setReference(ui->TableWidget->item(row, 0)->text());
    if (!a.setNomAtelier(ui->LineEdit_nom->text()) ||
        !a.setCapacite(ui->LineEdit_cap->text().toInt()) ||
        !a.setJour(ui->LineEdit_j->text()) ||
        !a.setHoraire(ui->LineEdit_h->text()) ||
        !a.setDuree(ui->LineEdit_d->text().toInt()) ||
        !a.setNumeroSalle(ui->LineEdit_ns->text().toInt())) {
        QMessageBox::warning(this, "Erreur", "Données invalides.");
        return;
    }

    if (a.modifier()) {
        afficherAteliers();
        QMessageBox::information(this, "Succès", "Atelier modifié !");
        on_pushButton_annuler_clicked();
    } else {
        QMessageBox::critical(this, "Échec", "Modification échouée.");
    }
}

// === SUPPRIMER ===
void MainWindow::on_pushButton_supprimer_clicked() {
    int row = ui->TableWidget->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Sélection", "Sélectionnez un atelier.");
        return;
    }

    QString ref = ui->TableWidget->item(row, 0)->text();
    if (QMessageBox::question(this, "Confirmer", "Supprimer <b>" + ref + "</b> ?") == QMessageBox::Yes) {
        if (Atmp.supprimer(ref)) {
            afficherAteliers();
            QMessageBox::information(this, "Succès", "Atelier supprimé !");
        }
    }
}

// === ANNULER ===
void MainWindow::on_pushButton_annuler_clicked() {
    ui->lineEdit_ref->clear(); ui->LineEdit_nom->clear(); ui->LineEdit_cap->clear();
    ui->LineEdit_j->clear(); ui->LineEdit_h->clear(); ui->LineEdit_d->clear(); ui->LineEdit_ns->clear();
    ui->lineEdit_ref->setEnabled(true); ui->TableWidget->clearSelection();
}

// === RECHERCHER (SANS COMBOBOX) ===
void MainWindow::on_pushButton_rechercher_clicked() {
    QString valeur = ui->lineEdit_recherche->text().trimmed();
    if (valeur.isEmpty()) {
        afficherAteliers();
        return;
    }

    // Recherche par référence ou nom
    QSqlQueryModel* model = Atmp.rechercher("Nom", valeur); // ou "Référence"
    ui->TableWidget->setRowCount(0);
    for (int i = 0; i < model->rowCount(); ++i) {
        ui->TableWidget->insertRow(i);
        for (int col = 0; col < 7; ++col) {
            ui->TableWidget->setItem(i, col, new QTableWidgetItem(model->record(i).value(col).toString()));
        }
    }
    delete model;
}

// === TRIER (SANS CHECKBOX) ===
void MainWindow::on_pushButton_trier_clicked() {
    QString ordre = "ASC";  // FIXE
    QSqlQueryModel* model = Atmp.trier("jour", ordre); // ou "capacité", etc.
    ui->TableWidget->setRowCount(0);
    for (int i = 0; i < model->rowCount(); ++i) {
        ui->TableWidget->insertRow(i);
        for (int col = 0; col < 7; ++col) {
            ui->TableWidget->setItem(i, col, new QTableWidgetItem(model->record(i).value(col).toString()));
        }
    }
    delete model;
}

// === STATISTIQUES ===
void MainWindow::on_pushButton_stat_clicked() {
    QMap<QString, int> stats = Atmp.statistiquesParJour();
    if (stats.isEmpty()) {
        ui->label_stat->setText("<font color='red'><b>Aucun atelier.</b></font>");
        return;
    }
    int total = 0; for (int v : stats.values()) total += v;
    QString html = "<div style='text-align:center; font-size:14px;'><b>Répartition par jour :</b><br><br>";
    QStringList jours = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};
    for (const QString &j : jours) {
        int c = stats.value(j, 0);
        double pct = total > 0 ? (c * 100.0 / total) : 0;
        html += QString("<b>%1</b> : %2 → <span style='color:blue;'>%3 %</span><br>").arg(j).arg(c).arg(pct, 0, 'f', 1);
    }
    html += QString("<br><b>Total :</b> %1</div>").arg(total);
    ui->label_stat->setText(html);
}
