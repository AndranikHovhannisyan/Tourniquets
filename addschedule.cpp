#include "addschedule.h"
#include "ui_addschedule.h"
#include <QSqlTableModel>

addSchedule::addSchedule(QSqlDatabase db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addSchedule)
{
    ui->setupUi(this);

    QSqlTableModel *scheduleTypeModel = new QSqlTableModel(this, db);
    scheduleTypeModel->setTable("schedule_type");
    scheduleTypeModel->select();
    ui->scheduleType->setModel(scheduleTypeModel);
}

addSchedule::~addSchedule()
{
    delete ui;
}
