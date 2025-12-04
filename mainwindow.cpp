#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adherent.h"
#include "employe.h"
#include "equipement.h"
#include "formateur.h"
#include "atelier.h"
#include "arduino.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QDate>
#include <QDateTime>
#include <QIntValidator>
#include <QFileDialog>
#include <QDir>
#include <QPrinter>
#include <QTextDocument>
#include <QTemporaryFile>
#include <QFile>
#include <QChart>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QGraphicsScene>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QPdfDocument>
#include <algorithm>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->TableWidget->setColumnCount(8);
    ui->TableWidget->setHorizontalHeaderLabels({
        "Référence", "Nom d'atelier", "Capacité", "Capacité Max", "Jour", "Durée", "Salle", "Horaire"
    });
    ui->LineEdit_cap->setValidator(new QIntValidator(0, 1000, this));
    ui->LineEdit_capmax->setValidator(new QIntValidator(10, 500, this));
    ui->LineEdit_d->setValidator(new QIntValidator(1, 10, this));
    ui->LineEdit_ns->setValidator(new QIntValidator(1, 999, this));
    ui->lineEdit_ref->setValidator(new QIntValidator(100, 9999999999LL, this));
    ui->lineEdit_ref->setMaxLength(10);
    ui->lineEdit_ref->setPlaceholderText("Entre 3 et 10 chiffres");
    ui->comboBox_trier->addItems({"Jour", "Horaire", "Capacité", "Salle"});
    afficherAteliers();
    connect(ui->TableWidget, &QTableWidget::itemDoubleClicked, this, [this](QTableWidgetItem *item) {
        int row = item->row();
        ui->lineEdit_ref->setText(ui->TableWidget->item(row, 0)->text());
        ui->LineEdit_nom->setText(ui->TableWidget->item(row, 1)->text());
        ui->LineEdit_cap->setText(ui->TableWidget->item(row, 2)->text());
        ui->LineEdit_capmax->setText(ui->TableWidget->item(row, 3)->text());
        ui->LineEdit_j->setText(ui->TableWidget->item(row, 4)->text());
        ui->LineEdit_d->setText(ui->TableWidget->item(row, 5)->text());
        ui->LineEdit_ns->setText(ui->TableWidget->item(row, 6)->text());
        ui->LineEdit_h->setText(ui->TableWidget->item(row, 7)->text());
        ui->lineEdit_ref->setEnabled(false);
    });
    // ADHERENTS
    QSqlQueryModel* model = A.afficher();
    ui->tableView->setModel(model);
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
void MainWindow::on_adherent_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_afficher_pie_clicked()
{
    QString critere = ui->comboBox_critere_pie->currentText();
    QMap<QString, int> stats = A.statistiques(critere);

    if (stats.isEmpty()) {
        QMessageBox::information(this, "Statistiques", "Aucune donnée trouvée.");
        return;
    }

    int total = 0;
    for (int v : stats.values())
        total += v;

    QPieSeries *series = new QPieSeries();

    for (auto it = stats.begin(); it != stats.end(); ++it) {
        double percentage = (double(it.value()) / total) * 100.0;

        QString label = QString("%1 — %2%")
                            .arg(it.key())
                            .arg(QString::number(percentage, 'f', 1));

        series->append(label, it.value());
    }
    QList<QColor> palette = {
        QColor("#6B8E3A"), QColor("#A7C957"), QColor("#E8A63B"),
        QColor("#F6C453"), QColor("#90BE6D"), QColor("#2F2F2F"),
        QColor("#EA9010"), QColor("#577590"), QColor("#BC4749"),
        QColor("#8ECAE6"), QColor("#FFB703"), QColor("#FB8500"),
        QColor("#6B8E3A"),QColor("#A7C957"),QColor("#F6AA1C"),QColor("#577590"),QColor("#BC4749"),
        QColor("#8ECAE6"),QColor("#FFB703"),QColor("#9B5DE5")
    };
    int i = 0;
    for (QPieSlice *slice : series->slices()) {
        slice->setBrush(palette[i % palette.size()]);
        slice->setLabelVisible(true);

        slice->setLabelPosition(QPieSlice::LabelInsideHorizontal);
        slice->setLabelColor(Qt::white);

        i++;
    }
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques (avec pourcentages) : " + critere);
    chart->setBackgroundBrush(QColor("#F6F5F0"));
    chart->legend()->setVisible(true);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->graphicsView_pie->setScene(nullptr);
    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView_pie);
    ui->graphicsView_pie->setScene(scene);
    scene->addWidget(chartView);
    chartView->resize(ui->graphicsView_pie->size());
}
void MainWindow::on_afficher_bar_clicked()
{
    QString critere = ui->comboBox_critere_bar->currentText();
    QMap<QString, int> stats = A.statistiques(critere);

    if (stats.isEmpty()) {
        QMessageBox::information(this, "Statistiques", "Aucune donnée trouvée.");
        return;
    }
    int total = 0;
    for (int v : stats.values())
        total += v;

    QBarSet *set = new QBarSet("Pourcentage");
    QStringList categories;

    for (auto it = stats.begin(); it != stats.end(); ++it) {
        double percentage = (double(it.value()) / total) * 100.0;
        *set << percentage;

        QString label = QString("%1 — %2%")
                            .arg(it.key())
                            .arg(QString::number(percentage, 'f', 1));

        categories << label;
    }
    set->setBrush(QColor("#6B8E3A"));
    set->setBorderColor(QColor("#2F2F2F"));

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques (en %) : " + critere);
    chart->setBackgroundBrush(QColor("#F6F5F0"));
    chart->legend()->setVisible(false);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsColor(QColor("#2F2F2F"));
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 100);
    axisY->setLabelFormat("%.0f %%");
    axisY->setLabelsColor(QColor("#2F2F2F"));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);

    ui->graphicsView_bar->setScene(nullptr);
    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView_bar);
    ui->graphicsView_bar->setScene(scene);
    scene->addWidget(view);
    view->resize(ui->graphicsView_bar->size());
}
void MainWindow::on_btn_upload_cv_clicked()
{
    int id = ui->lineEdit_uplod->text().toInt();

    if (id <= 0 || !Adherent::idExiste(id)) {
        QMessageBox::warning(this, "Erreur",
                             "Veuillez saisir un ID d'adhérent AVANT de téléverser un CV !");
        return;
    }
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Sélectionner un CV",
        QDir::homePath(),
        "Fichiers PDF (*.pdf)"
        );

    if (filePath.isEmpty())
        return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Erreur", "Impossible de lire le fichier PDF !");
        return;
    }

    QByteArray pdfData = file.readAll();
    file.close();
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

    if (t.contains("asthma") || t.contains("asthme") ||
        t.contains("diabetes") || t.contains("diabète") ||
        t.contains("illness") || t.contains("maladie")) {
        return "sante";
    }

    if (t.contains("football") || t.contains("soccer") ||
        t.contains("basket") || t.contains("swim") ||
        t.contains("natation") || t.contains("sport")) {
        return "sport";
    }

    if (t.contains("drawing") || t.contains("painting") ||
        t.contains("dessin") || t.contains("art") ||
        t.contains("music") || t.contains("musique")) {
        return "art";
    }

    if (t.contains("coding") || t.contains("programming") ||
        t.contains("programmation") || t.contains("python") ||
        t.contains("java") || t.contains("robot")) {
        return "coding";
    }

    if (t.contains("reading") || t.contains("read") ||
        t.contains("livres") || t.contains("books") ||
        t.contains("lecture")) {
        return "lecture";
    }

    if (t.contains("public speaking") || t.contains("presentation") ||
        t.contains("débat") || t.contains("debate") ||
        t.contains("communication")) {
        return "eloquence";
    }

    if (t.contains("science") || t.contains("experiment") ||
        t.contains("laboratory") || t.contains("laboratoire")) {
        return "science";
    }

    return "neutre";
}
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
    else {
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
    QString tempPath = QDir::temp().path() + "/cv_temp_" + QString::number(id) + ".pdf";
    QFile temp(tempPath);

    if (!temp.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'écrire le fichier temporaire !");
        return;
    }
    temp.write(pdfData);
    temp.close();
    QString cvText = extractTextFromPdf(tempPath);

    if (cvText.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur",
                             "Impossible de lire le contenu du CV.");
        return;
    }
    QString profil = determinerProfilDepuisCv(cvText);
    int refAtelier;
    QString nomAtelier, horaireAtelier;

    if (!trouverAtelierPourProfil(profil, refAtelier, nomAtelier, horaireAtelier)) {
        QMessageBox::information(this, "Information",
                                 "Aucun atelier approprié n'a été trouvé pour ce profil.");
        return;
    }
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
void MainWindow::on_fonc_adherent_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    qDebug() << "UPLOAD BUTTON CLICKED!";

}
void MainWindow::on_arduino_data_received(QString uid)
{
    if (uid.isEmpty()) {
        qDebug() << "Empty UID received.";
        return;
    }

    qDebug() << "UID received:" << uid;

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

        QSqlQuery in;
        in.prepare("INSERT INTO PRESENCE (CIN_EMP, DATE_IN) VALUES (:c, SYSDATE)");
        in.bindValue(":c", idEmp);
        in.exec();

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
    QSqlQueryModel* model = E.afficher();

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
    ui->stackedWidget->setCurrentIndex(3);
}


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
    int reference = ui->reference_equipement->text().toInt();
    QString nom = ui->nom_equipement->text();
    int quantite = ui->quantite_equipement->text().toInt();
    QString categorie = ui->categorie_equipement->text();
    double prix = ui->prix_equipement->text().toDouble();

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

    Eq.setReference(reference);
    Eq.setNom(nom);
    Eq.setQuantite(quantite);
    Eq.setCategorie(categorie);
    Eq.setPrix(prix);

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
    QString critere = ui->rech_equipement_input->currentText();
    QString valeur = ui->rech_equipement->text().trimmed();

    if (valeur.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir une valeur à rechercher");
        return;
    }

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

    if (critere == "NOM" || critere == "CATEGORIE") {
        if (valeur.length() < 2) {
            QMessageBox::warning(this, "Erreur", critere + " doit contenir au moins 2 caractères");
            ui->rech_equipement->clear();
            ui->rech_equipement->setFocus();
            return;
        }
    }

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




















