#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adherent.h"
#include "employe.h"
#include "equipement.h"
#include "formateur.h"
#include <QString>

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
//stat
#include <QChartView>
#include <QChart>
#include <QPieSeries>
#include <QPieSlice>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QPdfDocument>
#include <QGraphicsScene>
#include <algorithm>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ADHERENTS
    QSqlQueryModel* model = A.afficher();
    ui->tableView->setModel(model);
    //QSqlQueryModel* modelE = E.afficher();
    //ui->tab_employe->setModel(modelE);
    // Page par défaut (par ex: employé)
    ui->stackedWidget->setCurrentIndex(0);
    //arduino
    int test = Ar.connect_arduino();

    if (test == 1)
        qDebug() << "Arduino connected on port:" << Ar.getPortName();
    else
        qDebug() << "Arduino connection failed:" << test;
    connect(&Ar, &Arduino::dataReceived,
            this, &MainWindow::on_arduino_data_received);

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

        QString nom = model->data(model->index(row, 1)).toString();        QString prenom = model->data(model->index(row, 2)).toString();
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


//*****************stat
void MainWindow::on_adherent_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
//*********************lhne********************
void MainWindow::on_afficher_pie_clicked()
{
    QString critere = ui->comboBox_critere_pie->currentText();
    QMap<QString, int> stats = A.statistiques(critere);

    if (stats.isEmpty()) {
        QMessageBox::information(this, "Statistiques", "Aucune donnée trouvée.");
        return;
    }

    //pie
    QPieSeries *series = new QPieSeries();
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        series->append(it.key(), it.value());
    }
    QList<QColor> palette = {
        QColor("#6B8E3A"),  // vert foncé
        QColor("#A7C957"),  // vert clair
        QColor("#E8A63B"),  // orange foncé
        QColor("#F6C453"),  // jaune doux
        QColor("#2F2F2F"),  // noir
        QColor("#90BE6D"),  // green pastel
        QColor("#EA9010"),  // mandarine
        QColor("#577590"),  // bleu gris
        QColor("#BC4749"),  // rouge doux
        QColor("#8ECAE6"),  // bleu pastel
        QColor("#FFB703"),  // jaune-orange
        QColor("#FB8500")   // orange vif
    };


    int i = 0;
    for (QPieSlice *slice : series->slices()) {
        slice->setBrush(palette[i % palette.size()]);
        slice->setLabelColor(QColor("#2F2F2F"));
        slice->setLabelVisible(true);
        i++;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques : " + critere);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setBackgroundBrush(QColor("#F6F5F0"));
    chart->setTitleBrush(QColor("#2F2F2F"));
    chart->legend()->setLabelColor(QColor("#2F2F2F"));
    chart->legend()->setBackgroundVisible(false);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chartView->setMinimumSize(ui->graphicsView_pie->size());

    ui->graphicsView_pie->setScene(nullptr);
    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView_pie);
    scene->setSceneRect(ui->graphicsView_pie->rect());
    ui->graphicsView_pie->setScene(scene);

    scene->addWidget(chartView);
    chartView->resize(ui->graphicsView_pie->size());
}
//stats bar
void MainWindow::on_afficher_bar_clicked()
{
    QString critere = ui->comboBox_critere_bar->currentText();
    QMap<QString, int> stats = A.statistiques(critere);

    if (stats.isEmpty()) {
        QMessageBox::information(this, "Statistiques", "Aucune donnée trouvée.");
        return;
    }

    QBarSet *set = new QBarSet(critere);
    QStringList categories;

    for (auto it = stats.begin(); it != stats.end(); ++it) {
        *set << it.value();
        categories << it.key();
    }
    set->setBrush(QColor("#6B8E3A"));
    set->setBorderColor(QColor("#2F2F2F"));

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques : " + critere);
    chart->setBackgroundBrush(QColor("#F6F5F0"));
    chart->setTitleBrush(QColor("#2F2F2F"));
    chart->legend()->setLabelColor(QColor("#2F2F2F"));
    chart->legend()->setBackgroundVisible(false);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsColor(QColor("#2F2F2F"));
    axisX->setGridLineColor(QColor("#A7C957"));
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, *std::max_element(stats.begin(), stats.end()));
    axisY->setLabelsColor(QColor("#2F2F2F"));
    axisY->setGridLineColor(QColor("#A7C957"));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    view->setMinimumSize(ui->graphicsView_bar->size());
    ui->graphicsView_bar->setScene(nullptr);
    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView_bar);
    scene->setSceneRect(ui->graphicsView_bar->rect());
    ui->graphicsView_bar->setScene(scene);

    scene->addWidget(view);
    view->resize(ui->graphicsView_bar->size());
}
//************innovantes
//uploading
void MainWindow::on_btn_upload_cv_clicked()
{
    // 🔹 Lire l’ID depuis la 3ème Tab (lineEdit_uplod)
    int id = ui->lineEdit_uplod->text().toInt();

    if (id <= 0 || !Adherent::idExiste(id)) {
        QMessageBox::warning(this, "Erreur",
                             "Veuillez saisir un ID d'adhérent AVANT de téléverser un CV !");
        return;
    }

    // 🔹 Boîte de sélection du fichier PDF
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Sélectionner un CV",
        QDir::homePath(),
        "Fichiers PDF (*.pdf)"
        );

    if (filePath.isEmpty())
        return;

    // 🔹 Lire le PDF en bytes (pour stocker en BLOB)
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Erreur", "Impossible de lire le fichier PDF !");
        return;
    }

    QByteArray pdfData = file.readAll();
    file.close();

    // 🔹 Sauvegarde dans la Base de Données
    QSqlQuery q;
    q.prepare("UPDATE ADHERENTS SET CV_FILE = :cv WHERE ID = :id");
    q.bindValue(":cv", pdfData);
    q.bindValue(":id", id);

    if (!q.exec()) {
        QMessageBox::critical(this, "Erreur",
                              "Erreur lors de l'enregistrement du CV : " + q.lastError().text());
        return;
    }

    QMessageBox::information(this, "Succès", "CV enregistré dans la base de données !");

    // 🔹 EXTRACTION DU TEXTE pour affichage
    QString texte = extractTextFromPdf(filePath);
    ui->textEdit_cv->setText(texte);
}



