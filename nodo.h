#ifndef NODO_H
#define NODO_H

#include "torres.h"

class Nodo
{
public:
    Nodo();
    int getdata();
    void setData(int _data);
    int getX();
    void setX(int _x);
    int getY();
    void setY(int _y);

    Torres* getTorre();

private:
    int data;
    int x;
    int y;
    Torres* torre;
};

#endif // NODO_H