void MainWindow::on_envoyer_smsf_btn_clicked()
{
    qDebug() << "***** BOUTON ENVOYER SMS CLIQUE *****";

    QString telephone = ui->lineEdit_telf_sms->text().trimmed();
    QString message = ui->textEdit_messagef_sms->toPlainText().trimmed();

    qDebug() << "Téléphone saisi:" << telephone;
    qDebug() << "Message saisi:" << message;


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

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation d'envoi",
                                  "Êtes-vous sûr de vouloir envoyer ce SMS au numéro:\n"
                                      + telephone + " ?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }

    bool test = Formateur::envoyerSMS(telephone, message);

    if (test) {
        QMessageBox::information(this, "Succès", "SMS envoyé avec succès !");

        ui->lineEdit_telf_sms->clear();
        ui->textEdit_messagef_sms->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'envoi du SMS !");
    }
}

// Métiers Formateurs
void MainWindow::on_rech_forma_btn_clicked()
{

    QString critere = ui->comboBox_recherche_forma->currentText();
    QString valeur = ui->LineEdit_rech_forma->text().trimmed();

    if (valeur.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir une valeur à rechercher");
        return;
    }

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
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_fonctionalitef_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}
void MainWindow::on_fonc_equipement_btn_clicked()
{
     ui->stackedWidget->setCurrentIndex(4);
}

