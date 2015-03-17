#include "addschedule.h"
#include "ui_addschedule.h"
#include "constants.h"
#include <QSqlTableModel>
#include <QStringList>

addSchedule::addSchedule(QSqlDatabase db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addSchedule)
{
    ui->setupUi(this);
    this->db = db;
    this->setWindowTitle("add schedule");

    /*
    QMap<int, QString> weekDays = Constants::getWeekDays();
    QStringList strList;
    strList << weekDays[0]
            << weekDays[1]
            << weekDays[2]
            << weekDays[3]
            << weekDays[4]
            << weekDays[5]
            << weekDays[6];

    ui->weekDays->addItems(strList);
*/
    QSqlTableModel *scheduleTypeModel = new QSqlTableModel(this, db);
    scheduleTypeModel->setTable("schedule_type");
    scheduleTypeModel->select();
    ui->scheduleType->setModel(scheduleTypeModel);
}

addSchedule::~addSchedule()
{
    delete ui;
}
