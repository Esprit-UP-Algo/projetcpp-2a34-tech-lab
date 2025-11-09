QT += core gui widgets sql
# CONFIG += c++17
CONFIG += c++11 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adherent.cpp \
    atelier.cpp \
    chose.cpp \
    connection.cpp \
    crud.cpp \
    employe.cpp \
    equipement.cpp \
    formateur.cpp \
    main.cpp \
    mainwindow.cpp \
    personne.cpp

HEADERS += \
    adherent.h \
    atelier.h \
    chose.h \
    connection.h \
    crud.h \
    employe.h \
    equipement.h \
    formateur.h \
    mainwindow.h \
    personne.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressource.qrc

RESOURCES +=