QByteArray MainWindow::getCvBlobFromDB(int id)
{
    QSqlQuery q;
    q.prepare("SELECT CV_FILE FROM ADHERENTS WHERE ID = :id");
    q.bindValue(":id", id);

    if (!q.exec() || !q.next())
        return QByteArray();

    return q.value(0).toByteArray();
}



QString MainWindow::extractTextFromPdf(const QString &filePath)
{
    QPdfDocument doc;
    QPdfDocument::Error err = doc.load(filePath);

    if (err != QPdfDocument::Error::None) {
        qDebug() << "Erreur PDF:" << err;
        return "";
    }

    QString text;
    int pages = doc.pageCount();

    for (int i = 0; i < pages; ++i) {
        QPdfSelection sel = doc.getAllText(i);
        text += sel.text() + "\n";
    }

    return text;
}



QString MainWindow::determinerProfilDepuisCv(const QString &txt)
{
    QString t = txt.toLower();

    // Santé fragile / maladies chroniques
    if (t.contains("asthma") || t.contains("asthme") ||
        t.contains("diabetes") || t.contains("diabète") ||
        t.contains("illness") || t.contains("maladie")) {
        return "sante";
    }

    // Sportif
    if (t.contains("football") || t.contains("soccer") ||
        t.contains("basket") || t.contains("swim") ||
        t.contains("natation") || t.contains("sport")) {
        return "sport";
    }

    // Art / musique
    if (t.contains("drawing") || t.contains("painting") ||
        t.contains("dessin") || t.contains("art") ||
        t.contains("music") || t.contains("musique")) {
        return "art";
    }

    // Informatique / coding
    if (t.contains("coding") || t.contains("programming") ||
        t.contains("programmation") || t.contains("python") ||
        t.contains("java") || t.contains("robot")) {
        return "coding";
    }

    // Lecture / culture
    if (t.contains("reading") || t.contains("read") ||
        t.contains("livres") || t.contains("books") ||
        t.contains("lecture")) {
        return "lecture";
    }

    // Débat / communication
    if (t.contains("public speaking") || t.contains("presentation") ||
        t.contains("débat") || t.contains("debate") ||
        t.contains("communication")) {
        return "eloquence";
    }

    // Science / expériences
    if (t.contains("science") || t.contains("experiment") ||
        t.contains("laboratory") || t.contains("laboratoire")) {
        return "science";
    }

    return "neutre";
}
//recommendation
bool MainWindow::trouverAtelierPourProfil(const QString &profil, int &ref,
                                          QString &nom, QString &horaire)
{
    QSqlQuery q;

    if (profil == "sante") {
        q.prepare("SELECT REFERENCE, NOM_ATELIER, HORAIRE "
                  "FROM ATELIERS "
                  "WHERE (LOWER(NOM_ATELIER) LIKE '%relax%' "
                  "   OR LOWER(NOM_ATELIER) LIKE '%respir%' "
                  "   OR LOWER(NOM_ATELIER) LIKE '%sant%') "
                  "AND ROWNUM = 1");
    }
    else if (profil == "sport") {
        q.prepare("SELECT REFERENCE, NOM_ATELIER, HORAIRE "
                  "FROM ATELIERS "
                  "WHERE (LOWER(NOM_ATELIER) LIKE '%sport%' "
                  "   OR LOWER(NOM_ATELIER) LIKE '%football%' "
                  "   OR LOWER(NOM_ATELIER) LIKE '%basket%') "
                  "AND ROWNUM = 1");
    }
    else if (profil == "art") {
        q.prepare("SELECT REFERENCE, NOM_ATELIER, HORAIRE "
                  "FROM ATELIERS "
                  "WHERE (LOWER(NOM_ATELIER) LIKE '%art%' "
                  "   OR LOWER(NOM_ATELIER) LIKE '%dessin%' "
                  "   OR LOWER(NOM_ATELIER) LIKE '%musique%') "
                  "AND ROWNUM = 1");
    }
    else if (profil == "coding") {
        q.prepare("SELECT REFERENCE, NOM_ATELIER, HORAIRE "
                  "FROM ATELIERS "
                  "WHERE (LOWER(NOM_ATELIER) LIKE '%coding%' "
                  "   OR LOWER(NOM_ATELIER) LIKE '%code%' "
                  "   OR LOWER(NOM_ATELIER) LIKE '%robot%' "
                  "   OR LOWER(NOM_ATELIER) LIKE '%informat%') "
                  "AND ROWNUM = 1");
    }
    else if (profil == "lecture") {
        q.prepare("SELECT REFERENCE, NOM_ATELIER, HORAIRE "
                  "FROM ATELIERS "
                  "WHERE (LOWER(NOM_ATELIER) LIKE '%lecture%' "
                  "   OR LOWER(NOM_ATELIER) LIKE '%reading%' "
                  "   OR LOWER(NOM_ATELIER) LIKE '%book%') "
                  "AND ROWNUM = 1");
    }
    else if (profil == "eloquence") {
        q.prepare("SELECT REFERENCE, NOM_ATELIER, HORAIRE "
                  "FROM ATELIERS "
                  "WHERE (LOWER(NOM_ATELIER) LIKE '%débat%' "
                  "   OR LOWER(NOM_ATELIER) LIKE '%debate%' "
                  "   OR LOWER(NOM_ATELIER) LIKE '%eloquence%') "
                  "AND ROWNUM = 1");
    }
    else if (profil == "science") {
        q.prepare("SELECT REFERENCE, NOM_ATELIER, HORAIRE "
                  "FROM ATELIERS "
                  "WHERE (LOWER(NOM_ATELIER) LIKE '%science%' "
                  "   OR LOWER(NOM_ATELIER) LIKE '%lab%') "
                  "AND ROWNUM = 1");
    }
    else { // profil neutre -> n'importe quel atelier
        q.prepare("SELECT REFERENCE, NOM_ATELIER, HORAIRE "
                  "FROM ATELIERS WHERE ROWNUM = 1");
    }

    if (!q.exec() || !q.next()) {
        qDebug() << "Aucun atelier trouvé pour le profil:" << profil
                 << "erreur:" << q.lastError().text();
        return false;
    }

    ref     = q.value(0).toInt();
    nom     = q.value(1).toString();
    horaire = q.value(2).toString();
    return true;
}
void MainWindow::on_btn_recommander_clicked()
{
    int id = ui->lineEdit_uplod->text().toInt();

    if (id <= 0 || !Adherent::idExiste(id)) {
        QMessageBox::warning(this, "Erreur",
                             "Veuillez saisir un ID d'adhérent valide.");
        return;
    }

    QSqlQuery q;
    q.prepare("SELECT CV_FILE FROM ADHERENTS WHERE ID = :id");
    q.bindValue(":id", id);

    if (!q.exec() || !q.next()) {
        QMessageBox::warning(this, "Erreur",
                             "Impossible de récupérer le CV depuis la base.");
        return;
    }

    QByteArray pdfData = q.value(0).toByteArray();

    if (pdfData.isEmpty()) {
        QMessageBox::warning(this, "Erreur",
                             "Aucun CV n'est enregistré pour cet adhérent.");
        return;
    }

    // 3 — Créer un fichier PDF temporaire
    QString tempPath = QDir::temp().path() + "/cv_temp_" + QString::number(id) + ".pdf";
    QFile temp(tempPath);

    if (!temp.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'écrire le fichier temporaire !");
        return;
    }

    temp.write(pdfData);
    temp.close();

    // 4 — Extraire texte du PDF
    QString cvText = extractTextFromPdf(tempPath);

    if (cvText.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur",
                             "Impossible de lire le contenu du CV.");
        return;
    }

    // 5 — Déterminer le profil
    QString profil = determinerProfilDepuisCv(cvText);

    // 6 — Trouver atelier adapté
    int refAtelier;
    QString nomAtelier, horaireAtelier;

    if (!trouverAtelierPourProfil(profil, refAtelier, nomAtelier, horaireAtelier)) {
        QMessageBox::information(this, "Information",
                                 "Aucun atelier approprié n'a été trouvé pour ce profil.");
        return;
    }

    // 7 — Texte explicatif
    QString raison;

    if (profil == "sante")
        raison = "présente des éléments liés à la santé ou à des maladies chroniques.";
    else if (profil == "sport")
        raison = "montre un intérêt ou une pratique régulière du sport.";
    else if (profil == "art")
        raison = "met en avant des talents artistiques (dessin, musique, etc.).";
    else if (profil == "coding")
        raison = "contient des compétences ou un intérêt pour la programmation.";
    else if (profil == "lecture")
        raison = "indique un intérêt marqué pour la lecture et la culture.";
    else if (profil == "eloquence")
        raison = "souligne des compétences de communication et de prise de parole.";
    else if (profil == "science")
        raison = "mentionne un intérêt pour la science et les expériences.";
    else
        raison = "présente un profil général.";

    // 8 — Construire message final
    QString message = QString(
                          "L'élève ID %1 est recommandé pour l'atelier :\n\n"
                          "• Nom : %2\n"
                          "• Référence : %3\n"
                          "• Horaire : %4\n\n"
                          "Raison : %5"
                          )
                          .arg(id)
                          .arg(nomAtelier)
                          .arg(refAtelier)
                          .arg(horaireAtelier)
                          .arg(raison);


    ui->label_recommandation->setText(message);
    qDebug() << "TEXTE CV EXTRAIT = " << cvText;

}
//statistique adherents
void MainWindow::on_fonc_adherent_btn_clicked()
{
    //nemchu lel statistique chnag of index
    ui->stackedWidget->setCurrentIndex(1);
    qDebug() << "UPLOAD BUTTON CLICKED!";

}
//arduino adherent
void MainWindow::on_arduino_data_received(QString uid)
{
    if (uid.isEmpty()) {
        qDebug() << "Empty UID received.";
        return;
    }

    qDebug() << "UID received:" << uid;

    // 1. Find employee by RFID UID
    QSqlQuery q;
    q.prepare("SELECT ID FROM EMPLOYES WHERE RFID_UID = :uid");
    q.bindValue(":uid", uid);

    if (!q.exec()) {
        qDebug() << "Query error:" << q.lastError().text();
        return;
    }

    if (q.next()) {
        int idEmp = q.value(0).toInt();
        qDebug() << "Employee found:" << idEmp;

        // 2. Insert presence IN (trigger handles ID)
        QSqlQuery in;
        in.prepare("INSERT INTO PRESENCE (CIN_EMP, DATE_IN) VALUES (:c, SYSDATE)");
        in.bindValue(":c", idEmp);
        in.exec();

        // 3. Mark employee as PRESENT
        QSqlQuery etat;
        etat.prepare("UPDATE EMPLOYES SET ETAT='PRESENT' WHERE ID=:id");
        etat.bindValue(":id", idEmp);
        etat.exec();

        qDebug() << "ENTRY (IN) saved. Status = PRESENT.";
    }
    else {
        qDebug() << "Unknown badge!";
    }
}

