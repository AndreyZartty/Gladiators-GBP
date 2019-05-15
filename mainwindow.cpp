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
#include <QTransform>
#include <QWidget>
#include <QColor>
#include <string>

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

    //crear View
    view = new QGraphicsView(partida);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(1200,600);
    partida->setSceneRect(0,0,1200,600);
    partida->backgroundBrush();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete G1A;
    delete G1B;
    delete G2A;
    delete G2B;
    delete torre;
    delete cuadroB;
    delete cuadroN;
    delete ImgFlecha;
    delete ImgFlecha2;
    delete GenG2;
    delete GenG1;
}

void MainWindow::on_Inicio_clicked()
{
    ///Turno actual -> iteracion
    turn = 1;

    sendJSON("COMENZAR", "Comenzar");


    hide();

    //Titulo
    QGraphicsTextItem *auxtitulo = new QGraphicsTextItem;
    auxtitulo->setScale(5);
    auxtitulo->setPos(302,10);
    auxtitulo->setPlainText("Gladiators - GBP");
    QColor* BG2 = new QColor(255,255,255);
    auxtitulo->setDefaultTextColor(*BG2);

    //Muestra el view
    view->show();

    QGraphicsTextItem *titulo = new QGraphicsTextItem;
    titulo->setScale(5);
    titulo->setPos(300,10);
    titulo->setPlainText("Gladiators - GBP");
    QColor* BG = new QColor(192,119,21);
    titulo->setDefaultTextColor(*BG);

    //Widget Gladiador 2
    GenG1 = new NextGen();
    GenG1->move(0,150);

    //Widget Gladiador
    GenG2 = new NextGen2();
    GenG2->move(830,150);

    //Pixeles X y Y
    int pixX = 380;
    int pixY = 100;

    int xInicial=pixX;
    int yInicial=pixY;

    //Agrega todos los elementos a la partida
    partida->addPixmap(QPixmap(":/imagenes/fondoo.jpg"));
    partida->addItem(auxtitulo);
    partida->addItem(titulo);
    partida->addWidget(GenG1);
    partida->addWidget(GenG2);

    DibujarTablero();
    DibujarTorres();

    //Para Graficar los gladiadores
    graficarGladiador();



    SLOT(close());
}


/*void VisualizarPoblaciones::on_botonMostrar_clicked(){

}*/


void MainWindow::DibujarTorres(){

    //Imagenes
    torre = new QPixmap(":/imagenes/torre2.png");
    torre->setDevicePixelRatio(0.5*zoneSize);

    //Para generar torres aleatorias
    bool t = false;
    int i = 0;

    while(t==false){

        QString I;
        I.setNum(i);

        sendJSON("XCOORDTORRE", I.toStdString());
        sendJSON("YCOORDTORRE", I.toStdString());

        cout<<yTorreActual<<","<<xTorreActual<<endl;

        if (yTorreActual==-1 && xTorreActual==-1){
            t=true;
            break;
        }

        else{

            partida->addPixmap(*torre)->moveBy(xTorreActual,yTorreActual);



        }
        i++;
    }

}


