/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_10;
    QPushButton *pushButton_9;
    QPushButton *pushButton_2;
    QPushButton *pushButton_6;
    QPushButton *pushButton_13;
    QPushButton *pushButton_7;
    QGroupBox *groupBox_5;
    QLabel *label_37;
    QLabel *label_39;
    QLabel *label_40;
    QLabel *label_41;
    QLabel *label_42;
    QLabel *label_43;
    QLineEdit *id_6;
    QLineEdit *nom_6;
    QLineEdit *email_6;
    QLineEdit *prenom_6;
    QLineEdit *tel_8;
    QLineEdit *adr_6;
    QLabel *label_44;
    QLineEdit *tel_9;
    QPushButton *pushButton_8;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QPushButton *pushButton_5;
    QPushButton *pushButton_4;
    QPushButton *pushButton_17;
    QComboBox *comboBox_3;
    QPushButton *pushButton_3;
    QPushButton *pushButton_15;
    QTableWidget *tableWidget;
    QPushButton *pushButton_14;
    QComboBox *comboBox_2;
    QPushButton *pushButton_16;
    QTextEdit *textEdit;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1324, 708);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 255, 242);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        pushButton_10 = new QPushButton(centralWidget);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(569, 608, 361, 31));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        pushButton_10->setFont(font);
        pushButton_10->setStyleSheet(QString::fromUtf8("background-color: rgb(203, 42, 2);"));
        pushButton_9 = new QPushButton(centralWidget);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(569, 168, 111, 29));
        pushButton_9->setFont(font);
        pushButton_9->setStyleSheet(QString::fromUtf8("background-color: rgb(203, 42, 2);"));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(10, 19, 219, 78));
        pushButton_2->setMaximumSize(QSize(100000, 105));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        pushButton_2->setFont(font1);
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 102, 49);"));
        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(10, 104, 219, 78));
        pushButton_6->setMaximumSize(QSize(16777215, 105));
        pushButton_6->setFont(font1);
        pushButton_6->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 102, 49);"));
        pushButton_13 = new QPushButton(centralWidget);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(949, 608, 361, 31));
        pushButton_13->setFont(font);
        pushButton_13->setStyleSheet(QString::fromUtf8("background-color: rgb(203, 42, 2);"));
        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(849, 168, 90, 29));
        pushButton_7->setFont(font);
        pushButton_7->setStyleSheet(QString::fromUtf8("background-color: rgb(203, 42, 2);"));
        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName("groupBox_5");
        groupBox_5->setGeometry(QRect(239, 118, 321, 541));
        groupBox_5->setMinimumSize(QSize(210, 327));
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(true);
        groupBox_5->setFont(font2);
        groupBox_5->setStyleSheet(QString::fromUtf8("background-color: #15a255;"));
        label_37 = new QLabel(groupBox_5);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(20, 10, 41, 16));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        QBrush brush1(QColor(21, 162, 85, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        label_37->setPalette(palette);
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(true);
        label_37->setFont(font3);
        label_39 = new QLabel(groupBox_5);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(20, 60, 51, 31));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        label_39->setPalette(palette1);
        label_39->setFont(font3);
        label_40 = new QLabel(groupBox_5);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(20, 240, 91, 31));
        QPalette palette2;
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        label_40->setPalette(palette2);
        label_40->setFont(font3);
        label_41 = new QLabel(groupBox_5);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(20, 120, 81, 31));
        QPalette palette3;
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette3.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette3.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette3.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        label_41->setPalette(palette3);
        label_41->setFont(font3);
        label_42 = new QLabel(groupBox_5);
        label_42->setObjectName("label_42");
        label_42->setGeometry(QRect(20, 300, 91, 31));
        QPalette palette4;
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette4.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette4.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette4.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        label_42->setPalette(palette4);
        label_42->setFont(font3);
        label_43 = new QLabel(groupBox_5);
        label_43->setObjectName("label_43");
        label_43->setGeometry(QRect(20, 180, 131, 31));
        QPalette palette5;
        palette5.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        palette5.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette5.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette5.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette5.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette5.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette5.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette5.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette5.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette5.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette5.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        label_43->setPalette(palette5);
        label_43->setFont(font3);
        id_6 = new QLineEdit(groupBox_5);
        id_6->setObjectName("id_6");
        id_6->setGeometry(QRect(20, 30, 281, 31));
        QPalette palette6;
        palette6.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        QBrush brush2(QColor(0, 0, 0, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette6.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush2);
        palette6.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette6.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette6.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette6.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush2);
        palette6.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette6.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette6.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette6.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette6.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        id_6->setPalette(palette6);
        QFont font4;
        font4.setPointSize(11);
        id_6->setFont(font4);
        id_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        nom_6 = new QLineEdit(groupBox_5);
        nom_6->setObjectName("nom_6");
        nom_6->setGeometry(QRect(20, 90, 281, 31));
        QPalette palette7;
        palette7.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette7.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush2);
        palette7.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette7.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette7.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette7.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush2);
        palette7.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette7.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette7.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette7.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette7.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        nom_6->setPalette(palette7);
        nom_6->setFont(font4);
        nom_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        email_6 = new QLineEdit(groupBox_5);
        email_6->setObjectName("email_6");
        email_6->setGeometry(QRect(20, 210, 281, 31));
        QPalette palette8;
        palette8.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette8.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush2);
        palette8.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette8.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette8.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette8.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush2);
        palette8.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette8.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette8.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette8.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette8.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        email_6->setPalette(palette8);
        email_6->setFont(font4);
        email_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        prenom_6 = new QLineEdit(groupBox_5);
        prenom_6->setObjectName("prenom_6");
        prenom_6->setGeometry(QRect(20, 150, 281, 31));
        QPalette palette9;
        palette9.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette9.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush2);
        palette9.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette9.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette9.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette9.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush2);
        palette9.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette9.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette9.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette9.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette9.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        prenom_6->setPalette(palette9);
        prenom_6->setFont(font4);
        prenom_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tel_8 = new QLineEdit(groupBox_5);
        tel_8->setObjectName("tel_8");
        tel_8->setGeometry(QRect(20, 330, 281, 31));
        QPalette palette10;
        palette10.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette10.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush2);
        palette10.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette10.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette10.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette10.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush2);
        palette10.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette10.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette10.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette10.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette10.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        tel_8->setPalette(palette10);
        tel_8->setFont(font4);
        tel_8->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        adr_6 = new QLineEdit(groupBox_5);
        adr_6->setObjectName("adr_6");
        adr_6->setGeometry(QRect(20, 270, 281, 31));
        QPalette palette11;
        palette11.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette11.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush2);
        palette11.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette11.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette11.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette11.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush2);
        palette11.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette11.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette11.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette11.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette11.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        adr_6->setPalette(palette11);
        adr_6->setFont(font4);
        adr_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_44 = new QLabel(groupBox_5);
        label_44->setObjectName("label_44");
        label_44->setGeometry(QRect(20, 360, 101, 31));
        QPalette palette12;
        palette12.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        palette12.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette12.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette12.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        palette12.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette12.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette12.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette12.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette12.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette12.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette12.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        label_44->setPalette(palette12);
        label_44->setFont(font3);
        tel_9 = new QLineEdit(groupBox_5);
        tel_9->setObjectName("tel_9");
        tel_9->setGeometry(QRect(20, 390, 281, 31));
        QPalette palette13;
        palette13.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette13.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush2);
        palette13.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush);
        palette13.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush);
        palette13.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette13.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush2);
        palette13.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush);
        palette13.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush);
        palette13.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette13.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush);
        palette13.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush);
        tel_9->setPalette(palette13);
        tel_9->setFont(font4);
        tel_9->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_8 = new QPushButton(groupBox_5);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(10, 450, 101, 31));
        pushButton_8->setFont(font);
        pushButton_8->setStyleSheet(QString::fromUtf8("background-color: rgb(203, 42, 2);"));
        pushButton_11 = new QPushButton(groupBox_5);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(110, 490, 101, 31));
        pushButton_11->setFont(font);
        pushButton_11->setStyleSheet(QString::fromUtf8("background-color: rgb(203, 42, 2);"));
        pushButton_12 = new QPushButton(groupBox_5);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(210, 450, 101, 31));
        pushButton_12->setFont(font);
        pushButton_12->setStyleSheet(QString::fromUtf8("background-color: rgb(203, 42, 2);"));
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(10, 189, 219, 78));
        pushButton_5->setMaximumSize(QSize(16777215, 105));
        pushButton_5->setFont(font1);
        pushButton_5->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 102, 49);"));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(10, 274, 219, 79));
        pushButton_4->setMaximumSize(QSize(16777215, 105));
        pushButton_4->setFont(font1);
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 102, 49);"));
        pushButton_17 = new QPushButton(centralWidget);
        pushButton_17->setObjectName("pushButton_17");
        pushButton_17->setGeometry(QRect(10, 530, 219, 78));
        pushButton_17->setMaximumSize(QSize(16777215, 90));
        pushButton_17->setFont(font1);
        pushButton_17->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 102, 49);"));
        comboBox_3 = new QComboBox(centralWidget);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName("comboBox_3");
        comboBox_3->setGeometry(QRect(949, 168, 141, 28));
        QFont font5;
        font5.setBold(true);
        comboBox_3->setFont(font5);
        comboBox_3->setStyleSheet(QString::fromUtf8("background-color: rgb(127, 170, 121);"));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(10, 445, 219, 78));
        pushButton_3->setMaximumSize(QSize(16777215, 90));
        pushButton_3->setFont(font1);
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 102, 49);"));
        pushButton_15 = new QPushButton(centralWidget);
        pushButton_15->setObjectName("pushButton_15");
        pushButton_15->setGeometry(QRect(399, 78, 161, 31));
        pushButton_15->setFont(font);
        pushButton_15->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 102, 49);"));
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 7)
            tableWidget->setColumnCount(7);
        QBrush brush3(QColor(8, 8, 8, 255));
        brush3.setStyle(Qt::BrushStyle::NoBrush);
        QFont font6;
        font6.setPointSize(10);
        font6.setWeight(QFont::Black);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font6);
        __qtablewidgetitem->setForeground(brush3);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font);
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font);
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(569, 208, 741, 391));
        QPalette palette14;
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush2);
        QBrush brush4(QColor(255, 251, 233, 255));
        brush4.setStyle(Qt::BrushStyle::SolidPattern);
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush4);
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush2);
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::BrightText, brush2);
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush2);
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush4);
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush4);
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::HighlightedText, brush2);
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ToolTipText, brush2);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette14.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush2);
#endif
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush2);
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush4);
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush2);
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::BrightText, brush2);
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush2);
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush4);
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush4);
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::HighlightedText, brush2);
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ToolTipText, brush2);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette14.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush2);
#endif
        palette14.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush4);
        palette14.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::BrightText, brush2);
        palette14.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush4);
        palette14.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush4);
        palette14.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::HighlightedText, brush2);
        palette14.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ToolTipText, brush2);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette14.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush2);