//destrc
MainWindow::~MainWindow()
{
    delete ui;
}

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

void MainWindow::on_employe_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// --- EQUIPEMENTS ---

void MainWindow::on_equipement_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->equipements);
    load_equipement_data();
}

void MainWindow::load_equipement_data()
{
    QSqlQueryModel *model = Eq.afficher();
    ui->tableView_equipement->setModel(model);
    ui->tableView_equipement->resizeColumnsToContents();
}

void MainWindow::on_ajouter_equipement_btn_clicked()
{
    // Récupération des données du formulaire
    int reference = ui->reference_equipement->text().toInt();
    QString nom = ui->nom_equipement->text();
    int quantite = ui->quantite_equipement->text().toInt();
    QString categorie = ui->categorie_equipement->text();
    double prix = ui->prix_equipement->text().toDouble();

    // Validation des données
    if (reference <= 0) {
        QMessageBox::warning(this, "Erreur", "Référence invalide!");
        return;
    }
    if (nom.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Nom invalide!");
        return;
    }
    if (quantite < 0) {
        QMessageBox::warning(this, "Erreur", "Quantité invalide!");
        return;
    }
    if (prix < 0) {
        QMessageBox::warning(this, "Erreur", "Prix invalide!");
        return;
    }

    // Configuration de l'objet Equipement
    Eq.setReference(reference);
    Eq.setNom(nom);
    Eq.setQuantite(quantite);
    Eq.setCategorie(categorie);
    Eq.setPrix(prix);

    // Ajout dans la base
    if (Eq.ajouter()) {
        QMessageBox::information(this, "Succès", "Équipement ajouté avec succès!");
        load_equipement_data();
        clear_equipement_form();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout!");
    }
}

