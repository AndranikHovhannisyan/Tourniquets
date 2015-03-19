#include "addschedule.h"
#include "ui_addschedule.h"
#include "constants.h"
#include <QSqlTableModel>
#include <QStringList>
#include <QDebug>

addSchedule::addSchedule(QSqlDatabase db, QWidget *parent) :
    addDialog(db, parent),
    ui(new Ui::addSchedule)
{
    ui->setupUi(this);
    this->setWindowTitle("add schedule");

    QSqlTableModel *scheduleTypeModel = new QSqlTableModel(this, db);
    scheduleTypeModel->setTable("schedule_type");
    scheduleTypeModel->select();
    ui->scheduleType->setModel(scheduleTypeModel);
}

addSchedule::~addSchedule()
{
    delete ui;
}

void addSchedule::init() {
    qDebug() << "id =" << id;
}

void addSchedule::claer() {

}

void addSchedule::populateData(QSqlRecord &rec) {

}
