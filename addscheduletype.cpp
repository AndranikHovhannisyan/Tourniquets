#include "addscheduletype.h"
#include "ui_addscheduletype.h"

addScheduleType::addScheduleType(QSqlDatabase db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addScheduleType)
{
    ui->setupUi(this);
}

addScheduleType::~addScheduleType()
{
    delete ui;
}
