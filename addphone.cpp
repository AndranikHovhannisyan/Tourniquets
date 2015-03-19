#include "addphone.h"
#include "ui_addphone.h"
#include <QDebug>

addPhone::addPhone(QSqlDatabase db, QWidget *parent) :
    addDialog(db, parent),
    ui(new Ui::addPhone)
{
    ui->setupUi(this);
}

addPhone::~addPhone()
{
    delete ui;
}

void addPhone::init(QSqlRecord &) {
    qDebug() << "id =" << id;
}

void addPhone::claer() {

}

void addPhone::populateData(QSqlRecord &rec) {

}
