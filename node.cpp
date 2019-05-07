#include "node.h"

Node::Node()
{
    torre = new Torres();
}

int Node::getdata(){
    return data;
}

void Node::setData(int _data){
    data=_data;
}

int Node::getX(){
    return x;
}

void Node::setX(int _x){
    x=_x;
}

int Node::getY(){
    return y;
}

void Node::setY(int _y){
    y=_y;
}

Torres* Node::getTorre(){
    return torre;
}
