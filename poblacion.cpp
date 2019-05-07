#include "poblacion.h"
#include "gladiador.h"

#include <stdio.h>

Poblacion::Poblacion(string _nombrePoblacion)
{   
    nombrePoblacion = _nombrePoblacion;
    char vocales [] = {"aeiou"};
    char consonantes [] = {"bcdfghjlmnprstv"};
    string nombre;
    setGeneracion(1);
    for (int i=0; i <10; i++){
            nombre = "";
            Gladiador* gladiador = new Gladiador(getGeneracion());
            for (int i = 3; i > 0; i--){
                int r1 = rand() % 14;
                int r2 = rand() % 4;
                char letra1 = consonantes[r1];
                char letra2 = vocales[r2];
                string s1 (1, letra1);
                string s2 (1, letra2);
                nombre = nombre+s1+s2;
            }
            gladiador->setNombre(nombre);
            insertarGladiador(gladiador);
            cout<< "Se ha creado el gladiador: "<< gladiador->getNombre() <<endl;
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

string Poblacion::getNombrePoblacion(){
    return nombrePoblacion;
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
    cout<<"El mejor de la poblacion "<< nombrePoblacion <<" es: "<<mejor->getNombre()<<endl;
    return mejor;
}

void Poblacion::nuevageneracion(){
    setGeneracion(generacion++);

    Gladiador* temp;
    for (int i=0;i<gladiadores.getSize();i++) {
        temp = gladiadores.recorrer(i);
        temp->setEdad(temp->getEdad()+15);
        temp->setResistencia();
    }
}
