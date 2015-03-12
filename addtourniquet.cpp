#include "addtourniquet.h"
#include "ui_addtourniquet.h"

addTourniquet::addTourniquet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTourniquet)
{
    ui->setupUi(this);
}

addTourniquet::~addTourniquet()
{
    delete ui;
}
