#include "nextgen2.h"
#include "ui_nextgen2.h"

NextGen2::NextGen2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NextGen2)
{
    ui->setupUi(this);
}

NextGen2::~NextGen2()
{
    delete ui;
}

void NextGen2::modificarLabel(int i, QString label){

    //ui->V1A->setText("V"+QString::number(procesoA->getVehiculo1()->getTipo())+":");

    if (i==0){
        ui->nombre->setText(label);
    }

    if (i==1){
        ui->edad->setText(label);
    }

    if (i==2){
        ui->resistencia->setText(label);
    }

    if (i==3){
        ui->probabilidad->setText(label);
    }

    if (i==4){
        ui->inteligencia->setText(label);
    }

    if (i==5){
        ui->tronco_superior->setText(label);
    }
    if (i==6){
        ui->tronco_inferior->setText(label);
    }
}
