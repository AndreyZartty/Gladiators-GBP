#ifndef TORRES_H
#define TORRES_H

#include <QGraphicsPixmapItem>

class Torres
{
public:
    Torres();

    QPixmap* getTorre();
    QPixmap* getFlechaS();
    QPixmap* getFlechaF();
    QPixmap* getFlechaE();

    bool getEstado();
    void setEstado(bool _estado);

private:
    QPixmap *torre;
    QPixmap *flechaSencilla;
    QPixmap *flechaFuego;
    QPixmap *flechaExplosivo;

    bool estado;
};

#endif // TORRES_H
