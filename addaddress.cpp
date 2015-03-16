#include "addaddress.h"
#include "ui_addaddress.h"

addAddress::addAddress(QSqlDatabase db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addAddress)
{
    ui->setupUi(this);
}

addAddress::~addAddress()
{
    delete ui;
}
