#include "nextgen.h"
#include "ui_nextgen.h"

NextGen::NextGen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NextGen)
{
    ui->setupUi(this);
}

NextGen::~NextGen()
{
    delete ui;
}

void NextGen::modificarLabel(int i, QString label){

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
    if (i==7){
        ui->expectativa->setText(label);
    }
}
