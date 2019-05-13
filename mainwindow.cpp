#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QGraphicsItem>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <QDateTime>
#include <QTimer>
#include <QMatrix>

#include "thread.h"

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
    ///Turno actual -> iteracion
    turn = 1;

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

    //Agrega todos los elementos a la partida
    partida->addPixmap(QPixmap(":/imagenes/fondo.jpg"));
    partida->addItem(titulo);

    //DibujarTablero();
    //DibujarTorres();

    //Rellena el array de las torres
    for(int j=0; j<20; j++){
        for (int i=0;i<3;i++){
            torres[j][i]=0;
        }
    }

    //Para Graficar los gladiadores
    graficarGladiador();



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

        if (i<20){
            torres[i][0]=i;
            torres[i][1]=xTorreActual;
            torres[i][2]=yTorreActual;
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


void MainWindow::tirarFlechas(){

    flechasSencillas = new QPixmap(":/imagenes/flecha sencilla.png");
    flechasSencillas->setDevicePixelRatio(0.5*zoneSize);
    flechasFuego = new QPixmap(":/imagenes/flecha fuego-1.png");
    flechasFuego->setDevicePixelRatio(0.5*zoneSize);
    flechasExplosivo = new QPixmap(":/imagenes/flecha explosiva.png");
    flechasExplosivo->setDevicePixelRatio(0.5*zoneSize);

    for(int j=0;j<20;j++){

        //Gladiador 1
        //Verifica si esta a la derecha
        if (torres[j][1] == (xActG1+(450/zoneSize)) && torres[j][2] == yActG1 ){
            QMatrix rot;
            rot.rotate(180);
            flechasSencillas->transformed(rot);
            partida->addPixmap(*flechasSencillas)->moveBy(xActG1,yActG1);
        }

        //Verifica si esta a la izquierda
        if (torres[j][1] == (xActG1-(450/zoneSize)) && torres[j][2] == yActG1 ){
            partida->addPixmap(*flechasFuego)->moveBy(xActG1,yActG1);
        }

        //Verifica si esta a Arriba
        if (torres[j][1] == xActG1 && torres[j][2] == (yActG1-(450/zoneSize))){
            QMatrix rot;
            rot.rotate(270);
            flechasSencillas->transformed(rot);
            partida->addPixmap(*flechasSencillas)->moveBy(xActG1,yActG1);
        }

        //Verifica si esta a Abajo
        if (torres[j][1] == xActG1 && torres[j][2] == (yActG1+(450/zoneSize))){
            QMatrix rot;
            rot.rotate(90);
            flechasExplosivo->transformed(rot);
            partida->addPixmap(*flechasExplosivo)->moveBy(xActG1,yActG1);
        }


        //Gladiador 2
        //Verifica si esta a la derecha
        if (torres[j][1] == (xActG2+(450/zoneSize)) && torres[j][2] == yActG2 ){
            QMatrix rot;
            rot.rotate(180);
            flechasSencillas->transformed(rot);
            partida->addPixmap(*flechasSencillas)->moveBy(xActG2,yActG2);
        }

        //Verifica si esta a la izquierda
        if (torres[j][1] == (xActG2-(450/zoneSize)) && torres[j][2] == yActG2 ){
            partida->addPixmap(*flechasFuego)->moveBy(xActG2,yActG2);
        }

        //Verifica si esta a Arriba
        if (torres[j][1] == xActG2 && torres[j][2] == (yActG2-(450/zoneSize))){
            QMatrix rot;
            rot.rotate(270);
            flechasSencillas->transformed(rot);
            partida->addPixmap(*flechasSencillas)->moveBy(xActG2,yActG2);
        }

        //Verifica si esta a Abajo
        if (torres[j][1] == xActG2 && torres[j][2] == (yActG2+(450/zoneSize))){
            QMatrix rot;
            rot.rotate(90);
            flechasExplosivo->transformed(rot);
            partida->addPixmap(*flechasExplosivo)->moveBy(xActG2,yActG2);
        }
    }


}


void MainWindow::graficarGladiador() {

    //Imagenes del gladiador 1
    G1A = new QPixmap(":/imagenes/G1A.png");
    G1A->setDevicePixelRatio(0.5*zoneSize);
    G1B = new QPixmap(":/imagenes/G1B.png");
    G1B->setDevicePixelRatio(0.5*zoneSize);

    //Imagenes del gladiador 2
    G2A = new QPixmap(":/imagenes/G2A.png");
    G2A->setDevicePixelRatio(0.5*zoneSize);
    G2B = new QPixmap(":/imagenes/G2B.png");
    G2B->setDevicePixelRatio(0.5*zoneSize);

    bool move = true;

    ///Cuando hay que cambiar las torres de posicion
    if (turn % 3 == 0) {


    } else {


        //Para graficar los gladiadores
        t = false;
        iGlad = 0;
        turnoImgGlad1=0;
        turnoImgGlad2=0;

        //Para Graficar los gladiadores
        timer = new QTimer(this);

        //while(t==false){
            connect(timer,SIGNAL(timeout()), this, SLOT(grafGlad()));
            timer->start(2000);
        //}
    }

}

void MainWindow::grafGlad(){

    DibujarTablero();
    DibujarTorres();

    QString I;
    I.setNum(iGlad);

    //Gladiador 1
    sendJSON("XCOORDGP1", I.toStdString());
    sendJSON("YCOORDGP1", I.toStdString());

    //Gladiador 2
    sendJSON("XCOORDGP2", I.toStdString());
    sendJSON("YCOORDGP2", I.toStdString());

    tirarFlechas();

    //Hay que quitar este if porque lo estoy obligando
    /*if (iGlad==0){
        xActG2=xActG1;
        yActG2=yActG1;
    }*/

    if (xActG1==-1 && yActG1==-1 && xActG2==-1 && yActG2==-1){
        t=true;
        cout<<"Final del thread"<<endl;
        timer->stop();
    }

    if (xActG1!=-1 && yActG1!=-1){

        if (turnoImgGlad1 == 0){
            partida->addPixmap(*G1A)->moveBy(xActG1,yActG1);
            turnoImgGlad1=1;
        }
        else{
            partida->addPixmap(*G1B)->moveBy(xActG1,yActG1);
            turnoImgGlad1=0;
        }

        cout<<xActG1<<","<<yActG1<<endl;
        cout<<(iGlad)<<endl;

    }

    if (xActG2!=-1 && yActG2!=-1){

        if (turnoImgGlad2 == 0){
            partida->addPixmap(*G2A)->moveBy(xActG2,yActG2);
            turnoImgGlad2=1;
        }
        else{
            partida->addPixmap(*G2B)->moveBy(xActG2,yActG2);
            turnoImgGlad2=0;
        }
        cout<<xActG2<<","<<yActG2<<endl;
        cout<<(iGlad)<<endl;

    }

    iGlad++;

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
        client.sin_addr.s_addr = inet_addr("10.0.2.15"); //192.168.100.6
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

    //Gladiador 1
    struct json_object *xG1;
    json_object *parsed_jsonxG1 = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonxG1, "XCOORDGP1", &xG1);
    if (json_object_get_int(xG1) != 0){
        xActG1 = json_object_get_int(xG1);
    }

    struct json_object *yG1;
    json_object *parsed_jsonyG1 = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonyG1, "YCOORDGP1", &yG1);
    if (json_object_get_int(yG1) != 0){
        yActG1 = json_object_get_int(yG1);
    }

    //Gladiador 2
    struct json_object *xG2;
    json_object *parsed_jsonxG2 = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonxG2, "XCOORDGP2", &xG2);
    if (json_object_get_int(xG2) != 0){
        xActG2 = json_object_get_int(xG2);
    }

    struct json_object *yG2;
    json_object *parsed_jsonyG2 = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonyG2, "YCOORDGP2", &yG2);
    if (json_object_get_int(yG2) != 0){
        yActG2 = json_object_get_int(yG2);
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
