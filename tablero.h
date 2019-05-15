/**
  * @file tablero.h
  * @version 1.0
  * @date 15/05/2019
  * @authors Edgar Gonzales, Ruben Salas, Andrey Sanchez, Jose Solano
  * @title Laberinto de Obstaculos Grafico
  */


#ifndef TABLERO_H
#define TABLERO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "node.h"

class Tablero : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    /**
     * @brief Tablero Dibuja el tablero en la ventana principal
     * @param parent Ventana principal
     */
    explicit Tablero(QObject *parent = 0);

    /**
     * @brief getInstance Devuelve la instancia al tablero
     * @return instance Instancia al tablero
     */
    static Tablero& getInstance(){
               static Tablero instance;
               return instance;
    }

    ~Tablero();

    /**
     * @brief generar Genera una matriz de x tamaño
     * @param matriz Tamaño de la matriz
     * @return int Finaliza la funcion
     */
    int generar(int matriz);

    /**
     * @brief getnumMatriz Devuelve el tamaño de la matriz
     * @return numMatriz Tamaño de la matriz
     */
    int getnumMatriz();

    /**
     * @brief getNode Devuelve un nodo de la matriz
     * @param f Int para calcular ubicacion
     * @param c Int para calcular ubicacion
     * @return Node Nodo buscado
     */
    Node* getNode(int f, int c);

    /**
     * @brief imprimir Imprime el tablero en consola
     * @return int Posicion de la matriz
     */
    int imprimir();

signals:

private:
    int numMatriz;
    Node **matrizF;
    Node* nodo;

public slots:
};

#endif // TABLERO_H
