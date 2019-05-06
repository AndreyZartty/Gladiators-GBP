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
    void setMejor();
    Gladiador* getMejor();

private:
    List gladiadores;
    int generacion=1;
    Gladiador* mejor;
};

#endif // POBLACION_H
