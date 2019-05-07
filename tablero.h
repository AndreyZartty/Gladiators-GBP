#ifndef TABLERO_H
#define TABLERO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "nodo.h"

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

    Nodo* getNode(int f, int c);

    int imprimir();

signals:

private:
    int numMatriz;

    Nodo **matrizF;

    Nodo* nodo;


public slots:
};

#endif // TABLERO_H