void MainWindow::DibujarTablero(){

    //Imagenes
    cuadroB = new QPixmap(":/imagenes/cuadro-blanco (copy).png");
    cuadroB->setDevicePixelRatio(0.5*zoneSize);
    cuadroN = new QPixmap(":/imagenes/cuadro-negro (copy).png");
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


void MainWindow::tirarFlechasG1(){

    for(int j=1;j<25;j++){

        QString I;
        I.setNum(j);

        sendJSON("HITG1", I.toStdString());


        if (hitG1==1){

            sendJSON("ATYPEG1", I.toStdString());

            //cout<<aTypeG1<<endl;

            if (aTypeG1==-1){
                j=26;
                break;
            }

            else {

                //int direccionG1=aTypeG1%10;
                int flechaG1=(aTypeG1)/10;


                if (flechaG1==1){
                    ImgFlecha = new QPixmap(":/imagenes/flecha sencilla.png");
                    ImgFlecha->setDevicePixelRatio(0.5*zoneSize);
                }

                else if (flechaG1==2){
                    ImgFlecha = new QPixmap(":/imagenes/flecha fuego-1.png");
                    ImgFlecha->setDevicePixelRatio(0.5*zoneSize);
                }

                else if (flechaG1==3){
                    ImgFlecha = new QPixmap(":/imagenes/flecha explosiva.png");
                    ImgFlecha->setDevicePixelRatio(0.5*zoneSize);
                }

                /*if (direccionG1 == 0){
                    //ArribaIzq
                    QMatrix rm;
                    rm.rotate(135);
                    ImgFlecha = ImgFlecha->transformed(rm);
                }

                else if (direccionG1 == 1){
                    //Arriba
                    QMatrix rm;
                    rm.rotate(90);
                    ImgFlecha = ImgFlecha->transformed(rm);
                }

                else if (direccionG1 == 2){
                    //ArribaDer
                    QMatrix rm;
                    rm.rotate(45);
                    ImgFlecha = ImgFlecha->transformed(rm);
                }

                else if (direccionG1 == 3){
                    //Izquierda
                    QMatrix rm;
                    rm.rotate(180);
                    ImgFlecha = ImgFlecha->transformed(rm);
                }

                else if (direccionG1 == 4){
                    //Derecha
                    //viene por default
                }

                else if (direccionG1 == 5){
                    //AbajoIzq
                    QMatrix rm;
                    rm.rotate(225);
                    ImgFlecha = ImgFlecha->transformed(rm);
                }

                else if (direccionG1 == 6){
                    //Abajo
                    QMatrix rm;
                    rm.rotate(270);
                    ImgFlecha = ImgFlecha->transformed(rm);
                }

                else if (direccionG1 == 7){
                    //AbajoIDer
                    QMatrix rm;
                    rm.rotate(315);
                    ImgFlecha = ImgFlecha->transformed(rm);
                }*/

                partida->addPixmap(*ImgFlecha)->moveBy(xActG1,yActG1);
            }

        }

        if (hitG1==0){
            j=26;
            //break;
        }

        else {

            if (aTypeG1==-1){
                j=26;
                //break;
            }
        }
    }
}


void MainWindow::tirarFlechasG2(){

    for(int j=1;j<25;j++){

        //cout<<"j: "<<j<<endl;

        QString I;
        I.setNum(j);

        sendJSON("HITG2", I.toStdString());

        cout<<"HIT2: " << hitG2<<endl;

        if (hitG2==1){

            sendJSON("ATYPEG2", I.toStdString());

            cout<<"AT2: " << aTypeG2<<endl;

            if (aTypeG2==-1){
                j=26;
                //break;
            }

            else {

                //int direccionG2=aTypeG2%10;
                int flechaG2=(aTypeG2)/10;

                if (flechaG2==1){
                    ImgFlecha2 = new QPixmap(":/imagenes/flecha sencilla.png");
                    ImgFlecha2->setDevicePixelRatio(0.5*zoneSize);
                }

                else if (flechaG2==2){
                    ImgFlecha2 = new QPixmap(":/imagenes/flecha fuego-1.png");
                    ImgFlecha2->setDevicePixelRatio(0.5*zoneSize);
                }

                else if (flechaG2==3){
                    ImgFlecha2 = new QPixmap(":/imagenes/flecha explosiva.png");
                    ImgFlecha2->setDevicePixelRatio(0.5*zoneSize);
                }

                /*if (direccionG2 == 0){
                    //ArribaIzq
                    QMatrix rm;
                    rm.rotate(135);
                    ImgFlecha2 = ImgFlecha2->transformed(rm);
                }

                else if (direccionG1 == 1){
                    //Arriba
                    QMatrix rm;
                    rm.rotate(90);
                    ImgFlecha2 = ImgFlecha2->transformed(rm);
                }

                else if (direccionG1 == 2){
                    //ArribaDer
                    QMatrix rm;
                    rm.rotate(45);
                    ImgFlecha2 = ImgFlecha2->transformed(rm);
                }

                else if (direccionG1 == 3){
                    //Izquierda
                    QMatrix rm;
                    rm.rotate(180);
                    ImgFlecha2 = ImgFlecha2->transformed(rm);
                }

                else if (direccionG1 == 4){
                    //Derecha
                    //viene por default
                }

                else if (direccionG1 == 5){
                    //AbajoIzq
                    QMatrix rm;
                    rm.rotate(225);
                    ImgFlecha2 = ImgFlecha2->transformed(rm);
                }

                else if (direccionG1 == 6){
                    //Abajo
                    QMatrix rm;
                    rm.rotate(270);
                    ImgFlecha2 = ImgFlecha2->transformed(rm);
                }

                else if (direccionG1 == 7){
                    //AbajoIDer
                    QMatrix rm;
                    rm.rotate(315);
                    ImgFlecha2 = ImgFlecha2->transformed(rm);
                }*/

                partida->addPixmap(*ImgFlecha2)->moveBy(xActG2,yActG2);
            }
        }

        if (hitG2==0){
            j=26;
            //break;
        }

        else {

            if (aTypeG2==-1){
                j=26;
                //break;
            }
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

    //Cuadro Encima del jugador
    cuadroB = new QPixmap(":/imagenes/cuadro-blanco (copy).png");
    cuadroB->setDevicePixelRatio(0.5*zoneSize);

    resistenciaG1=100;
    resistenciaG2=100;

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
            connect(timer,SIGNAL(timeout()), this, SLOT(AuxGraficarGladiador()));
            timer->start(1000);
        //}
    }

}

void MainWindow::AuxGraficarGladiador(){

    //DibujarTablero();
    //DibujarTorres();

    if (xActG1 > 1 && yActG1>1){
        partida->addPixmap(*cuadroB)->moveBy(xActG1,yActG1);
    }

    if (xActG2 >1 && yActG2>1){
        partida->addPixmap(*cuadroB)->moveBy(xActG2,yActG2);
    }

    QString I;
    I.setNum(iGlad);

    if (resistenciaG1==0 && resistenciaG2==0){
        //QMessageBox::information(this, tr("Gladiadores Matados"), tr("Gladiadores Muertos"));

        //JSON para continuar ciclo
        sendJSON("REINICIAR", "0");
        sendJSON("NEXTPOSITIONG1","1");
        sendJSON("NEXTPOSITIONG2","1");
        partida->clear();
        timer->stop();
        on_Inicio_clicked();

    }

    if (resistenciaG1!=0){
        //Gladiador 1
        sendJSON("XCOORDGP1", I.toStdString());
        sendJSON("YCOORDGP1", I.toStdString());
        //Tirar Flechas
        tirarFlechasG1();
        //QMessageBox::information(this, tr("Gladiador Matado"), tr("Gladiador 2 Muerto, Gladiador 1 Vivo"));
    }

    if (resistenciaG2!=0){
        //Gladiador 2
        sendJSON("XCOORDGP2", I.toStdString());
        sendJSON("YCOORDGP2", I.toStdString());
        //Tirar Flechas
        tirarFlechasG2();
        //QMessageBox::information(this, tr("Gladiador Matado"), tr("Gladiador 1 Muerto, Gladiador 2 Vivo"));
    }


    if ((xActG1==-1 && yActG1==-1) || (xActG2==-1 && yActG2==-1)){
        t=true;
        cout<<"Final del thread"<<endl;
        QMessageBox::information(this, tr("Final de Juego"), tr("Juego Terminado"));
        sendJSON("NEXTPOSITIONG1","1");
        sendJSON("NEXTPOSITIONG2","1");
        sendJSON("REINICIAR","0");
        timer->stop();
        on_Inicio_clicked();
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


    }

    //Resistencia Solicita JSON
    sendJSON("RESISTENCIAG1","1");
    sendJSON("RESISTENCIAG2","2");

    cout<<"Resistencia G1: "<<resistenciaG1<<endl;
    cout<<"Resistencia G2: "<<resistenciaG2<<endl;

    sendJSON("NEXTPOSITIONG1","0");
    sendJSON("NEXTPOSITIONG2","0");

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
        client.sin_addr.s_addr = inet_addr("192.168.100.6"); //192.168.100.6
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

    struct json_object *ResistenciaG1;
    json_object *parsed_jsonResistenciaG1 = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonResistenciaG1, "RESISTENCIAG1", &ResistenciaG1);
    if (json_object_get_string(ResistenciaG1) != 0) {
        resistenciaG1 = stoi(json_object_get_string(ResistenciaG1));
    }

    struct json_object *HITG1;
    json_object *parsed_jsonHITG1 = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonHITG1, "HITG1", &HITG1);
    if (json_object_get_int(HITG1) >= 0){
        hitG1 = (json_object_get_int(HITG1));
    }

    struct json_object *ATYPEG1;
    json_object *parsed_jsonATYPEG1 = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonATYPEG1, "ATYPEG1", &ATYPEG1);
    if (json_object_get_int(ATYPEG1) != 0){
        aTypeG1 = (json_object_get_int(ATYPEG1));
    }

    struct json_object *XCOORDFLECHAG1;
    json_object *parsed_jsonXCOORDFLECHAG1 = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonXCOORDFLECHAG1, "XCOORDFLECHAG1", &XCOORDFLECHAG1);
    if (json_object_get_int(XCOORDFLECHAG1) != 0){
        xCoordG1 = json_object_get_int(XCOORDFLECHAG1);
    }

    struct json_object *YCOORDFLECHAG1;
    json_object *parsed_jsonYCOORDFLECHAG1 = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonYCOORDFLECHAG1, "YCOORDFLECHAG1", &YCOORDFLECHAG1);
    if (json_object_get_int(YCOORDFLECHAG1) != 0){
        yCoordG1 = json_object_get_int(YCOORDFLECHAG1);
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

    struct json_object *ResistenciaG2;
    json_object *parsed_jsonResistenciaG2 = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonResistenciaG2, "RESISTENCIAG2", &ResistenciaG2);
    if (json_object_get_string(ResistenciaG2) != 0) {
        resistenciaG2 = stoi(json_object_get_string(ResistenciaG2));
    }

    struct json_object *HITG2;
    json_object *parsed_jsonHITG2 = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonHITG2, "HITG2", &HITG2);
    if (json_object_get_int(HITG2) >= 0){
        hitG2 = json_object_get_int(HITG2);
    }

    struct json_object *ATYPEG2;
    json_object *parsed_jsonATYPEG2 = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonATYPEG2, "ATYPEG2", &ATYPEG2);
    if (json_object_get_int(ATYPEG2) != 0){
        aTypeG2 = json_object_get_int(ATYPEG2);
    }

    struct json_object *XCOORDFLECHAG2;
    json_object *parsed_jsonXCOORDFLECHAG2 = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonXCOORDFLECHAG2, "XCOORDFLECHAG2", &XCOORDFLECHAG2);
    if (json_object_get_int(XCOORDFLECHAG2) != 0){
        xCoordG2 = json_object_get_int(XCOORDFLECHAG2);
    }

    struct json_object *YCOORDFLECHAG2;
    json_object *parsed_jsonYCOORDFLECHAG2 = json_tokener_parse(recvBuff);
    json_object_object_get_ex(parsed_jsonYCOORDFLECHAG2, "YCOORDFLECHAG2", &YCOORDFLECHAG2);
    if (json_object_get_int(YCOORDFLECHAG2) != 0){
        yCoordG2 = json_object_get_int(YCOORDFLECHAG2);
    }


    ///Se limpian los Buffers
    memset(recvBuff, 0, MAXDATASIZE);
    memset(sendBuff, 0, MAXDATASIZE);

    ::close(fd);

}
