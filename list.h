#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "node.h"
#include "gladiador.h"

class List{

public:

    Node* getPointerHead();
    void setPointerHead(Node* head);
    void insertFirst(Gladiador *gladiador);
    int getSize();
    Node* getLast();
    void insertLast(Gladiador *gladiador);
private:

    Node* pointerHead= nullptr;

};

#endif // LIST_H
