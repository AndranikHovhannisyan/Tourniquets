#include "addposition.h"
#include "ui_addposition.h"
#include <QSqlTableModel>
#include <QDebug>

addPosition::addPosition(QSqlDatabase db, QWidget *parent) :
    addDialog(db, parent),
    ui(new Ui::addPosition)
{
    ui->setupUi(this);
    this->setWindowTitle("add position");

    QSqlTableModel *scheduleModel = new QSqlTableModel(this, db);
    scheduleModel->setTable("schedule");
    scheduleModel->select();
    ui->schedule->setModel(scheduleModel);
}

addPosition::~addPosition()
{
    delete ui;
}

void addPosition::init() {
    qDebug() << "id =" << id;
}

void addPosition::claer() {

}

void addPosition::populateData(QSqlRecord &rec) {

}
