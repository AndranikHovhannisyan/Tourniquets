#include "addemployerid.h"
#include "ui_addemployerid.h"
#include <QSqlRelationalTableModel>
#include <QSqlRecord>

#include <QDebug>
#include <QSqlError>

addEmployerId::addEmployerId(QSqlDatabase db, QWidget *parent) :
    addDialog(db, parent),
    ui(new Ui::addEmployerId)
{
    ui->setupUi(this);
    this->setWindowTitle("Ավելացնել աշխատակցի իդենտիֆիկատոր");

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(createEmployerId()));

    ui->idType->insertItem(0, "Քարտ");
    ui->idType->insertItem(1, "Մատնահետք");


    employerModel = new QSqlTableModel(this, db);
    employerModel->setTable("employer");
    employerModel->select();

    for (int i = 0; i < employerModel->rowCount(); i++) {
        comboIndexEmployerId[i] = employerModel->record(i).value("id").toInt();
        ui->employer->addItem(employerModel->record(i).value("firstname").toString());
    }
}

addEmployerId::~addEmployerId()
{
    delete ui;
}

void addEmployerId::createEmployerId()
{
    QSqlRelationalTableModel model(this, db);
    model.setTable("employer_ids");
    model.select();

    if (id == 0) {
        QSqlRecord record = model.record();
        record.setValue(0, QVariant(ui->employerId->text()));
        record.setValue(1, QVariant(comboIndexEmployerId[ui->employer->currentIndex()]));
        record.setValue(2, QVariant(ui->idType->currentIndex()));
        model.insertRecord(-1, record);

        qDebug() << model.lastError();
    }
    else {
        model.setFilter("emp_number = "+ QString::number(id));
        model.select();
        QSqlRecord record = model.record(0);
        record.setValue(0, QVariant(ui->employerId->text()));
        record.setValue(1, QVariant(comboIndexEmployerId[ui->employer->currentIndex()]));
        record.setValue(2, QVariant(ui->idType->currentIndex()));
        model.setRecord(0, record);
    }

    emit ready();
}

void addEmployerId::init()
{
    if (id != 0) {

        QSqlTableModel model(this, db);
        model.setTable("employer_ids");
        model.setFilter("emp_number = "+ QString::number(id));
        model.select();

        if (model.rowCount() == 1) {
            ui->employer->setCurrentIndex(comboIndexEmployerId.key(model.record(0).value("employeer_id").toInt()));
            ui->employerId->setText(model.record(0).value("emp_number").toString());
            ui->idType->setCurrentIndex(model.record(0).value("id_type").toInt());
        }
        else {
            this->claer();
        }
    }
    else {
        this->claer();
    }
}

void addEmployerId::claer() {
    ui->employerId->setText("");
    ui->employer->setCurrentIndex(0);
    ui->idType->setCurrentIndex(0);
}
