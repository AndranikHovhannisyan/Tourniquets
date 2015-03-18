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

void addDepartment::init() {
    qDebug() << "id =" << id;
}