/********************************************
********************************************************
****************************************************************************
****************************************************************************************
****************************************************************************************:
***************************************************************************************/
void MainWindow::on_afficher_bar_equipement_clicked()
{
    QString critere = "categorie";

    QMap<QString, double> stats = Eq.statistiques(critere);
    if (stats.isEmpty()) {
        QMessageBox::information(this, "Statistiques", "Aucune donnée trouvée.");
        return;
    }

    QBarSet *set = new QBarSet("Catégorie (%)");
    QStringList categories;

    for (auto it = stats.begin(); it != stats.end(); ++it) {
        *set << it.value();
        categories << it.key();
    }

    set->setColor(QColor("#6B8E3A"));

    QBarSeries *series = new QBarSeries();
    series->append(set);
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 100);
    axisY->setLabelFormat("%.0f %%");

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chart->setTitle("Statistiques équipements (%) par catégorie");
    chart->setBackgroundBrush(QColor("#F6F5F0"));
    chart->legend()->setVisible(true);

    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView_bar_eq->setScene(scene);
    scene->addWidget(view);
    view->resize(ui->graphicsView_bar_eq->size());
}
void MainWindow::on_afficher_pie_equipement_clicked()
{
    QString critere = "categorie";

    QMap<QString, double> stats = Eq.statistiques(critere);
    if (stats.isEmpty()) {
        QMessageBox::information(this, "Statistiques", "Aucune donnée trouvée.");
        return;
    }
    QPieSeries *series = new QPieSeries();
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        QString lbl = QString("%1 (%2%)")
        .arg(it.key())
            .arg(QString::number(it.value(), 'f', 1));
        series->append(lbl, it.value());
    }

    QList<QColor> palette = {
        QColor("#6B8E3A"), QColor("#A7C957"), QColor("#E8A63B"),
        QColor("#F2C14E"), QColor("#2F2F2F"), QColor("#9A031E"),
        QColor("#5F0F40"), QColor("#0F4C5C")
    };

    int i = 0;
    for (QPieSlice *slice : series->slices()) {
        slice->setBrush(palette[i % palette.size()]);
        slice->setLabelVisible(true);
        slice->setLabelPosition(QPieSlice::LabelInsideHorizontal);
        slice->setLabelColor(Qt::white);
        i++;
    }
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des équipements par catégorie (%)");
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setBackgroundBrush(QColor("#F6F5F0"));
    QChartView *view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView_pie_eq->setScene(scene);

    scene->addWidget(view);
    view->resize(ui->graphicsView_pie_eq->size());
}

//*ATelier***********************
/*****************************************
************µµµµµµµµµµµµµµµµµµµµµµµ*zeineb µµµµµµ*/

void MainWindow::afficherAteliers()
{
    ui->TableWidget->clearContents();
    ui->TableWidget->setRowCount(0);
    QSqlQueryModel *model = Atmp.afficher();
    if (!model || model->rowCount() == 0) { delete model; return; }

    for (int i = 0; i < model->rowCount(); ++i) {
        ui->TableWidget->insertRow(i);
        for (int c = 0; c < 8; ++c) {
            QString val = model->record(i).value(c).toString();
            QTableWidgetItem *item = new QTableWidgetItem(val);
            item->setTextAlignment(Qt::AlignCenter);
            if (c == 2 || c == 3) {
                int cap = model->record(i).value(2).toInt();
                int max = model->record(i).value(3).toInt();
                if (cap >= max && max > 0) {
                    item->setBackground(QColor(255, 182, 193));
                    item->setForeground(Qt::darkRed);
                    item->setFont(QFont("", -1, QFont::Bold));
                }
            }
            ui->TableWidget->setItem(i, c, item);
        }
    }
    delete model;
    ui->TableWidget->resizeColumnsToContents();
}

