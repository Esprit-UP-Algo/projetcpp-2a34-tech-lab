/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QPushButton *pushButton_11;
    QPushButton *employe_bt;
    QPushButton *commandes_bt;
    QPushButton *produit_bt;
    QPushButton *rdv_bt;
    QPushButton *fournisseur_bt;
    QPushButton *client_bt;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *widget_2;
    QLabel *label_14;
    QLabel *label_15;
    QLineEdit *nom_client;
    QRadioButton *radioButton;
    QLineEdit *telephone_client;
    QPushButton *ajouter_bt;
    QPushButton *modifier_bt;
    QPushButton *annuler_bt;
    QLabel *label_16;
    QRadioButton *radioButton_3;
    QLineEdit *lineEdit_9;
    QTableWidget *tableWidget_cl;
    QFrame *line_3;
    QPushButton *supprimer_bt;
    QFrame *line_2;
    QPushButton *pdf_bt;
    QPushButton *trier_bt;
    QLabel *label_12;
    QLabel *label_13;
    QLineEdit *mail_client;
    QLabel *label_17;
    QLineEdit *adresse_client;
    QLabel *label_8;
    QLabel *label_10;
    QLabel *label_9;
    QLabel *label_11;
    QFrame *line;
    QLineEdit *prenom_client;
    QLineEdit *age_client;
    QLineEdit *points_client;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *id_client;
    QLabel *label_4;
    QWidget *tab_2;
    QLabel *label_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1413, 742);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        widget = new QWidget(centralWidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 361, 791));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);"));
        pushButton_11 = new QPushButton(widget);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(50, 80, 271, 71));
        pushButton_11->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);\n"
"color: rgb(0, 0, 0);"));
        employe_bt = new QPushButton(widget);
        employe_bt->setObjectName("employe_bt");
        employe_bt->setGeometry(QRect(40, 190, 291, 61));
        employe_bt->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);\n"
"color: rgb(0, 0, 0);"));
        commandes_bt = new QPushButton(widget);
        commandes_bt->setObjectName("commandes_bt");
        commandes_bt->setGeometry(QRect(40, 330, 291, 61));
        commandes_bt->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);\n"
"color: rgb(0, 0, 0);"));
        produit_bt = new QPushButton(widget);
        produit_bt->setObjectName("produit_bt");
        produit_bt->setGeometry(QRect(40, 260, 291, 61));
        produit_bt->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);\n"
"color: rgb(0, 0, 0);"));
        rdv_bt = new QPushButton(widget);
        rdv_bt->setObjectName("rdv_bt");
        rdv_bt->setGeometry(QRect(40, 400, 291, 61));
        rdv_bt->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);\n"
"color: rgb(0, 0, 0);"));
        fournisseur_bt = new QPushButton(widget);
        fournisseur_bt->setObjectName("fournisseur_bt");
        fournisseur_bt->setGeometry(QRect(40, 470, 291, 61));
        fournisseur_bt->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);\n"
"color: rgb(0, 0, 0);"));
        client_bt = new QPushButton(widget);
        client_bt->setObjectName("client_bt");
        client_bt->setGeometry(QRect(40, 540, 291, 61));
        client_bt->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);\n"
"background-color: rgb(254, 255, 230);\n"
"color: rgb(0, 0, 0);"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(360, 0, 1371, 591));
        tabWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 253, 240);"));
        tab = new QWidget();
        tab->setObjectName("tab");
        widget_2 = new QWidget(tab);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(-20, 0, 1221, 551));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 253, 240);"));
        label_14 = new QLabel(widget_2);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(60, 320, 101, 41));
        label_14->setStyleSheet(QString::fromUtf8("font: 900 italic 12pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        label_15 = new QLabel(widget_2);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(70, 370, 101, 31));
        label_15->setStyleSheet(QString::fromUtf8("font: 900 italic 12pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        nom_client = new QLineEdit(widget_2);
        nom_client->setObjectName("nom_client");
        nom_client->setGeometry(QRect(190, 190, 151, 31));
        nom_client->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        radioButton = new QRadioButton(widget_2);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(860, 180, 81, 25));
        radioButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        telephone_client = new QLineEdit(widget_2);
        telephone_client->setObjectName("telephone_client");
        telephone_client->setGeometry(QRect(190, 320, 151, 31));
        telephone_client->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        ajouter_bt = new QPushButton(widget_2);
        ajouter_bt->setObjectName("ajouter_bt");
        ajouter_bt->setGeometry(QRect(370, 210, 90, 29));
        ajouter_bt->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);\n"
"color: rgb(0, 0, 0);"));
        modifier_bt = new QPushButton(widget_2);
        modifier_bt->setObjectName("modifier_bt");
        modifier_bt->setGeometry(QRect(370, 270, 90, 29));
        modifier_bt->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);\n"
