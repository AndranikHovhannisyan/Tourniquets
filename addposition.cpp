#include "addposition.h"
#include "ui_addposition.h"
#include <QSqlTableModel>

addPosition::addPosition(QSqlDatabase db, QWidget *parent) :
    QDialog(parent),
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
