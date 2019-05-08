#include "torres.h"

Torres::Torres()
{
    estado = false;
}

bool Torres::getEstado(){
    return estado;
}

void Torres::setEstado(bool _estado){
    estado = _estado;
}
