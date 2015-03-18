#include "addemployerid.h"
#include "ui_addemployerid.h"
#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QDebug>


addEmployerId::addEmployerId(QSqlDatabase db, QWidget *parent) :
    addDialog(db, parent),
    ui(new Ui::addEmployerId)
{
    ui->setupUi(this);
    this->setWindowTitle("Ավելացնել աշխատակցի իդենտիֆիկատոր");
    types["Քարտ"] = 0;
    types["Մատնահետք"] = 1;

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(createEmployerId()));

    QStringList strList;
    strList << "Քարտ" << "Մատնահետք";
    ui->idType->addItems(strList);


    employerModel = new QSqlTableModel(this, db);
    employerModel->setTable("employer");
    employerModel->select();

    for (int i = 0; i < employerModel->rowCount(); i++) {
        ui->employer->insertItem(employerModel->record(i).value("id").toInt(),
                                 employerModel->record(i).value("firstname").toString());
    }
}

addEmployerId::~addEmployerId()
{
    delete ui;
}

#include <QSqlError>

void addEmployerId::createEmployerId()
{
    QSqlRelationalTableModel model(this, db);
    model.setTable("employer_ids");
    model.select();


    if (id == 0) {

        QSqlRecord record = model.record();
        record.setValue(0, QVariant(ui->employerId->text()));
        record.setValue(1, QVariant(ui->employer->currentIndex()));
        record.setValue(2, QVariant(types[ui->idType->currentText()]));
        model.insertRecord(-1, record);

        qDebug() << model.lastError();
    }
//    else {
//        model.setFilter("id = "+ QString::number(id));
//        model.select();
//        QSqlRecord record = model.record(0);
//        record.setValue(1, QVariant(ui->country->text()));
//        record.setValue(2, QVariant(ui->city->text()));
//        record.setValue(3, QVariant(ui->street->text()));
//        record.setValue(4, QVariant(ui->hNumber->text()));
//        model.setRecord(0, record);
//    }

    emit ready();
}

void addEmployerId::init()
{
    qDebug() << "id =" << id;
}

void addEmployerId::claer() {

}
