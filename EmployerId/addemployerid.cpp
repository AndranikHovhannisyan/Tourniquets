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

    ui->idType->insertItem(0, "Քարտ");
    ui->idType->insertItem(1, "Մատնահետք");

//    QSqlTableModel *employerModel = new QSqlTableModel(this, db);
//    employerModel->setTable("employer");
//    employerModel->select();

//    for (int i = 0; i < employerModel->rowCount(); i++) {
//        comboIndexEmployerId[i] = employerModel->record(i).value("id").toInt();
//        ui->employer->addItem(employerModel->record(i).value("firstname").toString());
//    }

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(create()));
}


addEmployerId::~addEmployerId()
{
    delete ui;
}


void addEmployerId::init(QSqlRecord &record)
{
    ui->employer->setCurrentIndex(comboIndexEmployerId.key(record.value("employeer_id").toInt()));
    ui->employerId->setText(record.value("emp_number").toString());
    ui->idType->setCurrentIndex(record.value("id_type").toInt());
}


void addEmployerId::clear() {
    ui->employerId->setText("");
    ui->employer->setCurrentIndex(0);
    ui->idType->setCurrentIndex(0);
}

void addEmployerId::populateData(QSqlRecord &record) {
    record.setValue(record.indexOf("emp_number"), QVariant(ui->employerId->text()));
    record.setValue(record.indexOf("id_type"), QVariant(ui->idType->currentIndex()));

    if (comboIndexEmployerId[ui->employer->currentIndex()] != 0) {
        record.setValue(record.indexOf("employeer_id"), QVariant(comboIndexEmployerId[ui->employer->currentIndex()]));
    }
}
