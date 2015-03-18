#include "addemployer.h"
#include "ui_addemployer.h"
#include <QDebug>

addEmployer::addEmployer(QSqlDatabase db, QWidget *parent) :
    addDialog(db, parent),
    ui(new Ui::addEmployer)
{
    ui->setupUi(this);
}

addEmployer::~addEmployer()
{
    delete ui;
}

void addEmployer::init() {
    qDebug() << "id =" << id;
}

void addEmployer::claer() {

}
