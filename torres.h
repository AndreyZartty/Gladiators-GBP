/**
  * @file torres.h
  * @version 1.0
  * @date 15/05/2019
  * @authors Edgar Gonzales, Ruben Salas, Andrey Sanchez, Jose Solano
  * @title Torres Graficas
  */


#ifndef TORRES_H
#define TORRES_H

#include <QGraphicsPixmapItem>

class Torres
{
public:

    /**
     * @brief Torres Constructor
     */
    Torres();

    /**
     * @brief getEstado Devuelve un boolean indicando su estado
     * @return estado Estado de la torre
     */
    bool getEstado();

    /**
     * @brief setEstado Setea el estado de la torre
     * @param _estado Boolean a setear
     */
    void setEstado(bool _estado);

private:

    bool estado;
};

#endif // TORRES_H