"color: rgb(0, 0, 0);"));
        annuler_bt = new QPushButton(widget_2);
        annuler_bt->setObjectName("annuler_bt");
        annuler_bt->setGeometry(QRect(370, 340, 90, 29));
        annuler_bt->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);\n"
"color: rgb(0, 0, 0);"));
        label_16 = new QLabel(widget_2);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(760, 140, 81, 41));
        label_16->setStyleSheet(QString::fromUtf8("font: 900 italic 12pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        radioButton_3 = new QRadioButton(widget_2);
        radioButton_3->setObjectName("radioButton_3");
        radioButton_3->setGeometry(QRect(860, 200, 81, 25));
        radioButton_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        lineEdit_9 = new QLineEdit(widget_2);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setGeometry(QRect(490, 200, 221, 31));
        lineEdit_9->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        tableWidget_cl = new QTableWidget(widget_2);
        if (tableWidget_cl->columnCount() < 5)
            tableWidget_cl->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_cl->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_cl->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_cl->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_cl->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_cl->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget_cl->setObjectName("tableWidget_cl");
        tableWidget_cl->setGeometry(QRect(490, 250, 501, 191));
        tableWidget_cl->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 170, 0);"));
        line_3 = new QFrame(widget_2);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(470, 110, 20, 401));
        line_3->setFrameShape(QFrame::Shape::VLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);
        supprimer_bt = new QPushButton(widget_2);
        supprimer_bt->setObjectName("supprimer_bt");
        supprimer_bt->setGeometry(QRect(900, 450, 90, 29));
        supprimer_bt->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);\n"
"color: rgb(0, 0, 0);"));
        line_2 = new QFrame(widget_2);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(50, 520, 1231, 16));
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        pdf_bt = new QPushButton(widget_2);
        pdf_bt->setObjectName("pdf_bt");
        pdf_bt->setGeometry(QRect(790, 450, 90, 29));
        pdf_bt->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);\n"
"color: rgb(0, 0, 0);"));
        trier_bt = new QPushButton(widget_2);
        trier_bt->setObjectName("trier_bt");
        trier_bt->setGeometry(QRect(930, 220, 61, 21));
        trier_bt->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);\n"
