#include "torres.h"

Torres::Torres()
{
    torre = new QPixmap(":/imagenes/torre.png");
    torre->setDevicePixelRatio(5);
    flechaSencilla = new QPixmap(":/imagenes/flecha sencilla.png");
    flechaFuego = new QPixmap(":/imagenes/flecha fuego-1.png");
    flechaExplosivo = new QPixmap(":/imagenes/flecha explosiva.png");

    estado = false;
}

QPixmap* Torres::getTorre(){
    return torre;
}

QPixmap* Torres::getFlechaS(){
    return flechaSencilla;
}

QPixmap* Torres::getFlechaF(){
    return flechaFuego;
}

QPixmap* Torres::getFlechaE(){
    return flechaExplosivo;
}

bool Torres::getEstado(){
    return estado;
}

void Torres::setEstado(bool _estado){
    estado = _estado;
}
