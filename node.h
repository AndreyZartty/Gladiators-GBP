/**
  * @file node.h
  * @version 1.0
  * @date 15/05/2019
  * @authors Edgar Gonzales, Ruben Salas, Andrey Sanchez, Jose Solano
  * @title Nodos Graficos
  */


#ifndef NODE_H
#define NODE_H

#include "torres.h"

class Node
{
public:

    /**
     * @brief Node Constructor
     */
    Node();

    /**
     * @brief getdata Devuelve la info del nodo
     * @return data Datos del nodo
     */
    int getdata();

    /**
     * @brief setData Setea los datos del Nodo
     * @param _data Datos a setear
     */
    void setData(int _data);

    /**
     * @brief getX Devuelve el X del nodo
     * @return x X del Nodo
     */
    int getX();

    /**
     * @brief setX Setea el X del Nodo
     * @param _x X a setear
     */
    void setX(int _x);

    /**
     * @brief getY Devuelve el Y del nodo
     * @return y Y del Nodo
     */
    int getY();

    /**
     * @brief setY Setea el Y del nodo
     * @param _y Y a setear
     */
    void setY(int _y);

    /**
     * @brief getTorre Devuelve la torre en el nodo
     * @return torre Torre en el nodo
     */
    Torres* getTorre();

private:
    int data;
    int x;
    int y;
    Torres* torre;
};

#endif // NODE_H
