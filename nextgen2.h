/**
  * @file nextgen2.h
  * @version 1.0
  * @date 15/05/2019
  * @authors Edgar Gonzales, Ruben Salas, Andrey Sanchez, Jose Solano
  * @title Informacion del Gladiador Seleccionado de la Segunda Generacion
  */


#ifndef NEXTGEN2_H
#define NEXTGEN2_H

#include <QWidget>

namespace Ui {
class NextGen2;
}

class NextGen2 : public QWidget
{
    Q_OBJECT

public:

    /**
     * @brief NextGen2 Crea la ventana de estadisticas en tiempo real en la ventana principal
     * @param parent Ventana Principal
     */
    explicit NextGen2(QWidget *parent = 0);
    ~NextGen2();

    /**
     * @brief modificarLabel Modifica y muestra los atributos del gladiador
     * @param i Identificador de caracteristica
     * @param label Label a modificar
     */
    void modificarLabel(int i, QString label);

private:
    Ui::NextGen2 *ui;
};

#endif // NEXTGEN2_H
