QT += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport
CONFIG += c++11
QT += charts
QT += charts widgets


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    employe.cpp \
    connection.cpp \
    arduino.cpp

HEADERS += \
    mainwindow.h \
    employe.h \
    connection.h \
    arduino.h

FORMS += \
    mainwindow.ui
