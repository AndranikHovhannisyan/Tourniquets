#include "addDialog.h"
#include <QSqlRelationalTableModel>
#include <QSqlError>
#include <QDebug>


addDialog::addDialog(QSqlDatabase db, QWidget *parent) :
    QDialog(parent)
{
    this->db = db;
    this->id = 0;
    this->tableName = "";
    this->IdField = "id";
}

addDialog::~addDialog() {
}

void addDialog::editShow(int id) {
    this->id = id;
    this->init();
    this->show();
}

void addDialog::create()
{
    QSqlRelationalTableModel model(this, db);
    model.setTable(tableName);
    model.select();

    if (id == 0) {
        QSqlRecord record = model.record();
        populateData(record);
        model.insertRecord(-1, record);

        qDebug() << model.lastError();
    }
    else {
        model.setFilter(IdField + " = "+ QString::number(id));
        model.select();
        QSqlRecord record = model.record(0);
        populateData(record);
        model.setRecord(0, record);
    }

    emit ready();
}
