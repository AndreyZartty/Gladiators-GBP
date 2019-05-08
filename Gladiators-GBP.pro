QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gladiators-GBP
TEMPLATE = app
CONFIG += console


SOURCES += \
        gladiador.cpp \
        list.cpp \
        main.cpp \
        mainwindow.cpp \
        node.cpp \
        nodo.cpp \
        poblacion.cpp \
        tablero.cpp \
        torres.cpp

HEADERS += \
    gladiador.h \
    list.h \
    mainwindow.h \
    node.h \
    nodo.h \
    poblacion.h \
    tablero.h \
    torres.h

RESOURCES += \
    imagenes.qrc

FORMS += \
    mainwindow.ui
