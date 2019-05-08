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

    QGraphicsTextItem *titulo = new QGraphicsTextItem;
    titulo->setScale(3);
    titulo->setPos(300,10);
    titulo->setPlainText("Bienvenido A La Gran Batalla");

    //crear View
    QGraphicsView * view = new QGraphicsView(partida);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();
    view->setFixedSize(1200,600);
    partida->setSceneRect(0,0,1200,600);
    partida->backgroundBrush();

    //Pixeles X y Y
    int pixX = 380;
    int pixY = 100;

    int xInicial=pixX;
    int yInicial=pixY;

    //Crea un tablero
    Tablero* tablero = new Tablero();
    tablero->generar(10);
    tablero->imprimir();
    printf("\n");

    //Agrega todos los elementos a la partida
    partida->addPixmap(QPixmap(":/imagenes/fondo.jpg"));
    partida->addItem(titulo);

    //para mostrar los cuadros de la matriz en partida
    int num = tablero->getnumMatriz();

    //Cuadro Blanco
    QPixmap *cuadroB = new QPixmap(":/imagenes/cuadro-blanco.png");
    cuadroB->setDevicePixelRatio(5);

    //Cuadro Negro
    QPixmap *cuadroN = new QPixmap(":/imagenes/cuadro-negro.png");
    cuadroN->setDevicePixelRatio(5);

    int cuadro=0;
    int suma=45;

    //si ingresa un tablero de indice par
    if (num%2==0){

        for (int i=0;i<num;i++){

            for (int j=0;j<num;j++){

                //Modifica los x y y de cada node del tablero
                tablero->getNode(i,j)->setX(pixX);
                tablero->getNode(i,j)->setY(pixY);

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

                //Modifica los x y y de cada node del tablero
                tablero->getNode(i,j)->setX(pixX);
                tablero->getNode(i,j)->setY(pixY);

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

    //Para generar torres aleatorias
    for (int t=0; t<20; t++){
        int f = rand()%num;
        int c = rand()%num;

        if (f==0 & c==0){
            t=t-1;
        }

        else if (f==num & c==num){
            t=t-1;
        }

        else if (tablero->getNode(f,c)->getTorre()->getEstado() == false) {

            tablero->getNode(f,c)->getTorre()->setEstado(true);

            QPixmap *torre = tablero->getNode(f,c)->getTorre()->getTorre();

            int x = tablero->getNode(f,c)->getX();
            int y = tablero->getNode(f,c)->getY();

            partida->addPixmap(*torre)->moveBy(x,y);

        }
        else{
            t=t-1;
        }
    }

    SLOT(close());
}