void MainWindow::on_modifier_equipement_btn_clicked()
{
    int reference = ui->reference_equipement->text().toInt();

    if (reference <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir une référence valide!");
        return;
    }

    if (!Equipement::referenceExiste(reference)) {
        QMessageBox::warning(this, "Erreur", "Cette référence n'existe pas!");
        return;
    }

    QString nom = ui->nom_equipement->text();
    int quantite = ui->quantite_equipement->text().toInt();
    QString categorie = ui->categorie_equipement->text();
    double prix = ui->prix_equipement->text().toDouble();

    // Validation optionnelle des données modifiées
    if (!nom.isEmpty() && nom.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Nom invalide!");
        return;
    }
    if (quantite < 0) {
        QMessageBox::warning(this, "Erreur", "Quantité invalide!");
        return;
    }
    if (prix < 0) {
        QMessageBox::warning(this, "Erreur", "Prix invalide!");
        return;
    }

    Eq.setReference(reference);
    if (!nom.isEmpty()) Eq.setNom(nom);
    if (quantite > 0) Eq.setQuantite(quantite);
    if (!categorie.isEmpty()) Eq.setCategorie(categorie);
    if (prix > 0) Eq.setPrix(prix);

    if (Eq.modifier()) {
        QMessageBox::information(this, "Succès", "Équipement modifié avec succès!");
        load_equipement_data();
        clear_equipement_form();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification!");
    }
}

