#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QGraphicsItem>
#include <stdio.h>
#include <iostream>

using namespace std;

QGraphicsScene* MainWindow::partida = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    partida = new QGraphicsScene(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Inicio_clicked()
{

    //Crea el laberinto

    QGraphicsTextItem *datos = new QGraphicsTextItem;
    datos->setScale(3);
    datos->setPos(350,30);
    datos->setPlainText("Bienvenido A La Gran Batalla");

    //crear View
    QGraphicsView * view = new QGraphicsView(partida);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();
    view->setFixedSize(1200,600);
    partida->setSceneRect(0,0,1200,600);
    partida->backgroundBrush();

    Tablero* tablero = new Tablero();
    tablero->generar(7);
    tablero->imprimir();

    printf("\n");

    //Agrega todos los elementos a la partida

    partida->addPixmap(QPixmap(":/imagenes/fondo.jpg"));
    partida->addItem(datos);

    //para mostrar los cuadros de la matriz en partida
    int num = tablero->getnumMatriz();

    //Cuadro Blanco
    QPixmap *cuadroB = new QPixmap(":/imagenes/cuadro-blanco.png");
    cuadroB->setDevicePixelRatio(5);

    //Cuadro Negro
    QPixmap *cuadroN = new QPixmap(":/imagenes/cuadro-negro.png");
    cuadroN->setDevicePixelRatio(5);

    //Pixeles X y Y
    int pixX = 350;
    int pixY = 100;

    int xInicial=pixX;
    int yInicial=pixY;

    int cuadro=0;
    int suma=45;

    //si ingresa un tablero de indice par
    if (num%2==0){

        for (int i=0;i<num;i++){

            for (int j=0;j<num;j++){

                if (cuadro==0){
                    partida->addPixmap(*cuadroN)->moveBy(pixX,pixY);
                    cuadro++;
                }
                else{
                    partida->addPixmap(*cuadroB)->moveBy(pixX,pixY);
                    cuadro=0;
                }
                pixX=pixX+suma;
            }

            if(num%2==0 and cuadro==0){
                cuadro=1;
            }
            else{
                cuadro=0;
            }

            pixX=xInicial;
            pixY=pixY+suma;
        }
    }

    //si ingresa un indice impar
    else{
        for (int i=0;i<num;i++){

            for (int j=0;j<num;j++){

                if (cuadro==0){
                    partida->addPixmap(*cuadroN)->moveBy(pixX,pixY);
                    cuadro++;
                }
                else{
                    partida->addPixmap(*cuadroB)->moveBy(pixX,pixY);
                    cuadro=0;
                }
                pixX=pixX+suma;
            }
            pixX=xInicial;
            pixY=pixY+suma;
        }
    }

    SLOT(close());
}
