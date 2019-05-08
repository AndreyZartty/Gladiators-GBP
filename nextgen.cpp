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