void MainWindow::on_supprimer_equipement_btn_clicked()
{
    int reference = ui->reference_equipement->text().toInt();

    if (reference <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir une référence valide!");
        return;
    }

    if (!Equipement::referenceExiste(reference)) {
        QMessageBox::warning(this, "Erreur", "Cette référence n'existe pas!");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer l'équipement référence: " + QString::number(reference) + " ?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }

    if (Eq.supprimer(reference)) {
        QMessageBox::information(this, "Succès", "Équipement supprimé avec succès!");
        load_equipement_data();
        clear_equipement_form();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression!");
    }
}

void MainWindow::on_rech_equipement_btn_clicked()
{
    QString critere = ui->rech_equipement_input->currentText(); // REF, NOM, CATEGORIE
    QString valeur = ui->rech_equipement->text().trimmed();

    if (valeur.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir une valeur à rechercher");
        return;
    }

    // Validation spécifique pour REF
    if (critere == "REF") {
        bool ok;
        int ref = valeur.toInt(&ok);
        if (!ok || ref <= 0) {
            QMessageBox::warning(this, "Erreur", "Référence doit être un nombre positif");
            ui->rech_equipement->clear();
            ui->rech_equipement->setFocus();
            return;
        }
    }

    // Validation spécifique pour NOM ou CATEGORIE (optionnel)
    if (critere == "NOM" || critere == "CATEGORIE") {
        if (valeur.length() < 2) { // par exemple, au moins 2 caractères
            QMessageBox::warning(this, "Erreur", critere + " doit contenir au moins 2 caractères");
            ui->rech_equipement->clear();
            ui->rech_equipement->setFocus();
            return;
        }
    }

    // Appel à la fonction rechercher
    QSqlQueryModel* model = Eq.rechercher(critere, valeur);

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Recherche", "Aucun résultat trouvé pour " + critere + ": " + valeur);
    } else {
        QMessageBox::information(this, "Recherche", QString::number(model->rowCount()) + " résultat(s) trouvé(s)");
    }

    ui->tableView_equipement->setModel(model);
    ui->rech_equipement->clear();
    ui->rech_equipement->setFocus();
}

