#include "adddepartment.h"
#include "ui_adddepartment.h"
#include <QSqlTableModel>
#include <QDebug>

addDepartment::addDepartment(QSqlDatabase db, QWidget *parent) :
    addDialog(db, parent),
    ui(new Ui::addDepartment)
{
    ui->setupUi(this);
    this->setWindowTitle("add department");
    tableName = "department";

    QSqlTableModel *employerModel = new QSqlTableModel(this, db);
    employerModel->setTable("employer");
    employerModel->select();

    for (int i = 0; i < employerModel->rowCount(); i++) {
        comboIndexEmployerId[i] = employerModel->record(i).value("id").toInt();
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

void addDepartment::init() {
    qDebug() << "id =" << id;
}

void addDepartment::claer() {

}

void addDepartment::populateData(QSqlRecord &rec) {

}
