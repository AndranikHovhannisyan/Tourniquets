#include "addphone.h"
#include "ui_addphone.h"

addPhone::addPhone(QSqlDatabase db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addPhone)
{
    ui->setupUi(this);
}

addPhone::~addPhone()
{
    delete ui;
}
