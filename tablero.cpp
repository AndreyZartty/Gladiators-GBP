#include "tablero.h"
#include <stdio.h>

Tablero::Tablero(QObject *parent) : QObject(parent)
{
    //setPixmap(QPixmap(":/imagenes/fondo.jpg"));
}

int Tablero::generar(int matriz){

    numMatriz = matriz;

    matrizF = new int*[matriz]; //Reservar memoria para las filas
    for (int f=0; f<matriz; f++ ){
        matrizF[f] = new int[matriz]; //Reservar memoria para las columnas
    }

    for (int f=0; f<numMatriz; f++ ){
        for (int c=0; c<numMatriz; c++ ){
            *(*(matrizF+f)+c) = 0;
        }
    }
}

int Tablero::imprimir(){
    printf("Matriz... \n");

    for (int f=0; f<numMatriz; f++ ){
        for (int c=0; c<numMatriz; c++ ){
            printf("[%d]", *(*(matrizF+f)+c));
        }
        printf("\n");
    }

    printf("\n");
}

int Tablero::getnumMatriz(){
    return numMatriz;
}

Tablero::~Tablero(){

    //libera la memeoria que hemos utilizado
    for (int i=0; i<numMatriz; i++){
        delete[] matrizF[i];
    }

    delete[] matrizF;
}
