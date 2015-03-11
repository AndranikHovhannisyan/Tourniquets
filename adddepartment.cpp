#include "adddepartment.h"
#include "ui_adddepartment.h"

addDepartment::addDepartment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDepartment)
{
    ui->setupUi(this);
}

addDepartment::~addDepartment()
{
    delete ui;
}
