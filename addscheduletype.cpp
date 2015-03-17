#include "addscheduletype.h"
#include "ui_addscheduletype.h"

addScheduleType::addScheduleType(QSqlDatabase db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addScheduleType)
{
    ui->setupUi(this);
    this->db = db;
    this->setWindowTitle("add schedule type");
}

addScheduleType::~addScheduleType()
{
    delete ui;
}
