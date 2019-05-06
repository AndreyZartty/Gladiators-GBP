#include "list.h"
#include <iostream>

Node* List::getPointerHead() {
    return pointerHead;
}

void List::setPointerHead(Node* head) {
    pointerHead = head;
}
void List::insertFirst(Gladiador* gladiador) {
    Node* pointeraux = new Node(pointerHead, gladiador);
    setPointerHead(pointeraux);
}

int List::getSize() {
    Node *current = getPointerHead();
    int c=0;
    while(current != nullptr){
        current = current->get_nxtPtr();
        c++;
    }
    return c;
}

Gladiador* List::recorrer(int indice){
    Node *current = getPointerHead();
    while(indice>0){
        current = current->get_nxtPtr();
        indice--;
    }
    return current->get_data();
}

Node *List::getLast() {
    Node *current = getPointerHead();
    while(current->get_nxtPtr() != nullptr){
        current = current->get_nxtPtr();
    }
    return current;
}

void List::insertLast(Gladiador* gladiador) {
    Node* aux = new Node(nullptr, gladiador);
    if(pointerHead==nullptr){
        setPointerHead(aux);
    }
    else{
        Node *current = getPointerHead();
        while(current->get_nxtPtr() != nullptr){
            current = current->get_nxtPtr();
        }
        current->set_nxtNd(aux);
    }

}
