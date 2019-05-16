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

#include <QPushButton>

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
    explicit MainWindow(QWidget *parent = 0);

    static QGraphicsScene* partida;

    ~MainWindow();

    int sendJSON(string KEY, string data);
    void DibujarTablero();
    void DibujarTorres();
    void graficarGladiador();
    void tirarFlechasG1();
    void tirarFlechasG2();

private slots:
    void on_Inicio_clicked();
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

    //Botones
    QPushButton* botonEstadisticas;
    QPushButton* botonContinuar;

    //Vizualizar Poblaciones
    VisualizarPoblaciones* ViewPobla;

};

#endif // MAINWINDOW_H
