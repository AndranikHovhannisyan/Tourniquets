#include "addemployerid.h"
#include "ui_addemployerid.h"
#include <QSqlRelationalTableModel>
#include <QSqlRecord>

#include <QDebug>
#include <QSqlError>

addEmployerId::addEmployerId(QSqlRelationalTableModel *tableModel, QWidget *parent) :
    addDialog(tableModel, parent),
    ui(new Ui::addEmployerId)
{
    ui->setupUi(this);
    this->setWindowTitle("Ավելացնել աշխատակցի իդենտիֆիկատոր");

    idTypes[0] = "Քարտ";
    idTypes[1] = "Մատնահետք";

    ui->idType->insertItem(0, idTypes[0]);
    ui->idType->insertItem(1, idTypes[1]);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}


addEmployerId::~addEmployerId()
{
    delete ui;
}


void addEmployerId::init(QSqlRecord &record)
{
    ui->employerId->setText(record.value("emp_number").toString());
    ui->idType->setCurrentIndex(record.value("id_type").toInt());
}


void addEmployerId::clear() {
    ui->employerId->setText("");
    ui->idType->setCurrentIndex(0);
}

void addEmployerId::populateData(QSqlRecord &record) {
    record.setValue(record.indexOf("emp_number"), QVariant(ui->employerId->text()));
    record.setValue(record.indexOf("id_type"), QVariant(ui->idType->currentIndex()));
}
