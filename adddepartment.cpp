#include "adddepartment.h"
#include "ui_adddepartment.h"
#include <QSqlTableModel>

addDepartment::addDepartment(QSqlDatabase db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDepartment)
{
    ui->setupUi(this);

    QSqlTableModel *managerModel = new QSqlTableModel(this, db);
    managerModel->setTable("employer");
    managerModel->select();
    ui->managers->setModel(managerModel);

    QSqlTableModel *scheduleModel = new QSqlTableModel(this, db);
    scheduleModel->setTable("schedule");
    scheduleModel->select();
    ui->schedule->setModel(scheduleModel);
    ui->schedule->setModelColumn(1);
}

addDepartment::~addDepartment()
{
    delete ui;
}
