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

#include "tablero.h"

#define PORT 3550
#define MAXDATASIZE 1000

class Thread;
class QTimer;

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
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
    void tirarFlechas();

private slots:
    void on_Inicio_clicked();
    void grafGlad();

private:
    Ui::MainWindow *ui;

    NextGen* nextG;

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

    int lifeG2;
    int lifeG1;

    //variables para graficar un gladiador
    bool t;
    int iGlad;
    int turnoImgGlad1;
    int turnoImgGlad2;

    Thread *bThread;

    QTimer *timer;

    //imagenes
    QPixmap* G1A;
    QPixmap* G1B;
    QPixmap* G2A;
    QPixmap* G2B;
    QPixmap* flechasSencillas;
    QPixmap* flechasFuego;
    QPixmap* flechasExplosivo;

    //Tirar flechas
    int torres[20][3];
    int iTorre;

};

#endif // MAINWINDOW_H
