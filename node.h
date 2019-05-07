#ifndef NODE_H
#define NODE_H

#include "torres.h"

class Node
{
public:
    Node();
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

#endif // NODE_H
