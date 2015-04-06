#include "addaddress.h"
#include "ui_addaddress.h"
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>

#include <QDebug>

/**
 * @brief addAddress::addAddress
 * @param model
 * @param parent
 */
addAddress::addAddress(QSqlRelationalTableModel *tableModel, QWidget *parent) :
    addDialog(tableModel, parent),
    ui(new Ui::addAddress)
{
    ui->setupUi(this);
    this->setWindowTitle("Ավելացնել հասցե");
    tableName = "address";

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}

/**
 * @brief addAddress::~addAddress
 */
addAddress::~addAddress()
{
    delete ui;
}

/**
 * @brief addAddress::init
 * @param record
 */
void addAddress::init(QSqlRecord &record)
{
    ui->country->setText(record.value("country").toString());
    ui->city->setText(record.value("city").toString());
    ui->street->setText(record.value("street").toString());
    ui->hNumber->setText(record.value("h_number").toString());
}

/**
 * @brief addAddress::clear
 */
void addAddress::clear() {
    ui->country->setText("");
    ui->city->setText("");
    ui->street->setText("");
    ui->hNumber->setText("");
}

/**
 * @brief addAddress::populateData
 * @param record
 */
void addAddress::populateData(QSqlRecord &record) {
    record.setValue(record.indexOf("country"), QVariant(ui->country->text()));
    record.setValue(record.indexOf("city"), QVariant(ui->city->text()));
    record.setValue(record.indexOf("street"), QVariant(ui->street->text()));
    record.setValue(record.indexOf("h_number"), QVariant(ui->hNumber->text()));
}
