#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QStyledItemDelegate>
#include <QVariant>
#include <QLocale>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QInputDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>



class PasswordDelegate : public QStyledItemDelegate {
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    QString displayText(const QVariant &value, const QLocale &) const override {
        return QString(value.toString().length(), '*');
    }
};

QString getColumnName(const QString &critere)
{
    QString c = critere.toLower().trimmed();

    // ⚠️ Important : 'prenom' avant 'nom'
    if (c == "prenom" || c.contains("prén") || c.contains("pre"))
        return "Prenom";

    if (c == "nom")
        return "Nom";

    if (c == "email" || c == "mail")
        return "Email";

    if (c == "id")
        return "id";

    return "";
}

// ✅ Créer la table SQLite si elle n'existe pas
void MainWindow::creerTable()
{
    QSqlQuery query;
    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS employes ("
            "id INTEGER PRIMARY KEY ,"
            "nom TEXT,"
            "prenom TEXT,"
            "poste TEXT,"
            "email TEXT,"
            "motdepasse TEXT,"
            "telephone TEXT"
            ");"))
    {
        qDebug() << "Erreur création table :" << query.lastError().text();
    }
}


// ✅ Constructeur
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(nullptr)
{
    ui->setupUi(this);
    connect(ui->btnEnvoyerMail, &QPushButton::clicked, this, &MainWindow::on_btnEnvoyerMail_clicked);

    // Connexion SQLite
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("employe.db");

    if (!db.open()) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir la base : " + db.lastError().text());
        return;
    }

    // Création de la table si nécessaire
    creerTable();
    QSqlQuery q("PRAGMA table_info(employes);");
    while (q.next()) {
        qDebug() << "Colonne :" << q.value(1).toString();
    }

    // Configuration du modèle
    model = new QSqlTableModel(this, db);
    model->setTable("employes");
    model->setEditStrategy(QSqlTableModel::OnFieldChange); // modification automatique si modifié dans tableView
    model->select();

    // Affichage dans le tableau
    // Affichage dans le tableau
    ui->tableView->setModel(model);

    // Masquer le mot de passe derrière des étoiles
    int colMdp = model->fieldIndex("motdepasse");
    ui->tableView->setItemDelegateForColumn(colMdp, new PasswordDelegate(this));

    ui->tableView->resizeColumnsToContents();
    connect(ui->btnAscendant, &QPushButton::clicked, this, [=]() {
        ordreTri = Qt::AscendingOrder;
    });

    connect(ui->btnDescendant, &QPushButton::clicked, this, [=]() {
        ordreTri = Qt::DescendingOrder;
    });

    connect(ui->btnTrier, &QPushButton::clicked, this, &MainWindow::appliquerTri);
    connect(ui->btnFonctionalite, &QPushButton::clicked,
            this, &MainWindow::on_btnFonctionalite_clicked);
    connect(ui->btnMotDePasseOublie, &QPushButton::clicked,
            this, &MainWindow::on_btnMotDePasseOublie_clicked);







}




// ✅ Destructeur
MainWindow::~MainWindow()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) db.close();
    delete ui;
}

// ✅ Afficher tous les employés
void MainWindow::afficherEmployes()
{
    model->select();          // Recharge les données depuis SQLite
    ui->tableView->reset();   // Force l’actualisation du tableau
    ui->tableView->resizeColumnsToContents(); // Ajuste les colonnes automatiquement
}


// ✅ Ajouter un employé
void MainWindow::on_btnAjouter_clicked()
{
    if(ui->lineEditID->text().isEmpty() || ui->lineEditNom->text().isEmpty() || ui->lineEditEmail->text().isEmpty()) {
        QMessageBox::warning(this,"Erreur","L'ID, le nom et l'email sont obligatoires !");
        return;
    }

    bool ok;
    int id = ui->lineEditID->text().toInt(&ok);
    if(!ok) {
        QMessageBox::warning(this,"Erreur","L'ID doit être un nombre !");
        return;
    }

    QSqlRecord record = model->record();
    record.setValue("id", id);  // ← utilise l'ID saisi
    record.setValue("nom", ui->lineEditNom->text());
    record.setValue("prenom", ui->lineEditPrenom->text());
    record.setValue("poste", ui->lineEditPoste->text());
    record.setValue("email", ui->lineEditEmail->text());
    record.setValue("motdepasse", ui->lineEditMotdepasse->text());
    record.setValue("telephone", ui->lineEditTelephone->text());

    if(model->insertRecord(-1, record)) {
        if(model->submitAll()) {
            model->select(); // 🔄 rafraîchir la table
            QMessageBox::information(this,"Succès","Employé ajouté !");

            // Effacer les champs
            ui->lineEditID->clear();
            ui->lineEditNom->clear();
            ui->lineEditPrenom->clear();
            ui->lineEditPoste->clear();
            ui->lineEditEmail->clear();
            ui->lineEditMotdepasse->clear();
            ui->lineEditTelephone->clear();
        } else {
            QMessageBox::warning(this,"Erreur","Impossible d'ajouter : " + model->lastError().text());
        }
    } else {
        QMessageBox::warning(this,"Erreur","Impossible d'ajouter : " + model->lastError().text());
    }
}



