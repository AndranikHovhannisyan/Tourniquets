#include "addschedule.h"
#include "ui_addschedule.h"
#include "constants.h"
#include <QSqlTableModel>
#include <QStringList>
#include <QDebug>

#include "ScheduleType/scheduletype.h"

addSchedule::addSchedule(QSqlRelationalTableModel *tableModel, QWidget *parent) :
    addDialog(tableModel, parent),
    ui(new Ui::addSchedule)
{
    ui->setupUi(this);
    this->setWindowTitle("Ավելացնել Գրաֆիկ");

    ui->scheduleType->setModel(ScheduleType::create(model->database())->getModel());

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}

addSchedule::~addSchedule()
{
    delete ui;
}

void addSchedule::init(QSqlRecord &record)
{
    ui->stInTime->setTime(record.value("standart_in_time").toTime());
    ui->stOutTime->setTime(record.value("standart_out_time").toTime());
    ui->mondayDayIn->setTime(record.value("mon_in").toTime());
    ui->mondayDayOut->setTime(record.value("mon_out").toTime());
    ui->thursdayDayIn->setTime(record.value("thrsd_in").toTime());
    ui->thursdayDayOut->setTime(record.value("thrsd_out").toTime());
    ui->wednesdayDayIn->setTime(record.value("wed_in").toTime());
    ui->wednesdayDayOut->setTime(record.value("wed_out").toTime());
    ui->thusdayDayIn->setTime(record.value("thsd_in").toTime());
    ui->thusdayDayOut->setTime(record.value("thsd_out").toTime());
    ui->fridayDayIn->setTime(record.value("fri_in").toTime());
    ui->fridayDayOut->setTime(record.value("fri_out").toTime());
    ui->saturdayDayIn->setTime(record.value("sat_in").toTime());
    ui->saturdayDayOut->setTime(record.value("sat_out").toTime());
    ui->sundayDayIn->setTime(record.value("sun_in").toTime());
    ui->sundayDayOut->setTime(record.value("sun_out").toTime());
    ui->interval->setText(record.value("interval_in_days").toString());

    //TODO: this is bad solution but can't find good solution yet
    QSqlRelationalTableModel* scheduleTypeModel = ScheduleType::create(model->database())->getModel();
    int scheduleTypeCount = scheduleTypeModel->rowCount();
    for(int i = 0; i < scheduleTypeCount; i++) {
        if (scheduleTypeModel->record(i).value("id").toInt() == record.value("schedule_type_id").toInt()) {
            ui->scheduleType->setCurrentIndex(i);
            break;
        }
    }

}

void addSchedule::clear()
{
    ui->scheduleType->setCurrentIndex(0);
    ui->stInTime->setTime(QTime(0, 0));
    ui->stOutTime->setTime(QTime(0, 0));
    ui->mondayDayIn->setTime(QTime(0, 0));
    ui->mondayDayOut->setTime(QTime(0, 0));
    ui->thursdayDayIn->setTime(QTime(0, 0));
    ui->thursdayDayOut->setTime(QTime(0, 0));
    ui->wednesdayDayIn->setTime(QTime(0, 0));
    ui->wednesdayDayOut->setTime(QTime(0, 0));
    ui->thusdayDayIn->setTime(QTime(0, 0));
    ui->thusdayDayOut->setTime(QTime(0, 0));
    ui->fridayDayIn->setTime(QTime(0, 0));
    ui->fridayDayOut->setTime(QTime(0, 0));
    ui->saturdayDayIn->setTime(QTime(0, 0));
    ui->saturdayDayOut->setTime(QTime(0, 0));
    ui->sundayDayIn->setTime(QTime(0, 0));
    ui->sundayDayOut->setTime(QTime(0, 0));
    ui->interval->setText("");
}

void addSchedule::populateData(QSqlRecord &record)
{
    record.setValue(record.indexOf("standart_in_time"), QVariant(ui->stInTime->time()));
    record.setValue(record.indexOf("standart_out_time"), QVariant(ui->stOutTime->time()));
    record.setValue(record.indexOf("mon_in"), QVariant(ui->mondayDayIn->time()));
    record.setValue(record.indexOf("mon_out"), QVariant(ui->mondayDayOut->time()));
    record.setValue(record.indexOf("thrsd_in"), QVariant(ui->thursdayDayIn->time()));
    record.setValue(record.indexOf("thrsd_out"), QVariant(ui->thursdayDayOut->time()));
    record.setValue(record.indexOf("wed_in"), QVariant(ui->wednesdayDayIn->time()));
    record.setValue(record.indexOf("wed_out"), QVariant(ui->wednesdayDayOut->time()));
    record.setValue(record.indexOf("thsd_in"), QVariant(ui->thusdayDayIn->time()));
    record.setValue(record.indexOf("thsd_out"), QVariant(ui->thusdayDayOut->time()));
    record.setValue(record.indexOf("fri_in"), QVariant(ui->fridayDayIn->time()));
    record.setValue(record.indexOf("fri_out"), QVariant(ui->fridayDayOut->time()));
    record.setValue(record.indexOf("sat_in"), QVariant(ui->saturdayDayIn->time()));
    record.setValue(record.indexOf("sat_out"), QVariant(ui->saturdayDayOut->time()));
    record.setValue(record.indexOf("sun_in"), QVariant(ui->sundayDayIn->time()));
    record.setValue(record.indexOf("sun_out"), QVariant(ui->sundayDayOut->time()));
    record.setValue(record.indexOf("interval_in_days"), QVariant(ui->interval->text()));


    int scheduleTypeId = ScheduleType::create(model->database())
                                        ->getModel()
                                        ->record(ui->scheduleType->currentIndex())
                                        .value("id").toInt();
    record.setValue(record.indexOf("schedule_type_id"), QVariant(scheduleTypeId));
}