"color: rgb(0, 0, 0);"));
        label_12 = new QLabel(widget_2);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(80, 270, 91, 41));
        label_12->setStyleSheet(QString::fromUtf8("font: 900 italic 12pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        label_13 = new QLabel(widget_2);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(70, 220, 111, 41));
        label_13->setStyleSheet(QString::fromUtf8("font: 900 italic 12pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        mail_client = new QLineEdit(widget_2);
        mail_client->setObjectName("mail_client");
        mail_client->setGeometry(QRect(190, 280, 151, 31));
        mail_client->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_17 = new QLabel(widget_2);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(70, 410, 101, 41));
        label_17->setStyleSheet(QString::fromUtf8("font: 900 italic 12pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        adresse_client = new QLineEdit(widget_2);
        adresse_client->setObjectName("adresse_client");
        adresse_client->setGeometry(QRect(190, 410, 151, 31));
        adresse_client->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_8 = new QLabel(widget_2);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(370, 10, 381, 41));
        label_8->setStyleSheet(QString::fromUtf8("font: 900 italic 16pt \"Segoe UI\";\n"
"color: rgb(255, 170, 0);"));
        label_10 = new QLabel(widget_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(490, 110, 281, 41));
        label_10->setStyleSheet(QString::fromUtf8("font: 900 italic 16pt \"Segoe UI\";\n"
"color: rgb(0, 0, 255);"));
        label_9 = new QLabel(widget_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(50, 100, 301, 41));
        label_9->setStyleSheet(QString::fromUtf8("font: 900 italic 16pt \"Segoe UI\";\n"
"color: rgb(0, 0, 255);"));
        label_11 = new QLabel(widget_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(80, 180, 81, 41));
        label_11->setStyleSheet(QString::fromUtf8("font: 900 italic 12pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        line = new QFrame(widget_2);
        line->setObjectName("line");
        line->setGeometry(QRect(30, 80, 1001, 16));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        prenom_client = new QLineEdit(widget_2);
        prenom_client->setObjectName("prenom_client");
        prenom_client->setGeometry(QRect(190, 230, 151, 31));
        age_client = new QLineEdit(widget_2);
        age_client->setObjectName("age_client");
        age_client->setGeometry(QRect(190, 370, 151, 31));
        points_client = new QLineEdit(widget_2);
        points_client->setObjectName("points_client");
        points_client->setGeometry(QRect(190, 450, 151, 31));
        comboBox = new QComboBox(widget_2);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(850, 150, 111, 22));
        comboBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);"));
        comboBox_2 = new QComboBox(widget_2);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(710, 200, 91, 31));
        comboBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);"));
        label = new QLabel(widget_2);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 450, 151, 31));
        label->setStyleSheet(QString::fromUtf8("font: 900 italic 12pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        label_3 = new QLabel(widget_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(70, 150, 81, 16));
        label_3->setStyleSheet(QString::fromUtf8("font: 900 italic 12pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        id_client = new QLineEdit(widget_2);
        id_client->setObjectName("id_client");
        id_client->setGeometry(QRect(192, 151, 151, 31));
        label_4 = new QLabel(widget_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(1090, 40, 49, 41));
        label_4->setPixmap(QPixmap(QString::fromUtf8("../../../../../Downloads/WhatsApp Image 2025-09-15 at 3.55.25 PM.jpeg")));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        label_2 = new QLabel(tab_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 30, 311, 41));
        label_2->setStyleSheet(QString::fromUtf8("font: 900 italic 16pt \"Segoe UI\";\n"
"color: rgb(0, 0, 255);"));
        tabWidget->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1413, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion des Clients", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "Acceuil", nullptr));
        employe_bt->setText(QCoreApplication::translate("MainWindow", "Employ\303\251", nullptr));
        commandes_bt->setText(QCoreApplication::translate("MainWindow", "Commandes", nullptr));
        produit_bt->setText(QCoreApplication::translate("MainWindow", "Produit", nullptr));
        rdv_bt->setText(QCoreApplication::translate("MainWindow", "RDV", nullptr));
        fournisseur_bt->setText(QCoreApplication::translate("MainWindow", "Fournisseur", nullptr));
        client_bt->setText(QCoreApplication::translate("MainWindow", "Client", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\250phone :", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Age :", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "croissant", nullptr));
        ajouter_bt->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        modifier_bt->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        annuler_bt->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Trier par :", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MainWindow", "d\303\251croissant", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_cl->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_cl->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_cl->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_cl->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Age", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_cl->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Points de fid\303\251lit\303\251", nullptr));
        supprimer_bt->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        pdf_bt->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        trier_bt->setText(QCoreApplication::translate("MainWindow", "trier", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Mail :", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom :", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Adresse :", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Gestion des clients ", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Tableau clients :", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Formulaire client :", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Nom :", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "nom", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Age", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "points de fid\303\251lit\303\251", nullptr));

        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "ID", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "mail", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "points de fid\303\251lit\303\251", nullptr));
        comboBox_2->setItemText(3, QString());

        label->setText(QCoreApplication::translate("MainWindow", "Points de fid\303\251lit\303\251 :", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "ID Client :", nullptr));
        label_4->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Zone Export et statstiques :", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
