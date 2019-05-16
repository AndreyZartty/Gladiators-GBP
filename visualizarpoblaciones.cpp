#include "visualizarpoblaciones.h"
#include "ui_visualizarpoblaciones.h"

VisualizarPoblaciones::VisualizarPoblaciones(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualizarPoblaciones)
{
    ui->setupUi(this);

    BC=false;
    BV=false;
}

VisualizarPoblaciones::~VisualizarPoblaciones()
{
    delete ui;
}


void VisualizarPoblaciones::on_botonContinuar_clicked()
{
    BC=true;
}

void VisualizarPoblaciones::on_botonMostrar_clicked()
{
    BV=true;
}

bool VisualizarPoblaciones::botonV(){
    return BV;
}

bool VisualizarPoblaciones::botonC(){
    return BC;
}
