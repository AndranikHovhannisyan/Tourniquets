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
 * @brief addDialog::addDialog
 * @param tableModel
 * @param parent
 */
addDialog::addDialog(QSqlRelationalTableModel* tableModel, QWidget *parent) :
    QDialog(parent)
{
    model = tableModel;
}

/**
 * @brief addDialog::~addDialog
 */
addDialog::~addDialog() {
}

/**
 * This function is used to get create / edit signals
 *
 * @brief addDialog::editShow
 * @param id
 */
void addDialog::initialize(QModelIndex modelIndex)
{
    this->clear();
    rowNumber = modelIndex.row();
    if (modelIndex.row() != -1) {
        QSqlRecord record = model->record(modelIndex);
        this->init(record);
    }

    this->show();
}

/**
 * @brief addDialog::create
 */
void addDialog::save()
{
    QSqlRecord record = model.record(rowNumber);
    populateData(record);
    model.insertRecord(rowNumber, record);

    emit ready();
}
