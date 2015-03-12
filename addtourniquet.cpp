#include "addtourniquet.h"
#include "ui_addtourniquet.h"

addTourniquet::addTourniquet(QSqlDatabase db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTourniquet)
{
    ui->setupUi(this);
    ui->type->addItem("In");
    ui->type->addItem("Out");
    this->setWindowTitle("add tourniquet");
}

addTourniquet::~addTourniquet()
{
    delete ui;
}
