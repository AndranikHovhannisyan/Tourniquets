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

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(createAddress()));
}

addAddress::~addAddress()
{
    delete ui;
}

void addAddress::createAddress()
{
    QSqlTableModel model(this, db);
    model.setTable("address");
    QSqlRecord record = model.record();
    record.setValue(1, QVariant(ui->country->text()));
    record.setValue(2, QVariant(ui->city->text()));
    record.setValue(3, QVariant(ui->street->text()));
    record.setValue(4, QVariant(ui->hNumber->text()));
    model.insertRecord(-1, record);

    emit ready();
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
