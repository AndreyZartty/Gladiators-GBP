#ifndef GLADIADOR_H
#define GLADIADOR_H

#include <iostream>

using namespace std;


class Gladiador
{
public:
    Gladiador(int generacion);
    Gladiador(int generacion, Gladiador *padre1, Gladiador *parte2);
    void setNombre(string Nombre);
    void setEdad(int Edad);
    void setProbabilidadSupervivencia(int PS);
    void setExpectativaVida(int EV);
    void setInteligencia(int Inteligencia);
    void setCondicionFisica(int CF);
    void setFuerzaSuperior(int FS);
    void setFuerzaInferior(int FI);
    void setResistencia();
    int getEdad();
    int getProbabilidadSupervivencia();
    int getExpectativaVida();
    int getInteligencia();
    int getCondicionFisica();
    int getFuerzaSuperior();
    int getFuerzaInferior();
    int getResistencia();
    string getNombre();

private:
    string nombre;
    int edad;
    int probabilidadSupervivencia;
    int expectativaVida;
    int inteligencia;
    int condicionFisica;
    int fuerzaSuperior;
    int fuerzaInferior;
    int resistencia;
    int SendJson();
};

#endif // GLADIADOR_H