void MainWindow::on_pushButton_ajouterAtelier_clicked()
{
    QString ref = ui->lineEdit_ref->text().trimmed();
    if (ref.length() < 3 || ref.length() > 10) {
        QMessageBox::warning(this, "Erreur", "Référence : 3 à 10 chiffres");
        return;
    }
    QString nom = ui->LineEdit_nom->text().trimmed();
    int cap = ui->LineEdit_cap->text().toInt();
    int cap_max = ui->LineEdit_capmax->text().toInt();
    QString jour = ui->LineEdit_j->text().trimmed();
    QString horaire = ui->LineEdit_h->text().trimmed();
    int duree = ui->LineEdit_d->text().toInt();
    int salle = ui->LineEdit_ns->text().toInt();

    if (nom.isEmpty() || jour.isEmpty() || horaire.isEmpty() || cap_max < 10) {
        QMessageBox::warning(this, "Erreur", "Champs obligatoires ! Capacité Max ≥ 10");
        return;
    }

    Atelier a(ref, nom, cap, cap_max, jour, horaire, duree, salle);
    if (a.ajouter()) {
        QMessageBox::information(this, "Succès", "Atelier ajouté !");
        afficherAteliers();
        on_pushButton_annulerAteliers_clicked();
    } else {
        QMessageBox::critical(this, "Échec", "Référence existe déjà !");
    }
}


void MainWindow::on_pushButton_annulerAteliers_clicked()
{
    ui->lineEdit_ref->clear();
    ui->LineEdit_nom->clear();
    ui->LineEdit_cap->clear();
    ui->LineEdit_capmax->clear();
    ui->LineEdit_j->clear();
    ui->LineEdit_d->clear();
    ui->LineEdit_ns->clear();
    ui->LineEdit_h->clear();
    ui->lineEdit_ref->setEnabled(true);
    ui->lineEdit_recherche->clear();
    afficherAteliers();
}

void MainWindow::on_pushButton_trierAteliers_clicked()
{
    QString critere = ui->comboBox_trier->currentText();
    ui->TableWidget->clearContents(); ui->TableWidget->setRowCount(0);

    QSqlQuery query;
    QString sql = "SELECT REFERENCE, NOM_ATELIER, CAPACITE, CAPACITE_MAX, JOUR, DUREE, NUM_SALLE, HORAIRE FROM ATELIER";

    if (critere == "Jour")
        sql += " ORDER BY CASE JOUR WHEN 'Lundi' THEN 1 WHEN 'Mardi' THEN 2 WHEN 'Mercredi' THEN 3 WHEN 'Jeudi' THEN 4 WHEN 'Vendredi' THEN 5 WHEN 'Samedi' THEN 6 WHEN 'Dimanche' THEN 7 ELSE 99 END";
    else if (critere == "Horaire") sql += " ORDER BY HORAIRE";
    else if (critere == "Capacité") sql += " ORDER BY CAPACITE_MAX DESC";
    else if (critere == "Salle") sql += " ORDER BY NUM_SALLE";

    if (!query.exec(sql)) { QMessageBox::critical(this, "Erreur", query.lastError().text()); return; }

    int row = 0;
    while (query.next()) {
        ui->TableWidget->insertRow(row);
        for (int col = 0; col < 8; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            item->setTextAlignment(Qt::AlignCenter);
            if (col == 2 || col == 3) {
                int cap = query.value(2).toInt(), max = query.value(3).toInt();
                if (cap >= max && max > 0) {
                    item->setBackground(QColor(255,182,193));
                    item->setForeground(Qt::darkRed);
                    item->setFont(QFont("", -1, QFont::Bold));
                }
            }
            ui->TableWidget->setItem(row, col, item);
        }
        ++row;
    }
    ui->TableWidget->resizeColumnsToContents();
}

void MainWindow::on_pushButton_rechercherAtelier_clicked()
{
    QString critere = ui->comboBox_recherche_2->currentText().trimmed();
    QString valeur = ui->lineEdit_recherche->text().trimmed();

    ui->TableWidget->clearContents();
    ui->TableWidget->setRowCount(0);

    if (valeur.isEmpty()) {
        afficherAteliers();
        return;
    }

    // normalisation AVANT comparaison
    QString crit = critere.toLower().replace("’","'");

    QSqlQuery query;
    QString sql;

    if (crit.contains("référence") || crit.contains("reference")) {
        sql = "SELECT * FROM ATELIER WHERE REFERENCE LIKE :v ORDER BY REFERENCE";
        query.prepare(sql);
        query.bindValue(":v", "%" + valeur + "%");
    }
    else if (crit.contains("nom")) {
        sql = "SELECT * FROM ATELIER WHERE UPPER(NOM_ATELIER) LIKE UPPER(:v) ORDER BY NOM_ATELIER";
        query.prepare(sql);
        query.bindValue(":v", "%" + valeur + "%");
    }
    else if (crit.contains("salle")) {
        bool ok;
        int salle = valeur.toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Erreur", "Numéro de salle invalide !");
            return;
        }
        sql = "SELECT * FROM ATELIER WHERE NUM_SALLE = :s ORDER BY NUM_SALLE";
        query.prepare(sql);
        query.bindValue(":s", salle);
    }

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL", query.lastError().text());
        return;
    }

    int row = 0;
    while (query.next()) {
        ui->TableWidget->insertRow(row);
        for (int col = 0; col < 8; ++col) {
            QTableWidgetItem *item =
                new QTableWidgetItem(query.value(col).toString());
            item->setTextAlignment(Qt::AlignCenter);

            if (col == 2 || col == 3) {
                int cap  = query.value(2).toInt();
                int max  = query.value(3).toInt();
                if (cap >= max) {
                    item->setBackground(QColor(255,182,193));
                    item->setForeground(Qt::darkRed);
                    item->setFont(QFont("", -1, QFont::Bold));
                }
            }
            ui->TableWidget->setItem(row, col, item);
        }
        row++;
    }

    if (row == 0)
        QMessageBox::information(this, "Recherche", "Aucun atelier trouvé !");
}


