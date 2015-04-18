#include "adddepartment.h"
#include "ui_adddepartment.h"
#include <QSqlTableModel>
#include <QDebug>

#include "Employer/employer.h"
#include "Schedule/schedule.h"

addDepartment::addDepartment(QSqlRelationalTableModel *tableModel, QSqlDatabase *db, QWidget *parent) :
    addDialog(tableModel, parent),
    ui(new Ui::addDepartment)
{
    ui->setupUi(this);
    this->setWindowTitle("Ավելացնել բաժին");

    QSqlRelationalTableModel* employerModel = Employer::create(tableModel->database())->getModel();
    QSqlRelationalTableModel* scheduleModel = Schedule::create(tableModel->database())->getModel();

    ui->managers->setModel(employerModel);
    ui->schedule->setModel(scheduleModel);

    //Populate comboIndexManagerId
    int employerCount = employerModel->rowCount();
    for(int i = 0; i < employerCount; i++) {
        comboIndexManagerId[employerModel->record(i).value("id").toInt()] = i;
    }

    //Populate comboIndexScheduleId
    int scheduleCount = scheduleModel->rowCount();
    for(int i = 0; i < scheduleCount; i++) {
        comboIndexScheduleId[scheduleModel->record(i).value("id").toInt()] = i;
    }

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}

addDepartment::~addDepartment()
{
    delete ui;
}

void addDepartment::init(QSqlRecord &record)
{
    ui->dep_name->setText(record.value("name").toString());
    ui->managers->setCurrentIndex(comboIndexManagerId[record.value("manager_id").toInt()]);
    ui->schedule->setCurrentIndex(comboIndexScheduleId[record.value("schedule_id").toInt()]);
}

/**
 * @brief addDepartment::clear
 */
void addDepartment::clear() {
    ui->dep_name->setText("");
    ui->managers->setCurrentIndex(0);
    ui->schedule->setCurrentIndex(0);
}

#include <QSqlRecord>

void addDepartment::populateData(QSqlRecord &record)
{
    record.setValue(record.indexOf("name"), QVariant(ui->dep_name->text()));

    int employerId = Employer::create(model->database())
                                        ->getModel()
                                        ->record(ui->managers->currentIndex())
                                        .value("id").toInt();
    record.setValue(record.indexOf("manager_id"), QVariant(employerId));


    int scheduleId = Schedule::create(model->database())
                                        ->getModel()
                                        ->record(ui->schedule->currentIndex())
                                        .value("id").toInt();
    record.setValue(record.indexOf("schedule_id"), QVariant(scheduleId));
}
