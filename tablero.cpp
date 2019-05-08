#include "tablero.h"
#include <stdio.h>

Tablero::Tablero(QObject *parent) : QObject(parent)
{

}

int Tablero::generar(int matriz){

    numMatriz = matriz;

    matrizF = new Node*[matriz]; //Reservar memoria para las filas
    for (int f=0; f<matriz; f++ ){
        matrizF[f] = new Node[matriz]; //Reservar memoria para las columnas
    }

    for (int f=0; f<numMatriz; f++ ){
        for (int c=0; c<numMatriz; c++ ){
            (*(matrizF+f)+c)->setData(0);
        }
    }
}

int Tablero::imprimir(){
    printf("Matriz... \n");

    for (int f=0; f<numMatriz; f++ ){
        for (int c=0; c<numMatriz; c++ ){
            printf("[%d]", (*(matrizF+f)+c)->getdata());
        }
        printf("\n");
    }

    printf("\n");
}

int Tablero::getnumMatriz(){
    return numMatriz;
}

Node* Tablero::getNode(int f, int c){
    return (*(matrizF+f)+c);
}

Tablero::~Tablero(){

    //libera la memeoria que hemos utilizado
    for (int i=0; i<numMatriz; i++){
        delete[] matrizF[i];
    }

    delete[] matrizF;
}
