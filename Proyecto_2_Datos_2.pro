#-------------------------------------------------
#
# Project created by QtCreator 2019-04-27T00:56:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Proyecto_2_Datos_2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tablero.cpp \
    node.cpp \
    torres.cpp \
    nextgen.cpp

HEADERS  += mainwindow.h \
    tablero.h \
    node.h \
    torres.h \
    nextgen.h

FORMS    += mainwindow.ui \
    nextgen.ui

RESOURCES += \
    imagenes.qrc


