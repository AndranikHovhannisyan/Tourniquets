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

void addAddress::init()
{
    if (id != 0) {

        QSqlTableModel model(this, db);
        model.setTable("address");
        model.setFilter("id = "+ QString::number(id));
        model.select();

        if (model.rowCount() == 1) {
            ui->country->setText(model.record(0).value("country").toString());
            ui->city->setText(model.record(0).value("city").toString());
            ui->street->setText( model.record(0).value("street").toString());
            ui->hNumber->setText(model.record(0).value("h_number").toString());
        }
        else {
            this->claer();
        }
    }
    else {
        this->claer();
    }
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
