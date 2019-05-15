#include "visualizarpoblaciones.h"
#include "ui_visualizarpoblaciones.h"

VisualizarPoblaciones::VisualizarPoblaciones(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualizarPoblaciones)
{
    ui->setupUi(this);
}

VisualizarPoblaciones::~VisualizarPoblaciones()
{
    delete ui;
}


void VisualizarPoblaciones::on_botonContinuar_clicked()
{

}

void VisualizarPoblaciones::on_botonMostrar_clicked()
{

}