#endif
        tableWidget->setPalette(palette14);
        tableWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 251, 233);"));
        pushButton_14 = new QPushButton(centralWidget);
        pushButton_14->setObjectName("pushButton_14");
        pushButton_14->setGeometry(QRect(239, 78, 151, 31));
        pushButton_14->setFont(font);
        pushButton_14->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 102, 49);"));
        comboBox_2 = new QComboBox(centralWidget);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(689, 168, 141, 28));
        QFont font7;
        font7.setPointSize(9);
        font7.setBold(true);
        comboBox_2->setFont(font7);
        comboBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(127, 170, 121);"));
        pushButton_16 = new QPushButton(centralWidget);
        pushButton_16->setObjectName("pushButton_16");
        pushButton_16->setGeometry(QRect(10, 360, 219, 78));
        pushButton_16->setMaximumSize(QSize(16777215, 105));
        pushButton_16->setFont(font1);
        pushButton_16->setStyleSheet(QString::fromUtf8("background-color: rgb(9, 102, 49);"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(670, 11, 381, 141));
        QPalette palette15;
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        QBrush brush5(QColor(240, 255, 242, 255));
        brush5.setStyle(Qt::BrushStyle::SolidPattern);
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush5);
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Light, brush);
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Midlight, brush);
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Dark, brush);
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Mid, brush2);
        QBrush brush6(QColor(9, 102, 49, 255));
        brush6.setStyle(Qt::BrushStyle::SolidPattern);
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush6);
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::BrightText, brush);
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush);
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush5);
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush5);
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Shadow, brush);
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::AlternateBase, brush2);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::BrushStyle::SolidPattern);
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ToolTipBase, brush7);
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ToolTipText, brush2);
        QBrush brush8(QColor(255, 255, 255, 127));
        brush8.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush8);
