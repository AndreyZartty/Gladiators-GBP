#include "poblacion.h"
#include "gladiador.h"

Poblacion::Poblacion()
{
    setGeneracion(1);
    for (int i=0; i <10; i++){
            Gladiador* gladiador = new Gladiador(getGeneracion());
            insertarGladiador(gladiador);
            cout<< "Se ha creado el gladiador: "<< i+1 <<endl;
    }
    setMejor();
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

void Poblacion::setMejor(){
    Gladiador* temp;
    mejor=gladiadores.recorrer(0);
    for(int i=0;i<gladiadores.getSize();i++){
        temp = gladiadores.recorrer(i);
        if(temp->getResistencia()>mejor->getResistencia()){
            mejor=temp;
        }
    }
}

Gladiador* Poblacion::getMejor(){
    cout<<"El mejor es: "<<mejor->getResistencia()<<endl;
    return mejor;
}
