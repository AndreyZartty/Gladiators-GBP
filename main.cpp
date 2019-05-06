#include <stdio.h>

#include <iostream>
#include "gladiador.h"
#include "poblacion.h"
#include "list.h"

using namespace std;

int main()
{
    srand (time(NULL));
    //Gladiador *g1 = new Gladiador(1);
    //Gladiador *g2 = new Gladiador(1);
    //Gladiador *g3 = new Gladiador(1);
    //Gladiador *g4 = new Gladiador(1);
    //Gladiador *g5 = new Gladiador(1);
    Poblacion *poblacion = new Poblacion();
    poblacion->getMejor();
    /**nuevo->setEdad(25);
    nuevo->setInteligencia(10);
    nuevo->setCondicionFisica(10);
    nuevo->setFuerzaInferior(10);
    nuevo->setFuerzaSuperior(10);
    nuevo->setResistencia();**/

}
