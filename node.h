#ifndef NODE_H
#define NODE_H

#include "gladiador.h"

class Node {
public:
    Node();
    Node(Node* _nxtPtr, Gladiador* _data);
    void set_data(Gladiador* _data);
    void set_nxtNd(Node* node);
    Gladiador* get_data();
    Node* get_nxtPtr();
private:
    Gladiador* data;
    Node* nxtPtr;
};

#endif // NODE_H
