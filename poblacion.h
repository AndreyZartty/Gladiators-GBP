#ifndef POBLACION_H
#define POBLACION_H

#include "gladiador.h"
#include "list.h"

class Poblacion
{
public:
    Poblacion(string _nombrePoblacion);
    int getGeneracion();
    void setGeneracion(int Generacion);
    void insertarGladiador(Gladiador* gladiador);
    List getGladiadores();
    void setMejor();
    Gladiador* getMejor();
    string getNombrePoblacion();

private:
    string nombrePoblacion;
    List gladiadores;
    int generacion=1;
    Gladiador* mejor;
};

#endif // POBLACION_H
