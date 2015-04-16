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

    ui->managers->setModel(Employer::create(tableModel->database())->getModel());
    ui->schedule->setModel(Schedule::create(tableModel->database())->getModel());


    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}

addDepartment::~addDepartment()
{
    delete ui;
}

void addDepartment::init(QSqlRecord &record)
{
    ui->dep_name->setText(record.value("name").toString());
    ui->managers->setCurrentIndex(comboIndexManagerId.key(record.value("manager_id").toInt()));
    ui->schedule->setCurrentIndex(comboIndexScheduleId.key(record.value("schedule_id").toInt()));
}

/**
 * @brief addDepartment::clear
 */
void addDepartment::clear() {
    ui->dep_name->setText("");
    ui->managers->setCurrentIndex(0);
    ui->schedule->setCurrentIndex(0);
}

void addDepartment::populateData(QSqlRecord &record)
{
    record.setValue(record.indexOf("name"), QVariant(ui->dep_name->text()));

    if (comboIndexManagerId[ui->managers->currentIndex()] != 0) {
        record.setValue(record.indexOf("manager_id"), QVariant(comboIndexManagerId[ui->managers->currentIndex()]));
    }

    if (comboIndexScheduleId[ui->schedule->currentIndex()] != 0) {
        record.setValue(record.indexOf("schedule_id"), QVariant(comboIndexScheduleId[ui->schedule->currentIndex()]));
    }
}