void MainWindow::on_tri_up_equipement_clicked()
{
    QString critere = ui->trier_equipement_input->currentText();
    QString ordre = "ASC";
    QSqlQueryModel* model = Eq.trier(critere, ordre);
    ui->tableView_equipement->setModel(model);
    QMessageBox::information(this, "Tri", "Données triées par " + critere + " (Croissant)");
}

void MainWindow::on_tri_down_equipement_clicked()
{
    QString critere = ui->trier_equipement_input->currentText();
    QString ordre = "DESC";
    QSqlQueryModel* model = Eq.trier(critere, ordre);
    ui->tableView_equipement->setModel(model);
    QMessageBox::information(this, "Tri", "Données triées par " + critere + " (Décroissant)");
}

void MainWindow::on_rafraichir_equipement_btn_clicked()
{
    load_equipement_data();
    QMessageBox::information(this, "Rafraîchissement", "Liste des équipements actualisée");
}

void MainWindow::on_pdf_equipement_btn_clicked()
{
    QSqlQueryModel* model = Eq.afficher();
    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Export PDF", "Aucune donnée à exporter");
        return;
    }

    QString content;
    content += "LISTE DES ÉQUIPEMENTS\n";
    content += "=====================\n\n";
    content += "Exporté le : " + QDate::currentDate().toString("dd/MM/yyyy") + "\n";
    content += "Nombre d'équipements : " + QString::number(model->rowCount()) + "\n\n";

    for (int row = 0; row < model->rowCount(); ++row) {
        content += "▪ Équipement " + QString::number(row + 1) + ":\n";

        QString reference = model->data(model->index(row, 0)).toString();
        QString nom = model->data(model->index(row, 1)).toString();
        QString quantite = model->data(model->index(row, 2)).toString();
        QString categorie = model->data(model->index(row, 3)).toString();
        QString prix = model->data(model->index(row, 4)).toString();

        content += "   Référence : " + reference + "\n";
        content += "   Nom : " + nom + "\n";
        content += "   Quantité : " + quantite + "\n";
        content += "   Catégorie : " + categorie + "\n";
        content += "   Prix : " + prix + " DT\n\n";
    }

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Exporter en PDF",
                                                    QDir::homePath() + "/equipements_" + QDate::currentDate().toString("yyyyMMdd") + ".pdf",
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

void MainWindow::clear_equipement_form()
{
    ui->reference_equipement->clear();
    ui->nom_equipement->clear();
    ui->quantite_equipement->clear();
    ui->categorie_equipement->clear();
    ui->prix_equipement->clear();
}




