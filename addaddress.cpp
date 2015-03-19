#include "addaddress.h"
#include "ui_addaddress.h"
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>

#include <QDebug>

addAddress::addAddress(QSqlDatabase db, QWidget *parent) :
    addDialog(db, parent),
    ui(new Ui::addAddress)
{
    ui->setupUi(this);
    this->setWindowTitle("Ավելացնել հասցե");
    tableName = "address";

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(create()));
}

addAddress::~addAddress()
{
    delete ui;
}

void addAddress::init(QSqlRecord &record)
{
    ui->country->setText(record.value("country").toString());
    ui->city->setText(record.value("city").toString());
    ui->street->setText(record.value("street").toString());
    ui->hNumber->setText(record.value("h_number").toString());
}


void addAddress::claer() {
    ui->country->setText("");
    ui->city->setText("");
    ui->street->setText("");
    ui->hNumber->setText("");
}

void addAddress::populateData(QSqlRecord &record) {
    record.setValue(record.indexOf("country"), QVariant(ui->country->text()));
    record.setValue(record.indexOf("city"), QVariant(ui->city->text()));
    record.setValue(record.indexOf("street"), QVariant(ui->street->text()));
    record.setValue(record.indexOf("h_number"), QVariant(ui->hNumber->text()));
}
