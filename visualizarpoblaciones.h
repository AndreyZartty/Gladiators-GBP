/**
  * @file visualizarpoblaciones.h
  * @version 1.0
  * @date 15/05/2019
  * @authors Edgar Gonzales, Ruben Salas, Andrey Sanchez, Jose Solano
  * @title Visualizacion grafica del avance genetico
  */


#ifndef VISUALIZARPOBLACIONES_H
#define VISUALIZARPOBLACIONES_H

#include <QWidget>

namespace Ui {
class VisualizarPoblaciones;
}

class VisualizarPoblaciones : public QWidget
{
    Q_OBJECT

public:

    /**
     * @brief VisualizarPoblaciones Dibuja una pantalla de info historica de las poblaciones
     * @param parent Ventana principal
     */
    explicit VisualizarPoblaciones(QWidget *parent = 0);
    ~VisualizarPoblaciones();

private slots:

    /**
     * @brief on_botonContinuar_clicked Continua la animacion
     */
    void on_botonContinuar_clicked();

    /**
     * @brief on_botonMostrar_clicked Muestra la info historica de las poblaciones
     */
    void on_botonMostrar_clicked();

private:
    Ui::VisualizarPoblaciones *ui;
};

#endif // VISUALIZARPOBLACIONES_H
