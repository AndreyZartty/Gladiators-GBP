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
    List getPadres();
    void setMejor();
    Gladiador* getMejor();
    string getNombrePoblacion();
    void nuevageneracion();


private:
    string nombrePoblacion;
    List gladiadores;
    List padres;
    int generacion=1;
    Gladiador* mejor;
};

#endif // POBLACION_H
