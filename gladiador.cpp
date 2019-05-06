#include "gladiador.h"

#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <strings.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <json-c/json.h>
#include <json-c/debug.h>
#include <json-c/json_object.h>

#define PORT 3550
#define MAXDATASIZE 1000

using namespace std;
Gladiador::Gladiador(){};
Gladiador::Gladiador(int generacion)
{
    if (generacion == 1){
        //srand (time(NULL));
        int random = 15 + rand() % (61 - 15);
        setEdad(random);
        random = 1 + rand() % (5 - 1);

        setInteligencia(random);
        random = 1 + rand() % (5 - 1);

        setCondicionFisica(random);
        random = 1 + rand() % (5 - 1);

        setFuerzaSuperior(random);
        random = 1 + rand() % (5 - 1);

        setFuerzaInferior(random);
        setResistencia();
        setExpectativaVida(getResistencia()/10);
        setProbabilidadSupervivencia(getResistencia()-4);
        SendJson();
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

    cout <<"resistencia: " <<resistencia << endl;
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
int Gladiador::SendJson()
{
    /*char* str;
    int fd, numbytes;
    struct sockaddr_in client;

    fd = socket(AF_INET, SOCK_STREAM, 0);

    char buf[MAXDATASIZE];

    struct hostent *he;

    if (fd < 0)
    {
        printf("Error : Could not create socket\n");
        return 1;
    }
    else
    {
        client.sin_family = AF_INET;
        client.sin_port = htons(PORT);
        client.sin_addr.s_addr = inet_addr("192.168.100.28");
        memset(client.sin_zero, '\0', sizeof(client.sin_zero));
    }

    if (::connect(fd, (const struct sockaddr *)&client, sizeof(client)) < 0)
    {
        printf("ERROR connecting to server\n");
        return 1;
    }

    json_object *jobj = json_object_new_object();

    string auxNombre = nombre;
    int n = auxNombre.length();
    char nombreJson[n + 1];
    strcpy(nombreJson, auxNombre.c_str());

    string auxEdad= to_string(edad);
    n = auxEdad.length();
    char edadJson[n + 1];
    strcpy(edadJson, auxEdad.c_str());

    string auxPS = to_string(probabilidadSupervivencia);
    n = auxPS.length();
    char PSJson[n + 1];
    strcpy(PSJson, auxPS.c_str());

    string auxEV = to_string(expectativaVida);
    n = auxEV.length();
    char EVJson[n + 1];
    strcpy(EVJson, auxEV.c_str());

    string auxIntelig = to_string(inteligencia);
    n = auxIntelig.length();
    char inteligJson[n + 1];
    strcpy(inteligJson, auxIntelig.c_str());

    string auxCF = to_string(condicionFisica);
    n = auxCF.length();
    char CFJson[n + 1];
    strcpy(CFJson, auxCF.c_str());

    string auxFS = to_string(fuerzaSuperior);
    n = auxFS.length();
    char FSJson[n + 1];
    strcpy(FSJson, auxFS.c_str());

    string auxFI = to_string(fuerzaInferior);
    n = auxFI.length();
    char FIJson[n + 1];
    strcpy(FIJson, auxFI.c_str());

    string auxResist = to_string(resistencia);
    n = auxResist.length();
    char resistJson[n + 1];
    strcpy(resistJson, auxResist.c_str());
    for (int i = 0; i < n; i++)
        cout << nombreJson[i];

    json_object *jstring = json_object_new_string(nombreJson);
    json_object *jstring2 = json_object_new_string(edadJson);
    json_object *jstring3 = json_object_new_string(PSJson);
    json_object *jstring4 = json_object_new_string(EVJson);
    json_object *jstring5 = json_object_new_string(inteligJson);
    json_object *jstring6 = json_object_new_string(CFJson);
    json_object *jstring7 = json_object_new_string(FSJson);
    json_object *jstring8 = json_object_new_string(FIJson);
    json_object *jstring9 = json_object_new_string(resistJson);

    json_object_object_add(jobj,"Nombre", jstring);
    json_object_object_add(jobj,"Edad", jstring2);
    json_object_object_add(jobj,"ProbabilidadSupervivencia", jstring3);
    json_object_object_add(jobj,"ExpectativaVida", jstring4);
    json_object_object_add(jobj,"Inteligencia", jstring5);
    json_object_object_add(jobj,"CondicionFisica", jstring6);
    json_object_object_add(jobj,"FuerzaSuperior", jstring7);
    json_object_object_add(jobj,"FuerzaInferior", jstring8);
    json_object_object_add(jobj,"Resistencia", jstring9);



    if (strcpy(buf, json_object_to_json_string(jobj)) == NULL) {
        printf("ERROR strcpy()");
        exit(-1);
    }

    if (write(fd, buf, strlen(buf)) == -1)
    {
        printf("ERROR write()");
        exit(-1);
    }

    printf("Written data\n");

    memset(buf, 0, MAXDATASIZE);

    ::close(fd);*/
}
