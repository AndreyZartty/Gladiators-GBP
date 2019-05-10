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

Gladiador* List::sacar(int indice){
    Gladiador* res;
    Node *current = getPointerHead();
    if (indice==0){
        current = current->get_nxtPtr();
        res = pointerHead->get_data();
        pointerHead->set_nxtNd(nullptr);
        setPointerHead(current);
    }else if (indice == getSize()-1) {
        while(indice-1>0){
            current = current->get_nxtPtr();
            indice--;
        }
        res = current->get_data();
        current->set_nxtNd(nullptr);
    }else {
        while(indice-1>0){
            current = current->get_nxtPtr();
            indice--;
        }
        Node *temp = current->get_nxtPtr();
        current->set_nxtNd(temp->get_nxtPtr());
        res = temp->get_data();
        temp->set_nxtNd(nullptr);
    }
    return res;
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

void List::swap(Gladiador *xp, Gladiador *yp)
{
    Gladiador temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void List::bubbleSort()
{
    int n = getSize();
    int i, j;
    for (i = 0; i < n-1; i++){
        for (j = 0; j < n-i-1; j++){
            if (recorrer(j)->getResistencia() < recorrer(j+1)->getResistencia()){
                swap(recorrer(j), recorrer(j+1));
            }
        }
    }
}

void List::vaciar(){
    cout<<"El tamano de la lista antes es: "<<getSize()<<endl;
    int n = getSize();
    while(n>0) {
        sacar(n-1);
        n-=1;
    }
    cout<<"El tamano de la lista es: "<<getSize()<<endl;
}
