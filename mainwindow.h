/**
  * @file mainwindow.h
  * @version 1.0
  * @date 15/05/2019
  * @authors Edgar Gonzales, Ruben Salas, Andrey Sanchez, Jose Solano
  * @title Pantalla Principal
  */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <strings.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <json-c/json.h>
#include <json-c/debug.h>
#include <json-c/json_object.h>
#include <QMessageBox>

#include "nextgen.h"
#include "nextgen2.h"
#include "visualizarpoblaciones.h"

#include "tablero.h"

#define PORT 3550
#define MAXDATASIZE 1000

class Thread;
class QTimer;

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow//, public VisualizarPoblaciones
{
    Q_OBJECT

public:

    /**
     * @brief MainWindow Crea la pantalla principal
     * @param parent QWidget en donde se va a colocar
     */
    explicit MainWindow(QWidget *parent = 0);

    static QGraphicsScene* partida;

    ~MainWindow();

    /**
     * @brief sendJSON Solicita diferentes X's y Y's para graficar y datos para setear en labels
     * @param KEY Llave que se va a enviar
     * @param data String con informacion que se va a enviar
     * @return int Para terminar la funcion
     */
    int sendJSON(string KEY, string data);

    /**
     * @brief DibujarTablero Dibuja el laberinto
     */
    void DibujarTablero();

    /**
     * @brief DibujarTorres Dibuja las torres en el laberinto
     */
    void DibujarTorres();

    /**
     * @brief graficarGladiador Dibuja los gladiadores en el laberinto
     */
    void graficarGladiador();

    /**
     * @brief tirarFlechasG1 Dibuja las flechas para el gladiador 1 cuando se ataca
     */
    void tirarFlechasG1();

    /**
     * @brief tirarFlechasG2 Dibuja las flechas para el gladiador 2 cuando se ataca
     */
    void tirarFlechasG2();

private slots:

    /**
     * @brief on_Inicio_clicked Inicia el juego
     */
    void on_Inicio_clicked();

    /**
     * @brief AuxGraficarGladiador Thread de graficacion del gladiador
     */
    void AuxGraficarGladiador();

private:
    Ui::MainWindow *ui;

    NextGen* nextG;

    //QGraphicsView
    QGraphicsView * view;

    int zoneSize;
    int turn;

    int xNodeActual;
    int yNodeActual;
    int xTorreActual;
    int yTorreActual;

    int xActG1;
    int yActG1;
    int xActG2;
    int yActG2;

    string resistenciaTestG1;

    int resistenciaG2;
    int resistenciaG1;
    int hitG1;
    int hitG2;
    int aTypeG1;
    int aTypeG2;
    int xCoordG1;
    int xCoordG2;
    int yCoordG1;
    int yCoordG2;

    //variables para graficar un gladiador
    bool t;
    int iGlad;
    int turnoImgGlad1;
    int turnoImgGlad2;

    Thread *bThread;

    QTimer *timer;

    //Imagenes
    QPixmap* G1A;
    QPixmap* G1B;
    QPixmap* G2A;
    QPixmap* G2B;
    QPixmap* torre;
    QPixmap* cuadroB;
    QPixmap* cuadroN;
    QPixmap* ImgFlecha;
    QPixmap* ImgFlecha2;

    //Tirar flechas
    int iTorre;

    //Widget
    NextGen* GenG1;
    NextGen2* GenG2;

};

#endif // MAINWINDOW_H
