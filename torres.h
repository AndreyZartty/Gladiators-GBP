#ifndef TORRES_H
#define TORRES_H

#include <QGraphicsPixmapItem>

class Torres
{
public:
    Torres();
    bool getEstado();
    void setEstado(bool _estado);

private:

    bool estado;
};

#endif // TORRES_H
