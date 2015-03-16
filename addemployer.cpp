#include "addemployer.h"
#include "ui_addemployer.h"

addEmployer::addEmployer(QSqlDatabase db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addEmployer)
{
    ui->setupUi(this);
}

addEmployer::~addEmployer()
{
    delete ui;
}
