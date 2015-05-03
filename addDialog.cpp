#include "addDialog.h"
#include <QSqlRelationalTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

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
    initByRowNumber(modelIndex.row());
}

/**
 * @brief initByRowNumber
 * @param row
 */
void addDialog::initByRowNumber(int row)
{
    this->clear();
    rowNumber = row;
    if (row != -1) {
        QSqlRecord record = model->record(row);
        this->init(record);
    }

    this->show();
}

/**
 * @brief addDialog::create
 */
void addDialog::save()
{
    QSqlRecord record = model->record(rowNumber);
    populateData(record);

    if (rowNumber < 0) {
        model->insertRecord(rowNumber, record);
        rowNumber = model->rowCount() - 1;
    }
    else {
        model->setRecord(rowNumber, record);
    }

    model->select();
    emit ready(rowNumber);
}
