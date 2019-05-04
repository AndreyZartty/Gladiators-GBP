#include "poblacion.h"
#include "gladiador.h"

Poblacion::Poblacion()
{
    for (int i=0; i <10; i++){
            Gladiador* gladiador = new Gladiador(getGeneracion());
            insertarGladiador(gladiador);
            cout<< "Se ha creado el gladiador: "<< i+1 <<endl;
    }
}

int Poblacion::getGeneracion()
{
    return generacion;
}

void Poblacion::setGeneracion(int Generacion)
{
    generacion = Generacion;
}

void Poblacion::insertarGladiador(Gladiador *gladiador)
{
    gladiadores.insertLast(gladiador);
}

List Poblacion::getGladiadores()
{
    return gladiadores;
}
