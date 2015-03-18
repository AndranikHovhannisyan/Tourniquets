#include "addscheduletype.h"
#include "ui_addscheduletype.h"
#include <QDebug>

addScheduleType::addScheduleType(QSqlDatabase db, QWidget *parent) :
    addDialog(db, parent),
    ui(new Ui::addScheduleType)
{
    ui->setupUi(this);
    this->setWindowTitle("add schedule type");
}

addScheduleType::~addScheduleType()
{
    delete ui;
}

void addScheduleType::init() {
    qDebug() << "id =" << id;
}
