/**
  * @file nextgen.h
  * @version 1.0
  * @date 15/05/2019
  * @authors Edgar Gonzales, Ruben Salas, Andrey Sanchez, Jose Solano
  * @title Informacion del Gladiador Seleccionado de la Primera Generacion
  */

#ifndef NEXTGEN_H
#define NEXTGEN_H

#include <QDialog>

namespace Ui {
class NextGen;
}

class NextGen : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief NextGen Crea la ventana de estadisticas en tiempo real en la ventana principal
     * @param parent Ventana Principal
     */
    explicit NextGen(QWidget *parent = 0);
    ~NextGen();

    /**
     * @brief modificarLabel Modifica y muestra los atributos del gladiador
     * @param i Identificador de caracteristica
     * @param label Label a modificar
     */
    void modificarLabel(int i, QString label);

private:
    Ui::NextGen *ui;
};

#endif // NEXTGEN_H
