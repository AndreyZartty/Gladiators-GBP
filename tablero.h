#ifndef TABLERO_H
#define TABLERO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "node.h"

class Tablero : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Tablero(QObject *parent = 0);

    static Tablero& getInstance(){
               static Tablero instance;
               return instance;
    }

    ~Tablero();
    int generar(int matriz);
    int getnumMatriz();
    Node* getNode(int f, int c);
    int imprimir();
    QPixmap* getcuadroN();
    QPixmap* getcuadroB();

signals:

private:
    int numMatriz;
    Node **matrizF;
    Node* nodo;
    QPixmap *cuadroN;
    QPixmap *cuadroB;


public slots:
};

#endif // TABLERO_H
