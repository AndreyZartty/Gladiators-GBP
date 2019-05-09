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

    nextG = new NextGen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Inicio_clicked()
{

    sendJSON("COMENZAR", "Comenzar");

    hide();

    //Imagenes
    QPixmap* flechaSencilla = new QPixmap(":/imagenes/flecha sencilla.png");
    flechaSencilla->setDevicePixelRatio(0.5*zoneSize);
    QPixmap* flechaFuego = new QPixmap(":/imagenes/flecha fuego-1.png");
    flechaFuego->setDevicePixelRatio(0.5*zoneSize);
    QPixmap* flechaExplosivo = new QPixmap(":/imagenes/flecha explosiva.png");
    flechaExplosivo->setDevicePixelRatio(0.5*zoneSize);

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
    tablero->generar(zoneSize);
    tablero->imprimir();
    printf("\n");

    //Agrega todos los elementos a la partida
    partida->addPixmap(QPixmap(":/imagenes/fondo.jpg"));
    partida->addItem(titulo);

    DibujarTablero();
    DibujarTorres();

    SLOT(close());
}


void MainWindow::DibujarTorres(){

    //Imagenes
    QPixmap* torre = new QPixmap(":/imagenes/torre2.png");
    torre->setDevicePixelRatio(0.5*zoneSize);

    //Para generar torres aleatorias
    bool t = false;
    int i = 0;

    while(t==false){

        QString I;
        I.setNum(i);

        sendJSON("XCOORDTORRE", I.toStdString());
        sendJSON("YCOORDTORRE", I.toStdString());

        if (yTorreActual==-1 || xTorreActual==-1){
            t=true;
            break;
        }

        partida->addPixmap(*torre)->moveBy(xTorreActual,yTorreActual);

        i++;
    }

}


void MainWindow::DibujarTablero(){

    //Imagenes
    QPixmap* cuadroB = new QPixmap(":/imagenes/cuadro-blanco (copy).png");
    cuadroB->setDevicePixelRatio(0.5*zoneSize);
    QPixmap* cuadroN = new QPixmap(":/imagenes/cuadro-negro (copy).png");
    cuadroN->setDevicePixelRatio(0.5*zoneSize);

    //para mostrar los cuadros de la matriz en partida
    int num = zoneSize;

    int cuadro=0;
    int suma=(450/zoneSize);

    //si ingresa un tablero de indice par
    if (num%2==0){

        for (int i=0;i<num;i++){

            for (int j=0;j<num;j++){

                int id = i * zoneSize + j;
                QString iD;
                iD.setNum(id);

                //Modifica los x y y de cada node del tablero
                sendJSON("XCOORD",iD.toStdString());
                sendJSON("YCOORD",iD.toStdString());

                if (cuadro==0){
                    partida->addPixmap(*cuadroN)->moveBy(xNodeActual,yNodeActual);
                    cuadro++;
                }
                else{
                    partida->addPixmap(*cuadroB)->moveBy(xNodeActual,yNodeActual);
                    cuadro=0;
                }
            }

            if(num%2==0 and cuadro==0){
                cuadro=1;
            }
            else{
                cuadro=0;
            }
        }
    }

    //si ingresa un indice impar
    else{
        for (int i=0;i<num;i++){

            for (int j=0;j<num;j++){

                int id = i * zoneSize + j;
                QString iD;
                iD.setNum(id);

                //Modifica los x y y de cada node del tablero
                sendJSON("XCOORD",iD.toStdString());
                sendJSON("YCOORD",iD.toStdString());

                if (cuadro==0){
                    partida->addPixmap(*cuadroN)->moveBy(xNodeActual,yNodeActual);
                    cuadro++;
                }
                else{
                    partida->addPixmap(*cuadroB)->moveBy(xNodeActual,yNodeActual);
                    cuadro=0;
                }
            }
        }
    }
}


int MainWindow::sendJSON(string KEY, string data){
    char* str;
    int fd, numbytes;
    struct sockaddr_in client;

    fd = socket(AF_INET, SOCK_STREAM, 0);

    char sendBuff[MAXDATASIZE];
    char recvBuff[MAXDATASIZE];

    struct hostent *he;

    if (fd < 0)
    {
        printf("Error : Could not create socket\n");
        return 1;
    }
    else
    {
        client.sin_family = AF_INET;
        client.sin_port = htons(PORT);
        client.sin_addr.s_addr = inet_addr("172.20.10.5"); //172.20.10.4
        memset(client.sin_zero, '\0', sizeof(client.sin_zero));
    }

    if (::connect(fd, (const struct sockaddr *)&client, sizeof(client)) < 0)
    {
        printf("ERROR connecting to server\n");
        return 1;
    }


    json_object *jobj = json_object_new_object();

    json_object *jstring = json_object_new_string(data.c_str());

    json_object_object_add(jobj,KEY.c_str(), jstring);


    if (strcpy(sendBuff, json_object_to_json_string(jobj)) == NULL) {
        printf("ERROR strcpy()");
        exit(-1);
    }

    if (write(fd, sendBuff, strlen(sendBuff)) == -1)
    {
        printf("ERROR write()");
        exit(-1);
    }

    if ((numbytes=recv(fd,recvBuff,MAXDATASIZE,0)) < 0){

        printf("Error en recv() \n");
        exit(-1);
    }

    struct json_object *tempZoneSize;
    json_object *parsed_jsonZoneSize = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonZoneSize, "ZONESIZE", &tempZoneSize);
    if (json_object_get_int(tempZoneSize) != 0){
        zoneSize = json_object_get_int(tempZoneSize);
    }

    struct json_object *xActual;
    json_object *parsed_jsonxActual = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonxActual, "XCOORD", &xActual);
    if (json_object_get_int(xActual) != 0 ){
        xNodeActual = json_object_get_int(xActual);
    }

    struct json_object *yActual;
    json_object *parsed_jsonyActual = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonyActual, "YCOORD", &yActual);
    if (json_object_get_int(yActual) != 0){
        yNodeActual = json_object_get_int(yActual);
    }

    struct json_object *xTorre;
    json_object *parsed_jsonxTorre = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonxTorre, "XCOORDTORRE", &xTorre);
    if (json_object_get_int(xTorre) != 0 ){
        xTorreActual = json_object_get_int(xTorre);
    }

    struct json_object *yTorre;
    json_object *parsed_jsonyTorre = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonyTorre, "YCOORDTORRE", &yTorre);
    if (json_object_get_int(yTorre) != 0){
        yTorreActual = json_object_get_int(yTorre);
    }


    /*if (json_object_get_string(tempCodigo) != 0 && json_object_get_string(tempErrorCodigo) == 0) {

    } else {
        cout << json_object_get_string(tempErrorCodigo) << endl;
        QMessageBox::information(this, tr("Error"), tr("Máxima cantidad de juegos activos alcanzada, intente ingresar luego."));
        close();
        return 0;

    }*/

    ///Se limpian los Buffers
    memset(recvBuff, 0, MAXDATASIZE);
    memset(sendBuff, 0, MAXDATASIZE);

    ::close(fd);
}