//Formateur
// CRUD Formateurs
void MainWindow::on_ajouter_forma_btn_clicked()
{
    qDebug() << "*****BOUTON AJOUTER FORMATEUR CLIQUE *****";

    int idf = ui->id_forma->text().toInt();
    QString nomf = ui->nom_forma->text();
    QString emailf = ui->email_forma->text();
    QString mdpf = ui->mdp_forma->text();
    QString specialite = ui->specialite_forma->text();
    QString telf = ui->tel_forma->text();
    QString adressef = ui->adresse_forma->text();

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
        ui->tableView_forma->setModel(model);

        // Vider les champs après ajout réussi
        ui->id_forma->clear();
        ui->nom_forma->clear();
        ui->email_forma->clear();
        ui->mdp_forma->clear();
        ui->specialite_forma->clear();
        ui->tel_forma->clear();
        ui->adresse_forma->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout !");
    }
}

void MainWindow::on_modifier_forma_btn_clicked()
{
    qDebug() << "*****BOUTON MODIFIER FORMATEUR CLIQUE *****";

    int idf = ui->id_forma->text().toInt();
    QString nomf = ui->nom_forma->text();
    QString emailf = ui->email_forma->text();
    QString mdpf = ui->mdp_forma->text();
    QString specialite = ui->specialite_forma->text();
    QString telf = ui->tel_forma->text();
    QString adressef = ui->adresse_forma->text();

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
        ui->tableView_forma->setModel(model);

        // Vider les champs après modification
        ui->id_forma->clear();
        ui->nom_forma->clear();
        ui->email_forma->clear();
        ui->mdp_forma->clear();
        ui->specialite_forma->clear();
        ui->tel_forma->clear();
        ui->adresse_forma->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification !");
    }
}

void MainWindow::on_supprimer_forma_btn_clicked()
{
    int idf = ui->id_forma->text().toInt();

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
        ui->tableView_forma->setModel(model);

        // Vider les champs après suppression
        ui->id_forma->clear();
        ui->nom_forma->clear();
        ui->email_forma->clear();
        ui->mdp_forma->clear();
        ui->specialite_forma->clear();
        ui->tel_forma->clear();
        ui->adresse_forma->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression !");
    }
}




















// Nouvelle fonction pour l'envoi de SMS
void MainWindow::on_envoyer_smsf_btn_clicked()
{
    qDebug() << "***** BOUTON ENVOYER SMS CLIQUE *****";

    QString telephone = ui->lineEdit_telf_sms->text().trimmed();
    QString message = ui->textEdit_messagef_sms->toPlainText().trimmed();

    qDebug() << "Téléphone saisi:" << telephone;
    qDebug() << "Message saisi:" << message;

    // Validations
    if (telephone.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un numéro de téléphone");
        ui->lineEdit_telf_sms->setFocus();
        return;
    }

    if (message.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un message");
        ui->textEdit_messagef_sms->setFocus();
        return;
    }

    if (!Formateur::telValide(telephone)) {
        QMessageBox::warning(this, "Erreur",
                             "Numéro de téléphone invalide.\n"
                             "Doit commencer par 2, 5 ou 9 et avoir 8 chiffres");
        ui->lineEdit_telf_sms->clear();
        ui->lineEdit_telf_sms->setFocus();
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
        ui->lineEdit_telf_sms->clear();
        ui->textEdit_messagef_sms->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'envoi du SMS !");
    }
}










// Métiers Formateurs
void MainWindow::on_rech_forma_btn_clicked()
{
    // Récupérer le critère depuis un QComboBox
    QString critere = ui->comboBox_recherche_forma->currentText(); // Doit contenir "ID", "Nom", "Spécialité"
    QString valeur = ui->LineEdit_rech_forma->text().trimmed();

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
            ui->LineEdit_rech_forma->clear();
            ui->LineEdit_rech_forma->setFocus();
            return;
        }
    }

    QSqlQueryModel* model = Formateur::rechercher(critere, valeur);

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Recherche", "Aucun résultat trouvé pour " + critere + ": " + valeur);
    } else {
        QMessageBox::information(this, "Recherche", QString::number(model->rowCount()) + " résultat(s) trouvé(s)");
        ui->tableView_forma->setModel(model);
    }
    ui->LineEdit_rech_forma->clear();
}
void MainWindow::on_tri_up_forma_clicked()
{
    QString critere = ui->comboBox_tri_forma->currentText();
    QString ordre = "ASC";
    QSqlQueryModel* model = Formateur::trier(critere, ordre);
    ui->tableView_forma->setModel(model);
    QMessageBox::information(this, "Tri", "Données triées par " + critere + " (Croissant)");
}

