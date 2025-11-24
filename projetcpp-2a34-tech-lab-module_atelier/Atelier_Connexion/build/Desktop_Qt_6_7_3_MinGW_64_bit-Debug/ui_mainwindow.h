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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox_5;
    QLabel *label_38;
    QLabel *label_45;
    QLabel *label_46;
    QLabel *label_47;
    QLabel *label_48;
    QLabel *label_49;
    QLineEdit *lineEdit_ref;
    QLineEdit *LineEdit_nom;
    QLineEdit *LineEdit_j;
    QLineEdit *LineEdit_cap;
    QLineEdit *LineEdit_d;
    QLineEdit *LineEdit_h;
    QLabel *label_50;
    QLineEdit *LineEdit_ns;
    QPushButton *pushButton_modifier;
    QPushButton *pushButton_annuler;
    QPushButton *pushButton_ajouter;
    QTextEdit *textEdit;
    QPushButton *pushButton_10;
    QPushButton *pushButton_rechercher;
    QPushButton *pushButton_15;
    QPushButton *pushButton_supprimer;
    QPushButton *pushButton_trier;
    QPushButton *pushButton_stat;
    QLabel *label_5;
    QLabel *label_stat;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_18;
    QPushButton *pushButton_19;
    QPushButton *pushButton_20;
    QPushButton *pushButton_21;
    QPushButton *pushButton_2;
    QPushButton *pushButton_22;
    QTableWidget *TableWidget;
    QPushButton *pushButton_14;
    QComboBox *comboBox_trier;
    QLineEdit *lineEdit_recherche;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1368, 847);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(230, 100, 321, 541));
        groupBox_5->setMinimumSize(QSize(210, 327));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        groupBox_5->setFont(font);
        groupBox_5->setStyleSheet(QString::fromUtf8("background-color: #15a255;"));
        label_38 = new QLabel(groupBox_5);
        label_38->setObjectName("label_38");
        label_38->setGeometry(QRect(20, 5, 111, 21));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(21, 162, 85, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label_38->setPalette(palette);
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        label_38->setFont(font1);
        label_45 = new QLabel(groupBox_5);
        label_45->setObjectName("label_45");
        label_45->setGeometry(QRect(20, 60, 141, 31));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label_45->setPalette(palette1);
        label_45->setFont(font1);
        label_46 = new QLabel(groupBox_5);
        label_46->setObjectName("label_46");
        label_46->setGeometry(QRect(20, 240, 91, 31));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label_46->setPalette(palette2);
        label_46->setFont(font1);
        label_47 = new QLabel(groupBox_5);
        label_47->setObjectName("label_47");
        label_47->setGeometry(QRect(20, 120, 81, 31));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label_47->setPalette(palette3);
        label_47->setFont(font1);
        label_48 = new QLabel(groupBox_5);
        label_48->setObjectName("label_48");
        label_48->setGeometry(QRect(20, 300, 91, 31));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label_48->setPalette(palette4);
        label_48->setFont(font1);
        label_49 = new QLabel(groupBox_5);
        label_49->setObjectName("label_49");
        label_49->setGeometry(QRect(20, 180, 131, 31));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette5.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label_49->setPalette(palette5);
        label_49->setFont(font1);
        lineEdit_ref = new QLineEdit(groupBox_5);
        lineEdit_ref->setObjectName("lineEdit_ref");
        lineEdit_ref->setGeometry(QRect(20, 30, 281, 31));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush2(QColor(0, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette6.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette6.setBrush(QPalette::Active, QPalette::Base, brush);
        palette6.setBrush(QPalette::Active, QPalette::Window, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette6.setBrush(QPalette::Disabled, QPalette::Window, brush);
        lineEdit_ref->setPalette(palette6);
        QFont font2;
        font2.setPointSize(11);
        lineEdit_ref->setFont(font2);
        lineEdit_ref->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        LineEdit_nom = new QLineEdit(groupBox_5);
        LineEdit_nom->setObjectName("LineEdit_nom");
        LineEdit_nom->setGeometry(QRect(20, 90, 281, 31));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::Button, brush);
        palette7.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette7.setBrush(QPalette::Active, QPalette::Base, brush);
        palette7.setBrush(QPalette::Active, QPalette::Window, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette7.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette7.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette7.setBrush(QPalette::Disabled, QPalette::Window, brush);
        LineEdit_nom->setPalette(palette7);
        LineEdit_nom->setFont(font2);
        LineEdit_nom->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        LineEdit_j = new QLineEdit(groupBox_5);
        LineEdit_j->setObjectName("LineEdit_j");
        LineEdit_j->setGeometry(QRect(20, 210, 281, 31));
        QPalette palette8;
        palette8.setBrush(QPalette::Active, QPalette::Button, brush);
        palette8.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette8.setBrush(QPalette::Active, QPalette::Base, brush);
        palette8.setBrush(QPalette::Active, QPalette::Window, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette8.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette8.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette8.setBrush(QPalette::Disabled, QPalette::Window, brush);
        LineEdit_j->setPalette(palette8);
        LineEdit_j->setFont(font2);
        LineEdit_j->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        LineEdit_cap = new QLineEdit(groupBox_5);
        LineEdit_cap->setObjectName("LineEdit_cap");
        LineEdit_cap->setGeometry(QRect(20, 150, 281, 31));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::Button, brush);
        palette9.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette9.setBrush(QPalette::Active, QPalette::Base, brush);
        palette9.setBrush(QPalette::Active, QPalette::Window, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette9.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette9.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette9.setBrush(QPalette::Disabled, QPalette::Window, brush);
        LineEdit_cap->setPalette(palette9);
        LineEdit_cap->setFont(font2);
        LineEdit_cap->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        LineEdit_d = new QLineEdit(groupBox_5);
        LineEdit_d->setObjectName("LineEdit_d");
        LineEdit_d->setGeometry(QRect(20, 330, 281, 31));
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::Button, brush);
        palette10.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette10.setBrush(QPalette::Active, QPalette::Base, brush);
        palette10.setBrush(QPalette::Active, QPalette::Window, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette10.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette10.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette10.setBrush(QPalette::Disabled, QPalette::Window, brush);
        LineEdit_d->setPalette(palette10);
        LineEdit_d->setFont(font2);
        LineEdit_d->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        LineEdit_h = new QLineEdit(groupBox_5);
        LineEdit_h->setObjectName("LineEdit_h");
        LineEdit_h->setGeometry(QRect(20, 270, 281, 31));
        QPalette palette11;
        palette11.setBrush(QPalette::Active, QPalette::Button, brush);
        palette11.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette11.setBrush(QPalette::Active, QPalette::Base, brush);
        palette11.setBrush(QPalette::Active, QPalette::Window, brush);
        palette11.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette11.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette11.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette11.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette11.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette11.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette11.setBrush(QPalette::Disabled, QPalette::Window, brush);
        LineEdit_h->setPalette(palette11);
        LineEdit_h->setFont(font2);
        LineEdit_h->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_50 = new QLabel(groupBox_5);
        label_50->setObjectName("label_50");
        label_50->setGeometry(QRect(20, 360, 171, 31));
        QPalette palette12;
        palette12.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette12.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette12.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette12.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette12.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette12.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette12.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette12.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette12.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette12.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette12.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label_50->setPalette(palette12);
        label_50->setFont(font1);
        LineEdit_ns = new QLineEdit(groupBox_5);
        LineEdit_ns->setObjectName("LineEdit_ns");
        LineEdit_ns->setGeometry(QRect(20, 390, 281, 31));
        QPalette palette13;
        palette13.setBrush(QPalette::Active, QPalette::Button, brush);
        palette13.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette13.setBrush(QPalette::Active, QPalette::Base, brush);
        palette13.setBrush(QPalette::Active, QPalette::Window, brush);
        palette13.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette13.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette13.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette13.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette13.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette13.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette13.setBrush(QPalette::Disabled, QPalette::Window, brush);
        LineEdit_ns->setPalette(palette13);
        LineEdit_ns->setFont(font2);
        LineEdit_ns->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_modifier = new QPushButton(groupBox_5);
        pushButton_modifier->setObjectName("pushButton_modifier");
        pushButton_modifier->setGeometry(QRect(10, 450, 101, 31));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(true);
        pushButton_modifier->setFont(font3);
        pushButton_modifier->setStyleSheet(QString::fromUtf8("background-color: #E6A537;"));
        pushButton_annuler = new QPushButton(groupBox_5);
        pushButton_annuler->setObjectName("pushButton_annuler");
        pushButton_annuler->setGeometry(QRect(110, 490, 101, 31));
        pushButton_annuler->setFont(font3);
        pushButton_annuler->setStyleSheet(QString::fromUtf8("background-color: #E6A537;"));
        pushButton_ajouter = new QPushButton(groupBox_5);
        pushButton_ajouter->setObjectName("pushButton_ajouter");
        pushButton_ajouter->setGeometry(QRect(210, 450, 101, 31));
        pushButton_ajouter->setFont(font3);
        pushButton_ajouter->setStyleSheet(QString::fromUtf8("background-color: #E6A537;"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(640, 0, 381, 141));
        QPalette palette14;
        palette14.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush3(QColor(222, 254, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette14.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette14.setBrush(QPalette::Active, QPalette::Light, brush);
        palette14.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette14.setBrush(QPalette::Active, QPalette::Dark, brush);
        palette14.setBrush(QPalette::Active, QPalette::Mid, brush2);
        QBrush brush4(QColor(9, 102, 49, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette14.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette14.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette14.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette14.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette14.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette14.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette14.setBrush(QPalette::Active, QPalette::AlternateBase, brush2);
        QBrush brush5(QColor(255, 255, 220, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette14.setBrush(QPalette::Active, QPalette::ToolTipBase, brush5);
        palette14.setBrush(QPalette::Active, QPalette::ToolTipText, brush2);
        QBrush brush6(QColor(255, 255, 255, 127));
        brush6.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette14.setBrush(QPalette::Active, QPalette::PlaceholderText, brush6);
#endif
        palette14.setBrush(QPalette::Active, QPalette::Accent, brush2);
        palette14.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette14.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette14.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette14.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette14.setBrush(QPalette::Inactive, QPalette::Dark, brush);
        palette14.setBrush(QPalette::Inactive, QPalette::Mid, brush2);
        palette14.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette14.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette14.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette14.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette14.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette14.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette14.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush2);
        palette14.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush5);
        palette14.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush2);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette14.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush6);
#endif
        palette14.setBrush(QPalette::Inactive, QPalette::Accent, brush2);
        palette14.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette14.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::Dark, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::Mid, brush2);
        palette14.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette14.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        palette14.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette14.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush2);
        palette14.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush5);
        palette14.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush2);
        QBrush brush7(QColor(0, 0, 0, 127));
        brush7.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette14.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush7);
#endif
        palette14.setBrush(QPalette::Disabled, QPalette::Accent, brush2);
        textEdit->setPalette(palette14);
        pushButton_10 = new QPushButton(centralWidget);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(570, 590, 331, 31));
        pushButton_10->setFont(font3);
        pushButton_10->setStyleSheet(QString::fromUtf8("background-color: #E6A537;"));
        pushButton_rechercher = new QPushButton(centralWidget);
        pushButton_rechercher->setObjectName("pushButton_rechercher");
        pushButton_rechercher->setGeometry(QRect(560, 150, 111, 29));
        pushButton_rechercher->setFont(font3);
        pushButton_rechercher->setStyleSheet(QString::fromUtf8("background-color: #E6A537;"));
        pushButton_15 = new QPushButton(centralWidget);
        pushButton_15->setObjectName("pushButton_15");
        pushButton_15->setGeometry(QRect(390, 60, 161, 31));
        pushButton_15->setFont(font3);
        pushButton_15->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 102, 49);"));
        pushButton_supprimer = new QPushButton(centralWidget);
        pushButton_supprimer->setObjectName("pushButton_supprimer");
        pushButton_supprimer->setGeometry(QRect(940, 590, 361, 31));
        pushButton_supprimer->setFont(font3);
        pushButton_supprimer->setStyleSheet(QString::fromUtf8("background-color: #E6A537;"));
        pushButton_trier = new QPushButton(centralWidget);
        pushButton_trier->setObjectName("pushButton_trier");
        pushButton_trier->setGeometry(QRect(840, 150, 90, 29));
        pushButton_trier->setFont(font3);
        pushButton_trier->setStyleSheet(QString::fromUtf8("background-color: #E6A537;\n"
""));
        pushButton_stat = new QPushButton(centralWidget);
        pushButton_stat->setObjectName("pushButton_stat");
        pushButton_stat->setGeometry(QRect(0, 660, 191, 29));
        pushButton_stat->setStyleSheet(QString::fromUtf8("background-color: #E6A537;"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(1100, 30, 141, 111));
        label_5->setPixmap(QPixmap(QString::fromUtf8("../../Basket club.png")));
        label_5->setScaledContents(true);
        label_stat = new QLabel(centralWidget);
        label_stat->setObjectName("label_stat");
        label_stat->setGeometry(QRect(0, 670, 1201, 161));
        label_stat->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 251, 233);\n"
""));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 50, 221, 591));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_18 = new QPushButton(verticalLayoutWidget);
        pushButton_18->setObjectName("pushButton_18");
        pushButton_18->setMaximumSize(QSize(16777215, 105));
        QFont font4;
        font4.setPointSize(14);
        font4.setBold(true);
        pushButton_18->setFont(font4);
        pushButton_18->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 102, 49);"));

        verticalLayout_2->addWidget(pushButton_18);

        pushButton_19 = new QPushButton(verticalLayoutWidget);
        pushButton_19->setObjectName("pushButton_19");
        pushButton_19->setMaximumSize(QSize(16777215, 105));
        pushButton_19->setFont(font4);
        pushButton_19->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 102, 49);"));

        verticalLayout_2->addWidget(pushButton_19);

        pushButton_20 = new QPushButton(verticalLayoutWidget);
        pushButton_20->setObjectName("pushButton_20");
        pushButton_20->setMaximumSize(QSize(16777215, 105));
        pushButton_20->setFont(font4);
        pushButton_20->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 102, 49);"));

        verticalLayout_2->addWidget(pushButton_20);

        pushButton_21 = new QPushButton(verticalLayoutWidget);
        pushButton_21->setObjectName("pushButton_21");
        pushButton_21->setMaximumSize(QSize(16777215, 105));
        pushButton_21->setFont(font4);
        pushButton_21->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 102, 49);"));

        verticalLayout_2->addWidget(pushButton_21);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMaximumSize(QSize(16777215, 90));
        pushButton_2->setFont(font4);
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 102, 49);"));

        verticalLayout_2->addWidget(pushButton_2);

        pushButton_22 = new QPushButton(verticalLayoutWidget);
        pushButton_22->setObjectName("pushButton_22");
        pushButton_22->setMaximumSize(QSize(16777215, 90));
        pushButton_22->setFont(font4);
        pushButton_22->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 102, 49);"));

        verticalLayout_2->addWidget(pushButton_22);

        TableWidget = new QTableWidget(centralWidget);
        if (TableWidget->columnCount() < 6)
            TableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        TableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        TableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        TableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        TableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        TableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        TableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        TableWidget->setObjectName("TableWidget");
        TableWidget->setGeometry(QRect(560, 200, 751, 391));
        QPalette palette15;
        palette15.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        QBrush brush8(QColor(255, 251, 233, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette15.setBrush(QPalette::Active, QPalette::Button, brush8);
        palette15.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette15.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette15.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette15.setBrush(QPalette::Active, QPalette::Base, brush8);
        palette15.setBrush(QPalette::Active, QPalette::Window, brush8);
        palette15.setBrush(QPalette::Active, QPalette::HighlightedText, brush2);
        palette15.setBrush(QPalette::Active, QPalette::ToolTipText, brush2);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette15.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette15.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette15.setBrush(QPalette::Inactive, QPalette::Button, brush8);
        palette15.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette15.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette15.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette15.setBrush(QPalette::Inactive, QPalette::Base, brush8);
        palette15.setBrush(QPalette::Inactive, QPalette::Window, brush8);
        palette15.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush2);
        palette15.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush2);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette15.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette15.setBrush(QPalette::Disabled, QPalette::Button, brush8);
        palette15.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette15.setBrush(QPalette::Disabled, QPalette::Base, brush8);
        palette15.setBrush(QPalette::Disabled, QPalette::Window, brush8);
        palette15.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush2);
        palette15.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush2);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette15.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush2);