void MainWindow::on_pushButton_calendrier_clicked()
{
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Calendrier des Ateliers - Smart Summer Club");
    dialog->resize(1300, 750);

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    QLabel *titre = new QLabel("📅 Calendrier des Ateliers");
    titre->setAlignment(Qt::AlignCenter);
    titre->setStyleSheet("background: #e3f2fd; padding: 20px; font-size: 22pt; font-weight: bold; color: #1565c0;");
    layout->addWidget(titre);

    QTableWidget *calendrier = new QTableWidget(0, 8, dialog);
    QStringList headers = {"Heure", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};
    calendrier->setHorizontalHeaderLabels(headers);
    calendrier->verticalHeader()->setVisible(false);
    calendrier->setStyleSheet(
        "QTableWidget { gridline-color: #bdbdbd; background-color: #ffffff; }"
        "QHeaderView::section { background: #1976d2; color: white; padding: 14px; font-weight: bold; }"
        );

    QSqlQuery query;
    if (!query.exec("SELECT JOUR, HORAIRE, REFERENCE, NOM_ATELIER, NUM_SALLE, CAPACITE, CAPACITE_MAX FROM ATELIER ORDER BY HORAIRE")) {
        QMessageBox::critical(this, "Erreur", query.lastError().text());
        delete dialog;
        return;
    }

    QMap<QString, QMap<QString, QList<QStringList>>> planning;
    QSet<QString> heuresSet;

    while (query.next()) {
        QString jour = query.value(0).toString().trimmed();
        QString horaire = query.value(1).toString().trimmed();
        QString ref = query.value(2).toString();
        QString nom = query.value(3).toString();
        int salle = query.value(4).toInt();
        int cap = query.value(5).toInt();
        int cap_max = query.value(6).toInt();
        int restant = cap_max - cap;

        planning[jour][horaire] << (QStringList() << ref << nom << QString::number(salle) << QString::number(cap) << QString::number(cap_max) << QString::number(restant));
        heuresSet << horaire;
    }

    QStringList heures = heuresSet.values();
    std::sort(heures.begin(), heures.end());

    calendrier->setRowCount(heures.size());

    for (int i = 0; i < heures.size(); ++i) {
        QString h = heures[i];
        QTableWidgetItem *itemHeure = new QTableWidgetItem(h);
        itemHeure->setBackground(QColor("#e8eaf6"));
        itemHeure->setFont(QFont("Arial", 11, QFont::Bold));
        itemHeure->setTextAlignment(Qt::AlignCenter);
        calendrier->setItem(i, 0, itemHeure);

        for (int j = 0; j < 7; ++j) {
            QString jour = headers[j + 1];
            auto &map = planning[jour];

            if (map.contains(h) && !map[h].isEmpty()) {
                QWidget *container = new QWidget();
                QVBoxLayout *vlayout = new QVBoxLayout(container);
                vlayout->setSpacing(6);
                vlayout->setContentsMargins(8, 8, 8, 8);

                for (const auto &data : map[h]) {
                    QString ref = data[0];
                    QString nom = data[1];
                    QString salle = data[2];
                    int restant = data[5].toInt();

                    QLabel *label = new QLabel();
                    QString color = (restant <= 0) ? "#ffebee" : "#e8f5e9";
                    QString border = (restant <= 0) ? "#d32f2f" : "#43a047";
                    QString status = (restant <= 0) ? "Complet" : QString("%1 places").arg(restant);

                    label->setText(QString(
                                       "<div style='background:%1; border-left:5px solid %2; padding:10px; border-radius:6px; font-size:10pt;'>"
                                       "<b style='color:#1a237e;'>%3</b><br>"
                                       "<span style='color:#424242; font-weight:bold;'>%4</span><br>"
                                       "<span style='color:#616161;'>Salle %5 | %6</span>"
                                       "</div>"
                                       ).arg(color, border, ref, nom, salle, status));

                    vlayout->addWidget(label);
                }
                calendrier->setCellWidget(i, j + 1, container);
            } else {
                QTableWidgetItem *empty = new QTableWidgetItem("— Aucun atelier —");
                empty->setTextAlignment(Qt::AlignCenter);
                empty->setBackground(QColor("#f5f5f5"));
                empty->setForeground(QColor("#9e9e9e"));
                calendrier->setItem(i, j + 1, empty);
            }
        }
        calendrier->setRowHeight(i, 140);
    }

    calendrier->setColumnWidth(0, 90);
    for (int c = 1; c < 8; ++c) calendrier->setColumnWidth(c, 180);

    layout->addWidget(calendrier);

    QPushButton *btnClose = new QPushButton("Fermer");
    btnClose->setStyleSheet("QPushButton { background:#d32f2f; color:white; padding:12px; font-weight:bold; border-radius:6px; }");
    connect(btnClose, &QPushButton::clicked, dialog, &QDialog::accept);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnClose);
    btnLayout->addStretch();
    layout->addLayout(btnLayout);

    dialog->exec();
    delete dialog;
}
void MainWindow::on_pushButton_modifierAtelier_clicked()
{
    QString ref = ui->lineEdit_ref->text();
    if (ref.isEmpty()) {
        QMessageBox::warning(this, "Sélection", "Double-cliquez sur un atelier à modifier.");
        return;
    }
    Atelier a;
    a.setReference(ref);
    a.setNomAtelier(ui->LineEdit_nom->text());
    a.setCapacite(ui->LineEdit_cap->text().toInt());
    a.setCapaciteMax(ui->LineEdit_capmax->text().toInt());
    a.setJour(ui->LineEdit_j->text());
    a.setHoraire(ui->LineEdit_h->text());
    a.setDuree(ui->LineEdit_d->text().toInt());
    a.setNumeroSalle(ui->LineEdit_ns->text().toInt());

    if (a.modifier()) {
        QMessageBox::information(this, "Succès", "Atelier modifié !");
        afficherAteliers();
        on_pushButton_annulerAteliers_clicked();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification.");
    }
}

