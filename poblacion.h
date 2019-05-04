#ifndef POBLACION_H
#define POBLACION_H

#include "gladiador.h"
#include "list.h"

class Poblacion
{
public:
    Poblacion();
    int getGeneracion();
    void setGeneracion(int Generacion);
    void insertarGladiador(Gladiador* gladiador);
    List getGladiadores();

private:
    List gladiadores;
    int generacion=1;
};

#endif // POBLACION_H
