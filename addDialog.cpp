#include "addDialog.h"
#include <QSqlRelationalTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
/**
 * @brief addDialog::addDialog
 * @param db
 * @param parent
 */
addDialog::addDialog(QSqlDatabase db, QWidget *parent) :
    QDialog(parent)
{
    this->db = db;
    this->id = 0;
    this->tableName = "";
    this->IdField = "id";
}

/**
 * @brief addDialog::~addDialog
 */
addDialog::~addDialog() {
}

/**
 * @brief addDialog::editShow
 * @param id
 */
void addDialog::editShow(int id) {
    this->id = id;
    this->initialize();
    this->show();
}

/**
 * @brief addDialog::create
 */
void addDialog::create()
{
    int insertedId = id;
    QSqlRecord record;
    QSqlRelationalTableModel model(this, db);
    model.setTable(tableName);
    model.select();

    if (id == 0) {
        record = model.record();
        populateData(record);
        model.insertRecord(-1, record);
        insertedId = model.query().lastInsertId().toInt();
    }
    else {
        model.setFilter(IdField + " = "+ QString::number(id));
        model.select();
        record = model.record(0);
        populateData(record);
        model.setRecord(0, record);
    }

    emit ready(insertedId);
}

/**
 * @brief addDialog::initialize
 */
void addDialog::initialize()
{
    if (id != 0) {

        QSqlTableModel model(this, db);
        model.setTable(tableName);
        model.setFilter(IdField + " = "+ QString::number(id));
        model.select();

        if (model.rowCount() == 1) {
            QSqlRecord record = model.record(0);
            init(record);
        }
        else {
            this->claer();
        }
    }
    else {
        this->claer();
    }
}

/**
 * @brief addDialog::subConnections
 */
void addDialog::subConnections() {

}