// ✅ Modifier un employé à partir de l'ID
void MainWindow::on_btnModifier_clicked()
{
    QString id = ui->lineEditID->text().trimmed();
    if(id.isEmpty()) {
        QMessageBox::warning(this,"Erreur","Veuillez entrer l'ID de l'employé !");
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE employes SET nom=:nom, prenom=:prenom, poste=:poste, email=:email, motdepasse=:motdepasse, telephone=:telephone WHERE id=:id");
    query.bindValue(":nom", ui->lineEditNom->text());
    query.bindValue(":prenom", ui->lineEditPrenom->text());
    query.bindValue(":poste", ui->lineEditPoste->text());
    query.bindValue(":email", ui->lineEditEmail->text());
    query.bindValue(":motdepasse", ui->lineEditMotdepasse->text());
    query.bindValue(":telephone", ui->lineEditTelephone->text());
    query.bindValue(":id", id);

    if(query.exec()) {
        if(query.numRowsAffected() > 0) {
            model->select(); // 🔄 rafraîchir le tableau
            QMessageBox::information(this,"Succès","Employé modifié !");
        } else {
            QMessageBox::warning(this,"Erreur","Aucun employé trouvé avec cet ID.");
        }
    } else {
        QMessageBox::warning(this,"Erreur","Modification échouée : " + query.lastError().text());
    }
}

// ✅ Supprimer un employé à partir de l'email
void MainWindow::on_btnSupprimer_clicked()
{
    QString email = ui->lineEditEmail->text().trimmed();
    if(email.isEmpty()) {
        QMessageBox::warning(this,"Erreur","Veuillez entrer l'email de l'employé !");
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM employes WHERE email=:email");
    query.bindValue(":email", email);

    if(query.exec()) {
        if(query.numRowsAffected() > 0) {
            model->select(); // 🔄 rafraîchir le tableau
            QMessageBox::information(this,"Succès","Employé supprimé !");
        } else {
            QMessageBox::warning(this,"Erreur","Aucun employé trouvé avec cet email.");
        }
    } else {
        QMessageBox::warning(this,"Erreur","Suppression échouée : " + query.lastError().text());
    }
}


void MainWindow::on_btnEnvoyerMail_clicked()
{
    // 1. Récupérer l'email saisi dans le lineEditEmailClient
    QString emailClient = ui->lineEditEmailClient->text().trimmed();

    // 2. Vérifier qu'il n'est pas vide
    if (emailClient.isEmpty()) {
        QMessageBox::warning(this, "Email manquant",
                             "Veuillez saisir l'adresse e-mail du client dans le champ.");
        ui->lineEditEmailClient->setFocus();
        return;
    }

    // 3. Vérifier le format de l'email (très fiable)
    QRegularExpression regex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    if (!regex.match(emailClient).hasMatch()) {
        QMessageBox::warning(this, "Format incorrect",
                             "L'adresse e-mail n'est pas valide.\nExemple : nom@gmail.com");
        ui->lineEditEmailClient->setFocus();
        return;
    }


    // 4. Sujet et corps du message (tu peux personnaliser ici)
    QString sujet = "Notification importante - Changement d'emploi";
    QString corps =
        "Bonjour,\n\n"
        "Nous vous informons que votre emploi a été mise à jour dans notre système.\n\n"
        "Si vous avez des questions, n’hésitez pas à nous contacter.\n\n"
        "Cordialement,\n"
        "L'équipe RH\n"
        "Smart summer club";


    // 5. Construire l'URL Gmail (ouvre un nouvel onglet prêt à envoyer)
    QString url = QString(
                      "https://mail.google.com/mail/?view=cm&fs=1"
                      "&to=%1"
                      "&su=%2"
                      "&body=%3"
                      )
                      .arg(QUrl::toPercentEncoding(emailClient))
                      .arg(QUrl::toPercentEncoding(sujet))
                      .arg(QUrl::toPercentEncoding(corps));

    // 6. Ouvrir Gmail dans le navigateur par défaut
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
void MainWindow::on_btnExporterPDF_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter PDF", "", "PDF (*.pdf)");
    if (fileName.isEmpty()) return;

    QPdfWriter pdf(fileName);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setPageOrientation(QPageLayout::Landscape);
    pdf.setPageMargins(QMarginsF(50, 50, 50, 50)); // marges réduites pour gagner de l'espace
    pdf.setResolution(300);

    QPainter painter(&pdf);

    const int margin = 60;
    const int pageWidth = pdf.width() - 2 * margin;
    int x = margin;
    int y = margin;

    // === TITRE ===
    painter.setFont(QFont("Arial", 28, QFont::Bold));
    painter.drawText(x, y + 40, "Liste des employés");
    y += 120;

    int numCols = model->columnCount();
    QVector<int> colWidths(numCols);

    QFont headerFont("Arial", 11, QFont::Bold);
    QFont cellFont("Arial", 9);
    QFontMetrics fmHeader(headerFont);
    QFontMetrics fmCell(cellFont);

    // === CALCUL DES LARGEURS (EMAIL PRIORITAIRE) ===
    for (int col = 0; col < numCols; ++col) {
        QString header = model->headerData(col, Qt::Horizontal).toString().toLower();

        int w = fmHeader.horizontalAdvance(model->headerData(col, Qt::Horizontal).toString()) + 60;

        for (int row = 0; row < model->rowCount(); ++row) {
            QString cell = model->data(model->index(row, col)).toString();
            QRect rect = fmCell.boundingRect(0, 0, 2000, 200, Qt::AlignLeft | Qt::TextWordWrap, cell);
            w = qMax(w, rect.width() + 50);
        }

        // FORÇAGE EXTRÊME SELON LA COLONNE
        if (header.contains("email")) {
            w = qMax(w, 620);        // EMAIL ULTRA LARGE (priorité absolue)
        }
        else if (header.contains("motdepasse") || header.contains("hotdepass")) {
            w = qMax(w, 320);
        }
        else if (header.contains("telephone") || header.contains("téléphone")) {
            w = qMax(w, 300);
        }
        else if (header.contains("poste")) {
            w = qMax(w, 280);
        }
        else if (header.contains("nom") || header.contains("prenom")) {
            w = qMax(w, 220);
        }
        else if (header.contains("id")) {
            w = qMax(w, 100);
        }
        else {
            w = qMax(w, 180);
        }

        colWidths[col] = qMin(w, 800);
    }

    // === AJUSTEMENT INTELLIGENT : L'EMAIL PREND LE MAXIMUM POSSIBLE ===
    int totalFixed = 0;
    int emailCol = -1;

    for (int i = 0; i < numCols; ++i) {
        QString h = model->headerData(i, Qt::Horizontal).toString().toLower();
        if (h.contains("email")) {
            emailCol = i;
        } else {
            totalFixed += colWidths[i];
        }
    }

    // On donne tout l'espace restant à la colonne email
    if (emailCol != -1) {
        int availableForEmail = pageWidth - totalFixed - 100; // petite marge de sécurité
        colWidths[emailCol] = qMax(colWidths[emailCol], availableForEmail);
    }

    const int rowHeight = 75;
    int currentPage = 1;

    auto drawTableHeader = [&]() {
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

    // En-tête première page
    drawTableHeader();

    // === LIGNES DE DONNÉES ===
    painter.setFont(cellFont);
    for (int row = 0; row < model->rowCount(); ++row) {
        if (y > pdf.height() - 180) {
            // Numéro de page
            painter.setFont(QFont("Arial", 9, QFont::StyleItalic));
            painter.drawText(pdf.width() - 300, pdf.height() - 40, QString("Page %1").arg(currentPage++));
            pdf.newPage();

            y = margin + 60;
            painter.setFont(QFont("Arial", 24, QFont::Bold));
            painter.drawText(x, y, "Liste des employés (suite)");
            y += 80;
            drawTableHeader();
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

    // Dernière page
    painter.setFont(QFont("Arial", 9, QFont::StyleItalic));
    painter.drawText(pdf.width() - 300, pdf.height() - 40, QString("Page %1").arg(currentPage));

    painter.end();

    QMessageBox::information(this, "Export PDF",
                             "PDF généré avec succès !\n\nLa colonne EMAIL est maintenant ultra-large et parfaitement lisible !");
}
void MainWindow::on_btnRechercher_clicked()
{
    QString texte = ui->lineEditRecherche->text().trimmed();
    QString critere = ui->comboBox_recherche->currentText().trimmed();

    if (texte.isEmpty()) {
        model->setFilter("");
        model->select();
        return;
    }

    // Obtenir le nom exact de la colonne
    QString colonne = getColumnName(critere);
    if (colonne.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Critère inconnu !");
        return;
    }

    // Échapper les apostrophes
    texte.replace("'", "''");

    QString filtre;

    // Si c'est l'ID, filtrer comme nombre
    if (colonne == "id") {
        bool ok;
        int id = texte.toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Erreur", "L'ID doit être un nombre !");
            return;
        }
        filtre = QString("id = %1").arg(id);
    } else {
        // Pour Nom, Prenom, Email → insensible à la casse
        filtre = QString("LOWER(%1) LIKE LOWER('%%2%')").arg(colonne).arg(texte.toLower());
    }

    qDebug() << "Filtre appliqué :" << filtre;

    model->setFilter(filtre);
    if (!model->select()) {
        QMessageBox::warning(this, "Erreur", "Erreur SQL : " + model->lastError().text());
        return;
    }

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Aucun résultat", "Aucun enregistrement ne correspond au critère.");
    }
}
// Slot du bouton Ascendant

void MainWindow::appliquerTri()
{
    model->setFilter("");
    // Récupérer le critère choisi dans le comboBox
    QString critere = ui->comboBox_Tri->currentText().trimmed().toLower();

    // Déterminer le nom de la colonne à trier
    QString colonne;
    if (critere == "id") colonne = "id";
    else if (critere == "poste") colonne = "poste";
    else {
        QMessageBox::warning(this, "Erreur", "Critère de tri inconnu !");
        return;
    }

    // Appliquer le tri sur le modèle existant
    model->setSort(model->fieldIndex(colonne), ordreTri);
    model->select();  // Recharge les données depuis SQLite

    // Optionnel : remplacer les NULL par des chaînes vides dans la vue
    for (int row = 0; row < model->rowCount(); ++row) {
        QModelIndex idx = model->index(row, model->fieldIndex(colonne));
        if (!model->data(idx).isValid() || model->data(idx).toString().isEmpty()) {
            model->setData(idx, "");  // Affiche une cellule vide au lieu de NULL
        }
    }

    // Ajuster les colonnes pour que tout soit lisible
    ui->tableView->resizeColumnsToContents();
}
void MainWindow::on_btnFonctionalite_clicked()
{
    // Récupération des données depuis la BD
    QSqlQuery query("SELECT poste, COUNT(*) FROM employes GROUP BY poste");

    QPieSeries *series = new QPieSeries();
    QString resultat = "📊 Statistiques des employés par poste :\n\n";

    while (query.next()) {
        QString poste = query.value(0).toString();
        int nombre = query.value(1).toInt();

        series->append(poste + " (" + QString::number(nombre) + ")", nombre);
        resultat += poste + " : " + QString::number(nombre) + "\n";
    }

    // Création d’un graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des employés par poste");
    chart->legend()->setAlignment(Qt::AlignRight);

    // Couleurs automatiques + explosion du premier morceau
    if (!series->slices().isEmpty()) {
        series->slices().first()->setExploded(true);
        series->slices().first()->setLabelVisible(true);
    }

    // Création d’une fenêtre personnalisée
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Statistiques");
    dialog->resize(600, 500);  // 🔥 Fenêtre plus grande

    QVBoxLayout *layout = new QVBoxLayout(dialog);

    // Zone texte
    QLabel *label = new QLabel(resultat);
    label->setStyleSheet("font-size: 16px; padding: 10px;");

    // Zone graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    layout->addWidget(label);
    layout->addWidget(chartView);

    dialog->setLayout(layout);
    dialog->exec();  // Affiche la grande fenêtre
}

void MainWindow::on_btnMotDePasseOublie_clicked()
{
    bool ok;
    QString id = QInputDialog::getText(this,
                                       "Mot de passe oublié",
                                       "Veuillez saisir votre ID :",
                                       QLineEdit::Normal,
                                       "", &ok);
    if(!ok || id.isEmpty()) return;

    // Table correcte : employes
    QSqlQuery query;
    query.prepare("SELECT motdepasse FROM employes WHERE id = :id");
    query.bindValue(":id", id);

    if(!query.exec() || !query.next()) {
        QMessageBox::warning(this, "Erreur", "ID introuvable !");
        return;
    }

    QString mdp = query.value("motdepasse").toString();

    // Question secrète codée dans le programme selon l'ID
    QString question, reponseCorrecte;

    if(id == "1") { question = "Couleur préférée ?"; reponseCorrecte = "bleu"; }
    else if(id == "2") { question = "Nom du premier animal ?"; reponseCorrecte = "rex"; }
    else { question = "Code secret ?"; reponseCorrecte = "1234"; }

    // Demander la réponse
    QString reponse = QInputDialog::getText(this, "Question secrète", question, QLineEdit::Normal, "", &ok);
    if(!ok || reponse.isEmpty()) return;

    if(reponse.toLower() == reponseCorrecte.toLower()) {
        QMessageBox::information(this, "Mot de passe", "Votre mot de passe est : " + mdp);
    } else {
        QMessageBox::warning(this, "Erreur", "Réponse incorrecte !");
    }
}
