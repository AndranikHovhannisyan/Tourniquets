#include "addemployerid.h"
#include "ui_addemployerid.h"
#include <QSqlTableModel>
#include <QDebug>

addEmployerId::addEmployerId(QSqlDatabase db, QWidget *parent) :
    addDialog(db, parent),
    ui(new Ui::addEmployerId)
{
    ui->setupUi(this);
    this->setWindowTitle("add employer id");

    QSqlTableModel *employerModel = new QSqlTableModel(this, db);
    employerModel->setTable("employer");
    employerModel->select();
    ui->employer->setModel(employerModel);
}

addEmployerId::~addEmployerId()
{
    delete ui;
}

void addEmployerId::init() {
    qDebug() << "id =" << id;
}