#endif
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette15.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Accent, brush2);
#endif
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush5);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Light, brush);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Midlight, brush);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Dark, brush);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Mid, brush2);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush6);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::BrightText, brush);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush5);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush5);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Shadow, brush);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::AlternateBase, brush2);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ToolTipBase, brush7);
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ToolTipText, brush2);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush8);
#endif
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette15.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Accent, brush2);
#endif
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush5);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Light, brush);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Midlight, brush);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Dark, brush);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Mid, brush2);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::BrightText, brush);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush5);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush5);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Shadow, brush);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::AlternateBase, brush2);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ToolTipBase, brush7);
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ToolTipText, brush2);
        QBrush brush9(QColor(0, 0, 0, 127));
        brush9.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush9);
#endif
#if QT_VERSION >= QT_VERSION_CHECK(6, 6, 0)
        palette15.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Accent, brush2);
#endif
        textEdit->setPalette(palette15);
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(1140, 30, 160, 131));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1324, 25));
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
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Exporter en PDF ", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Employ\303\251", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Trier", nullptr));
        groupBox_5->setTitle(QString());
        label_37->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        label_39->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        label_40->setText(QCoreApplication::translate("MainWindow", "Sp\303\251cialit\303\251", nullptr));
        label_41->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        label_42->setText(QCoreApplication::translate("MainWindow", "T\303\251lephone", nullptr));
        label_43->setText(QCoreApplication::translate("MainWindow", "Mot de passe", nullptr));
        label_44->setText(QCoreApplication::translate("MainWindow", "Adresse", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "Annuler", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Adherents", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Formateurs", nullptr));
        pushButton_17->setText(QCoreApplication::translate("MainWindow", "Se d\303\251connecter", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("MainWindow", "ID", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("MainWindow", "Nom", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("MainWindow", "Sp\303\251cialit\303\251", nullptr));

        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Equipement", nullptr));
        pushButton_15->setText(QCoreApplication::translate("MainWindow", "Fonctionalit\303\251s", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Nouvelle colonne", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Mot de passe", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Specialit\303\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Adresse", nullptr));
        pushButton_14->setText(QCoreApplication::translate("MainWindow", "Accueil", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "ID", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "Nom", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "Sp\303\251cialit\303\251", nullptr));

        pushButton_16->setText(QCoreApplication::translate("MainWindow", "Ateliers", nullptr));
        textEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:28pt; font-weight:700;\">Smart Summer</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:28pt; font-weight:700;\">Club</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
