#include "nodo.h"

Nodo::Nodo()
{
    torre = new Torres();
}

int Nodo::getdata(){
    return data;
}

void Nodo::setData(int _data){
    data=_data;
}

int Nodo::getX(){
    return x;
}

void Nodo::setX(int _x){
    x=_x;
}

int Nodo::getY(){
    return y;
}

void Nodo::setY(int _y){
    y=_y;
}

Torres* Nodo::getTorre(){
    return torre;
}
