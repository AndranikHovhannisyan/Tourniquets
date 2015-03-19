#include "addtourniquet.h"
#include "ui_addtourniquet.h"
#include <QDebug>

addTourniquet::addTourniquet(QSqlDatabase db, QWidget *parent) :
    addDialog(db, parent),
    ui(new Ui::addTourniquet)
{
    ui->setupUi(this);
    ui->type->addItem("In");
    ui->type->addItem("Out");
    this->setWindowTitle("add tourniquet");
}

addTourniquet::~addTourniquet()
{
    delete ui;
}

void addTourniquet::init() {
    qDebug() << "id =" << id;
}

void addTourniquet::claer() {

}

void addTourniquet::populateData(QSqlRecord &rec) {

}