void MainWindow::on_tri_down_forma_clicked()
{
    QString critere = ui->comboBox_tri_forma->currentText();
    QString ordre = "DESC";
    QSqlQueryModel* model = Formateur::trier(critere, ordre);
    ui->tableView_forma->setModel(model);
    QMessageBox::information(this, "Tri", "Données triées par " + critere + " (Décroissant)");
}

void MainWindow::on_raffraichir_forma_btn_clicked()
{
    QSqlQueryModel* model = Formateur::afficher();
    ui->tableView_forma->setModel(model);
    QMessageBox::information(this, "Rafraîchissement", "Liste des formateurs actualisée");
}

void MainWindow::on_pdf_forma_btn_clicked()
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








void MainWindow::on_afficher_pie_f_clicked()
{
    QString critere = ui->comboBox_critere_pie_f->currentText();
    QMap<QString, int> stats = F.statistiques(critere);

    if (stats.isEmpty()) {
        QMessageBox::information(this, "Statistiques", "Aucune donnée trouvée.");
        return;
    }

    QPieSeries *series = new QPieSeries();

    for (auto it = stats.begin(); it != stats.end(); ++it) {
        series->append(it.key(), it.value());
    }

    QList<QColor> palette = {
        QColor("#6B8E3A"),
        QColor("#A7C957"),
        QColor("#E8A63B"),
        QColor("#F2C14E"),
        QColor("#2F2F2F")
    };

    int i = 0;
    for (QPieSlice *slice : series->slices()) {
        slice->setBrush(palette[i % palette.size()]);
        slice->setLabelColor(QColor("#2F2F2F"));
        slice->setLabelVisible(true);
        i++;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques : " + critere);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setBackgroundBrush(QColor("#F6F5F0"));
    chart->setTitleBrush(QColor("#2F2F2F"));
    chart->legend()->setLabelColor(QColor("#2F2F2F"));
    chart->legend()->setBackgroundVisible(false);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->graphicsView_pie_4->setScene(nullptr);
    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView_pie_4);
    scene->setSceneRect(ui->graphicsView_pie_4->rect());
    ui->graphicsView_pie_4->setScene(scene);

    scene->addWidget(chartView);
    chartView->resize(ui->graphicsView_pie_4->size());
}

void MainWindow::on_afficher_bar_f_clicked()
{
    QString critere = ui->comboBox_critere_bar_4->currentText();
    QMap<QString, int> stats = F.statistiques(critere);

    if (stats.isEmpty()) {
        QMessageBox::information(this, "Statistiques", "Aucune donnée trouvée.");
        return;
    }

    QBarSet *set = new QBarSet(critere);
    QStringList categories;

    for (auto it = stats.begin(); it != stats.end(); ++it) {
        *set << it.value();
        categories << it.key();
    }

    set->setBrush(QColor("#6B8E3A"));
    set->setBorderColor(QColor("#2F2F2F"));

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques : " + critere);
    chart->setBackgroundBrush(QColor("#F6F5F0"));
    chart->setTitleBrush(QColor("#2F2F2F"));
    chart->legend()->setLabelColor(QColor("#2F2F2F"));
    chart->legend()->setBackgroundVisible(false);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsColor(QColor("#2F2F2F"));
    axisX->setGridLineColor(QColor("#A7C957"));
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, *std::max_element(stats.begin(), stats.end()));
    axisY->setLabelsColor(QColor("#2F2F2F"));
    axisY->setGridLineColor(QColor("#A7C957"));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);

    ui->graphicsView_bar_4->setScene(nullptr);
    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView_bar_4);
    scene->setSceneRect(ui->graphicsView_bar_4->rect());
    ui->graphicsView_bar_4->setScene(scene);

    scene->addWidget(view);
    view->resize(ui->graphicsView_bar_4->size());
}

void MainWindow::on_Gformateur_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_fonctionalitef_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