void MainWindow::on_pushButton_supprimerAteliers_clicked()
{
    QString ref = ui->lineEdit_ref->text();
    if (ref.isEmpty()) {
        QMessageBox::warning(this, "Sélection", "Sélectionnez un atelier à supprimer.");
        return;
    }
    if (QMessageBox::question(this, "Confirmer", "Supprimer l'atelier <b>" + ref + "</b> ?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        if (Atmp.supprimer(ref)) {
            QMessageBox::information(this, "Succès", "Atelier supprimé !");
            afficherAteliers();
            on_pushButton_annulerAteliers_clicked();
        }
    }
}


void MainWindow::on_pushButton_pdf_clicked()
{
    QSqlQueryModel* model = Atmp.afficher();
    if (!model || model->rowCount() == 0) {
        QMessageBox::information(this, "PDF", "Aucun atelier !");
        delete model;
        return;
    }

    QString html = R"(
    <html><head><style>
        body {font-family:Arial;margin:40px;}
        h1 {color:#c62828;text-align:center;}
        table {width:100%;border-collapse:collapse;margin:25px 0;}
        th,td {border:1px solid #333;padding:12px;text-align:center;}
        th {background:#1976d2;color:white;}
        tr:nth-child(even) {background:#f0f8ff;}
    </style></head><body>
    <h1>LISTE DES ATELIERS - SMART SUMMER CLUB</h1>
    <p style="text-align:center;"><i>Généré le )" + QDateTime::currentDateTime().toString("dd/MM/yyyy à hh:mm") + R"(</i></p>
    <p style="text-align:center;font-weight:bold;">Total : )" + QString::number(model->rowCount()) + R"( ateliers</p>
    <table>
        <tr><th>Réf</th><th>Nom</th><th>Capacité</th><th>Capacité Max</th><th>Jour</th><th>Horaire</th><th>Durée</th><th>Salle</th></tr>)";

    for (int i = 0; i < model->rowCount(); ++i) {
        QString ref = model->record(i).value(0).toString();
        bool ok;
        int n = ref.toInt(&ok);
        if (ok) ref = QString("%1").arg(n, 6, 10, QChar('0'));

        html += "<tr>";
        html += "<td><b>" + ref + "</b></td>";
        html += "<td>" + model->record(i).value(1).toString() + "</td>";
        html += "<td>" + model->record(i).value(2).toString() + "</td>";
        html += "<td><b>" + model->record(i).value(3).toString() + "</b></td>";
        html += "<td><b>" + model->record(i).value(4).toString().toUpper() + "</b></td>";
        html += "<td>" + model->record(i).value(7).toString() + "</td>";
        html += "<td>" + model->record(i).value(5).toString() + "</td>";
        html += "<td><b>" + model->record(i).value(6).toString() + "</b></td>";
        html += "</tr>";
    }

    html += R"(</table>
        <div style="text-align:center;margin-top:50px;color:#777;">
            © 2025-2026 ESPRIT - Smart Summer Club
        </div>
    </body></html>)";

    QString file = QFileDialog::getSaveFileName(this, "Exporter PDF",
                                                QDir::homePath() + "/Ateliers_" + QDate::currentDate().toString("yyyy-MM-dd") + ".pdf", "PDF (*.pdf)");

    if (!file.isEmpty()) {
        QTextDocument doc;
        doc.setHtml(html);
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(file);
        doc.print(&printer);
        QMessageBox::information(this, "Succès", "PDF généré :\n" + file);
    }
    delete model;
}
void MainWindow::on_btnExporterPDF_clicked()
{

    QAbstractItemModel *model = ui->tab_employe->model();

    if (!model) {
        QMessageBox::warning(this, "Erreur", "Aucune donnée à exporter !");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Exporter PDF", "", "PDF (*.pdf)");
    if (fileName.isEmpty()) return;
    QPdfWriter pdf(fileName);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setPageOrientation(QPageLayout::Landscape);
    pdf.setPageMargins(QMarginsF(40, 40, 40, 40));
    pdf.setResolution(300);

    QPainter painter(&pdf);

    const int margin = 60;
    const int pageWidth = pdf.width() - 2 * margin;
    int x = margin;
    int y = margin;
    painter.setFont(QFont("Arial", 28, QFont::Bold));
    painter.drawText(x, y + 40, "Liste des employés");
    y += 120;
    int numCols = model->columnCount();
    QVector<int> colWidths(numCols);

    QFont headerFont("Arial", 11, QFont::Bold);
    QFont cellFont("Arial", 9);
    QFontMetrics fmHeader(headerFont);
    QFontMetrics fmCell(cellFont);
    for (int col = 0; col < numCols; ++col) {
        QString header = model->headerData(col, Qt::Horizontal).toString().toLower();

        int w = fmHeader.horizontalAdvance(model->headerData(col, Qt::Horizontal).toString()) + 60;

        for (int row = 0; row < model->rowCount(); ++row) {
            QString cell = model->data(model->index(row, col)).toString();
            QRect rect = fmCell.boundingRect(0, 0, 2000, 200,
                                             Qt::AlignLeft | Qt::TextWordWrap, cell);
            w = qMax(w, rect.width() + 50);
        }
        if (header.contains("email"))
            w = qMax(w, 620);
        else if (header.contains("mot") || header.contains("pass"))
            w = qMax(w, 300);
        else if (header.contains("tel"))
            w = qMax(w, 250);
        else if (header.contains("poste"))
            w = qMax(w, 200);
        else if (header.contains("nom") || header.contains("prénom"))
            w = qMax(w, 220);
        else if (header.contains("id"))
            w = qMax(w, 100);
        else
            w = qMax(w, 160);

        colWidths[col] = qMin(w, 800);
    }

    int totalFixed = 0;
    int emailCol = -1;

    for (int i = 0; i < numCols; ++i) {
        QString h = model->headerData(i, Qt::Horizontal).toString().toLower();
        if (h.contains("email"))
            emailCol = i;
        else
            totalFixed += colWidths[i];
    }

    if (emailCol != -1) {
        int available = pageWidth - totalFixed - 100;
        colWidths[emailCol] = qMax(colWidths[emailCol], available);
    }

    const int rowHeight = 75;
    int currentPage = 1;
    auto drawHeader = [&]() {
        painter.setFont(headerFont);
        int cx = x;
        for (int col = 0; col < numCols; ++col) {
            painter.drawRect(cx, y, colWidths[col], rowHeight);
            painter.drawText(QRect(cx + 10, y + 8, colWidths[col] - 20, rowHeight - 10),
                             Qt::AlignCenter,
                             model->headerData(col, Qt::Horizontal).toString());
            cx += colWidths[col];
        }
        y += rowHeight;
    };

    drawHeader();

    painter.setFont(cellFont);
    for (int row = 0; row < model->rowCount(); ++row) {

        if (y > pdf.height() - 180) {
            painter.setFont(QFont("Arial", 9, QFont::StyleItalic));
            painter.drawText(pdf.width() - 300, pdf.height() - 40,
                             QString("Page %1").arg(currentPage++));

            pdf.newPage();
            y = margin + 60;

            painter.setFont(QFont("Arial", 24, QFont::Bold));
            painter.drawText(x, y, "Liste des employés (suite)");
            y += 80;
            drawHeader();
        }

        int cx = x;
        for (int col = 0; col < numCols; ++col) {
            QString text = model->data(model->index(row, col)).toString();

            painter.drawRect(cx, y, colWidths[col], rowHeight);

            QRect textRect(cx + 12, y + 8, colWidths[col] - 24, rowHeight - 16);
            painter.drawText(textRect,
                             Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap,
                             text);

            cx += colWidths[col];
        }
        y += rowHeight;
    }

    painter.setFont(QFont("Arial", 9, QFont::StyleItalic));
    painter.drawText(pdf.width() - 300, pdf.height() - 40,
                     QString("Page %1").arg(currentPage));

    painter.end();

    QMessageBox::information(this, "Export PDF",
                             "PDF généré avec succès !");
}
//INNVHIBA
void MainWindow::on_btnFonctionalite_clicked()
{
    QSqlQuery query("SELECT poste, COUNT(*) FROM employes GROUP BY poste");

    QPieSeries *series = new QPieSeries();
    QString resultat = "📊 Statistiques des employés par poste :\n\n";

    while (query.next()) {
        QString poste = query.value(0).toString();
        int nombre = query.value(1).toInt();

        series->append(poste + " (" + QString::number(nombre) + ")", nombre);
        resultat += poste + " : " + QString::number(nombre) + "\n";
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des employés par poste");
    chart->legend()->setAlignment(Qt::AlignRight);

    if (!series->slices().isEmpty()) {
        series->slices().first()->setExploded(true);
        series->slices().first()->setLabelVisible(true);
    }


    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Statistiques");
    dialog->resize(600, 500);

    QVBoxLayout *layout = new QVBoxLayout(dialog);

    QLabel *label = new QLabel(resultat);
    label->setStyleSheet("font-size: 16px; padding: 10px;");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    layout->addWidget(label);
    layout->addWidget(chartView);

    dialog->setLayout(layout);
    dialog->exec();
}
void MainWindow::on_btnEnvoyerMail_clicked()
{
    QString emailClient = ui->lineEditEmailClient->text().trimmed();
    if (emailClient.isEmpty()) {
        QMessageBox::warning(this, "Email manquant",
                             "Veuillez saisir l'adresse e-mail du client dans le champ.");
        ui->lineEditEmailClient->setFocus();
        return;
    }

    QRegularExpression regex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    if (!regex.match(emailClient).hasMatch()) {
        QMessageBox::warning(this, "Format incorrect",
                             "L'adresse e-mail n'est pas valide.\nExemple : nom@gmail.com");
        ui->lineEditEmailClient->setFocus();
        return;
    }

    QString sujet = "Notification importante - Changement d'emploi";
    QString corps =
        "Bonjour,\n\n"
        "Nous vous informons que votre emploi a été mise à jour dans notre système.\n\n"
        "Si vous avez des questions, n’hésitez pas à nous contacter.\n\n"
        "Cordialement,\n"
        "L'équipe RH\n"
        "Smart summer club";
    QString url = QString(
                      "https://mail.google.com/mail/?view=cm&fs=1"
                      "&to=%1"
                      "&su=%2"
                      "&body=%3"
                      )
                      .arg(QUrl::toPercentEncoding(emailClient))
                      .arg(QUrl::toPercentEncoding(sujet))
                      .arg(QUrl::toPercentEncoding(corps));

    bool ouvert = QDesktopServices::openUrl(QUrl(url));

    if (ouvert) {
        ui->labelEmailClient->setText("E-mail en cours de rédaction pour : " + emailClient);
        ui->labelEmailClient->setStyleSheet("color: green; font-weight: bold;");
        QMessageBox::information(this, "Prêt à envoyer",
                                 "Gmail s'est ouvert avec le message pré-rempli.\n"
                                 "Il ne reste plus qu'à cliquer sur Envoyer !");
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le navigateur.");
    }
}
void MainWindow::on_ateliers_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_fonctionalitbtn_atelier_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}
void MainWindow::on_afficher_pie_atelier_clicked()
{
    QMap<QString, int> stats = Atmp.statistiquesJour(); // objet Atelier AT

    if (stats.isEmpty()) {
        QMessageBox::information(this, "Statistiques Atelier",
                                 "Aucune donnée trouvée.");
        return;
    }

    int total = 0;
    for (int v : stats.values())
        total += v;
    QPieSeries *series = new QPieSeries();

    for (auto it = stats.begin(); it != stats.end(); ++it) {
        double percentage = (double(it.value()) / total) * 100.0;

        QString label = QString("%1 — %2%")
                            .arg(it.key())
                            .arg(QString::number(percentage, 'f', 1));

        series->append(label, it.value());
    }

    QList<QColor> palette = {
        QColor("#6B8E3A"), QColor("#A7C957"), QColor("#F6AA1C"),
        QColor("#577590"), QColor("#BC4749"), QColor("#8ECAE6")
    };

    int i = 0;
    for (QPieSlice *slice : series->slices()) {
        slice->setBrush(palette[i % palette.size()]);
        slice->setLabelVisible(true);
        slice->setLabelPosition(QPieSlice::LabelInsideHorizontal);
        slice->setLabelColor(Qt::white);
        i++;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des Ateliers par Jour (%)");
    chart->setBackgroundBrush(QColor("#F6F5F0"));

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->graphicsView_atelier->setScene(nullptr);
    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView_atelier);
    ui->graphicsView_atelier->setScene(scene);

    scene->addWidget(chartView);
    chartView->resize(ui->graphicsView_atelier->size());
}
void MainWindow::on_afficher_pie_atelier2_clicked()
{
    QMap<QString, int> stats = Atmp.statistiquesCapacite();

    if (stats.isEmpty()) {
        QMessageBox::information(this, "Statistiques Atelier", "Aucune donnée trouvée.");
        return;
    }

    int total = 0;
    for (int v : stats.values())
        total += v;

    QPieSeries *series = new QPieSeries();

    for (auto it = stats.begin(); it != stats.end(); ++it) {
        double percentage = (double(it.value()) / total) * 100.0;
        QString label = QString("Capacité %1 — %2%")
                            .arg(it.key())
                            .arg(QString::number(percentage, 'f', 1));
        series->append(label, it.value());
    }

    QList<QColor> palette = {
        QColor("#6B8E3A"), QColor("#A7C957"), QColor("#F6AA1C"),
        QColor("#577590"), QColor("#BC4749"), QColor("#8ECAE6"),
        QColor("#FFB703"), QColor("#9B5DE5")
    };

    int i = 0;
    for (QPieSlice *slice : series->slices()) {
        slice->setBrush(palette[i % palette.size()]);
        slice->setLabelVisible(true);
        slice->setLabelPosition(QPieSlice::LabelInsideHorizontal);
        slice->setLabelColor(Qt::white);
        i++;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des Ateliers par Capacité (%)");
    chart->setBackgroundBrush(QColor("#F6F5F0"));

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->graphicsView_atelier->setScene(nullptr);
    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView_atelier);
    ui->graphicsView_atelier->setScene(scene);

    scene->addWidget(chartView);
    chartView->resize(ui->graphicsView_atelier->size());
}
