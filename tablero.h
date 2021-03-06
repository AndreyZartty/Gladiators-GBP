#ifndef TABLERO_H
#define TABLERO_H

#include <QObject>
#include <QGraphicsPixmapItem>

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

    int imprimir();

signals:

private:
    int numMatriz;

    int **matrizF;


public slots:
};

#endif // TABLERO_H
