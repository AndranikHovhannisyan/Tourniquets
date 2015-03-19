#include "adddepartment.h"
#include "ui_adddepartment.h"
#include <QSqlTableModel>
#include <QDebug>

addDepartment::addDepartment(QSqlDatabase db, QWidget *parent) :
    addDialog(db, parent),
    ui(new Ui::addDepartment)
{
    ui->setupUi(this);
    this->setWindowTitle("Ավելացնել բաժին");
    tableName = "department";

    QSqlTableModel *employerModel = new QSqlTableModel(this, db);
    employerModel->setTable("employer");
    employerModel->select();

    for (int i = 0; i < employerModel->rowCount(); i++) {
        comboIndexManagerId[i] = employerModel->record(i).value("id").toInt();
        ui->managers->addItem(employerModel->record(i).value("firstname").toString());
    }

    QSqlTableModel *scheduleModel = new QSqlTableModel(this, db);
    scheduleModel->setTable("schedule");
    scheduleModel->select();

    for (int i = 0; i < scheduleModel->rowCount(); i++) {
        comboIndexScheduleId[i] = scheduleModel->record(i).value("id").toInt();
        ui->schedule->addItem(scheduleModel->record(i).value("standart_in_time").toString());
    }

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(create()));
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

void addDepartment::claer() {
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
