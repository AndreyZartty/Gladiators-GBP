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
    Poblacion *poblacion = new Poblacion("Lannister");
    poblacion->getMejor();
    //poblacion->setPadres();

    //Poblacion *poblacion2 = new Poblacion("Stark");
    //poblacion2->getMejor();

    //poblacion->getGladiadores().bubbleSort();
    poblacion->nuevageneracion();
    poblacion->nuevageneracion();
    poblacion->nuevageneracion();
    poblacion->nuevageneracion();
    poblacion->nuevageneracion();
    poblacion->nuevageneracion();
    poblacion->nuevageneracion();
    poblacion->nuevageneracion();
    poblacion->nuevageneracion();
    poblacion->nuevageneracion();
    poblacion->nuevageneracion();
    poblacion->nuevageneracion();
    poblacion->nuevageneracion();
    poblacion->nuevageneracion();
    poblacion->nuevageneracion();
    poblacion->nuevageneracion();




    cout<<"POBLACION"<<endl;
    for (int i=0;i<poblacion->getGladiadores().getSize(); i++) {
        if (poblacion->getGladiadores().recorrer(i)->getMuerto()){
            cout<<poblacion->getGladiadores().recorrer(i)->getNombre()<<" (muerto)"<<endl;
        }else {
            cout<<poblacion->getGladiadores().recorrer(i)->getNombre()<<poblacion->getGladiadores().recorrer(i)->getResistencia()<<endl;
        }
    }
    //for (int i=0;i<poblacion->getPadres().getSize(); i++) {
        //cout<<poblacion->getPadres().recorrer(i)->getNombre()<<endl;
    //}

    //Gladiador *g1 = new Gladiador(1);
    //Gladiador *g2 = new Gladiador(1);
    //Gladiador *g3 = new Gladiador(2, g1, g2);
    //cout<<00000000000<<endl;
    //poblacion2->nuevageneracion();
    /**nuevo->setEdad(25);
    nuevo->setInteligencia(10);
    nuevo->setCondicionFisica(10);
    nuevo->setFuerzaInferior(10);
    nuevo->setFuerzaSuperior(10);
    nuevo->setResistencia();**/
}
