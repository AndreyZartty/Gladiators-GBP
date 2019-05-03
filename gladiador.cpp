#include "gladiador.h"
#include <time.h>

Gladiador::Gladiador(int generacion)
{
    if (generacion == 1){
        srand (time(NULL));
        int random = rand() % 60 +15;
        edad = random;
        random = rand() % 4 +1;
        inteligencia = random;
        random = rand() % 4 +1;
        condicionFisica = random;
        random = rand() % 4 +1;
        fuerzaSuperior = random;
        random = rand() % 4 +1;
        fuerzaInferior = random;
        setResistencia();
    }
    else {
        cout << "Introduzca los padres si no es la primera generacion" << endl;
    }
}
Gladiador::Gladiador(int generacion, Gladiador *padre1, Gladiador *parte2)
{
    if (generacion == 1){
        cout << "No introduzca padres, ya que no es de la primera generacion" << endl;
    }
    else {

    }
}

void Gladiador::setNombre(string Nombre)
{
    nombre = Nombre;
}

void Gladiador::setEdad(int Edad)
{
    edad = Edad;
}

void Gladiador::setProbabilidadSupervivencia(int PS)
{
    probabilidadSupervivencia = PS;
}

void Gladiador::setExpectativaVida(int EV)
{
    expectativaVida = EV;
}

void Gladiador::setInteligencia(int Inteligencia)
{
    inteligencia = Inteligencia;
}

void Gladiador::setCondicionFisica(int CF)
{
    condicionFisica = CF;
}

void Gladiador::setFuerzaSuperior(int FS)
{
    fuerzaSuperior = FS;
}

void Gladiador::setFuerzaInferior(int FI)
{
    fuerzaInferior = FI;
}

void Gladiador::setResistencia()
{
    int resist=0;
    if(25 <= edad && edad <= 45){
        resist += 20;
    }
    else if (25 > edad){
        resist += 15;
    }
    else if (45 < edad){
        resist += 10;
    }
    resist += 2*inteligencia;
    resist += 2*condicionFisica;
    resist += 2*fuerzaInferior;
    resist += 2*fuerzaSuperior;

    resistencia = resist;

    cout << resistencia << endl;
}



string Gladiador::getNombre()
{
    return nombre;
}

int Gladiador::getEdad()
{
    return edad;
}

int Gladiador::getProbabilidadSupervivencia()
{
    return probabilidadSupervivencia;
}

int Gladiador::getExpectativaVida()
{
    return expectativaVida;
}

int Gladiador::getInteligencia()
{
    return inteligencia;
}

int Gladiador::getCondicionFisica()
{
    return condicionFisica;
}

int Gladiador::getFuerzaSuperior()
{
    return fuerzaSuperior;
}

int Gladiador::getFuerzaInferior()
{
    return fuerzaInferior;
}

int Gladiador::getResistencia()
{
    return resistencia;
}