#endif
        TableWidget->setPalette(palette15);
        TableWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 251, 233);"));
        pushButton_14 = new QPushButton(centralWidget);
        pushButton_14->setObjectName("pushButton_14");
        pushButton_14->setGeometry(QRect(230, 60, 151, 31));
        pushButton_14->setFont(font3);
        pushButton_14->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 102, 49);"));
        comboBox_trier = new QComboBox(centralWidget);
        comboBox_trier->addItem(QString());
        comboBox_trier->addItem(QString());
        comboBox_trier->addItem(QString());
        comboBox_trier->addItem(QString());
        comboBox_trier->setObjectName("comboBox_trier");
        comboBox_trier->setGeometry(QRect(940, 150, 141, 28));
        QFont font5;
        font5.setBold(true);
        comboBox_trier->setFont(font5);
        comboBox_trier->setStyleSheet(QString::fromUtf8("background-color: rgb(127, 170, 121);"));
        lineEdit_recherche = new QLineEdit(centralWidget);
        lineEdit_recherche->setObjectName("lineEdit_recherche");
        lineEdit_recherche->setGeometry(QRect(680, 150, 131, 31));
        lineEdit_recherche->setStyleSheet(QString::fromUtf8("background-color: rgb(127, 170, 121);"));
        MainWindow->setCentralWidget(centralWidget);
        label_stat->raise();
        groupBox_5->raise();
        textEdit->raise();
        pushButton_10->raise();
        pushButton_rechercher->raise();
        pushButton_15->raise();
        pushButton_supprimer->raise();
        pushButton_trier->raise();
        pushButton_stat->raise();
        label_5->raise();
        verticalLayoutWidget->raise();
        TableWidget->raise();
        pushButton_14->raise();
        comboBox_trier->raise();
        lineEdit_recherche->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1368, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion des Clients", nullptr));
        groupBox_5->setTitle(QString());
        label_38->setText(QCoreApplication::translate("MainWindow", "r\303\251f\303\251rence", nullptr));
        label_45->setText(QCoreApplication::translate("MainWindow", "nom d\342\200\231atelier", nullptr));
        label_46->setText(QCoreApplication::translate("MainWindow", "horaire", nullptr));
        label_47->setText(QCoreApplication::translate("MainWindow", "capacit\303\251", nullptr));
        label_48->setText(QCoreApplication::translate("MainWindow", "dur\303\251e", nullptr));
        label_49->setText(QCoreApplication::translate("MainWindow", "jour", nullptr));
        label_50->setText(QCoreApplication::translate("MainWindow", "num\303\251ro de salle", nullptr));
        pushButton_modifier->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        pushButton_annuler->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        pushButton_ajouter->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        textEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:28pt; font-weight:700;\">Smart Summer</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:28pt; font-weight:700;\">Club</span></p></body></html>", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Exporter en PDF ", nullptr));
        pushButton_rechercher->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        pushButton_15->setText(QCoreApplication::translate("MainWindow", "Fonctionalit\303\251s", nullptr));
        pushButton_supprimer->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        pushButton_trier->setText(QCoreApplication::translate("MainWindow", "Trier", nullptr));
        pushButton_stat->setText(QCoreApplication::translate("MainWindow", "statistique selon jour ", nullptr));
        label_5->setText(QString());
        label_stat->setText(QString());
        pushButton_18->setText(QCoreApplication::translate("MainWindow", "Employ\303\251", nullptr));
        pushButton_19->setText(QCoreApplication::translate("MainWindow", "Adherents", nullptr));
        pushButton_20->setText(QCoreApplication::translate("MainWindow", "Formateurs", nullptr));
        pushButton_21->setText(QCoreApplication::translate("MainWindow", "Ateliers", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Equipement", nullptr));
        pushButton_22->setText(QCoreApplication::translate("MainWindow", "Se d\303\251connecter", nullptr));
        QTableWidgetItem *___qtablewidgetitem = TableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "r\303\251f\303\251rence", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = TableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "nom d'atelier", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = TableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "capacit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = TableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "jour", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = TableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "horaire", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = TableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "num\303\251ro de salle", nullptr));
        pushButton_14->setText(QCoreApplication::translate("MainWindow", "Accueil", nullptr));
        comboBox_trier->setItemText(0, QCoreApplication::translate("MainWindow", "jour", nullptr));
        comboBox_trier->setItemText(1, QCoreApplication::translate("MainWindow", "horaire", nullptr));
        comboBox_trier->setItemText(2, QCoreApplication::translate("MainWindow", "capacit\303\251", nullptr));
        comboBox_trier->setItemText(3, QCoreApplication::translate("MainWindow", "nom d'atelier", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
