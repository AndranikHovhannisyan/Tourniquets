#include "addphone.h"
#include "ui_addphone.h"
#include <QSqlTableModel>
#include <QDebug>

addPhone::addPhone(QSqlDatabase db, QWidget *parent) :
    addDialog(db, parent),
    ui(new Ui::addPhone)
{
    ui->setupUi(this);
    this->setWindowTitle("Ավելացնել հեռախոսահամար");
    tableName = "phone_number";
    IdField = "number";

    QSqlTableModel *employerModel = new QSqlTableModel(this, db);
    employerModel->setTable("employer");
    employerModel->select();

    for (int i = 0; i < employerModel->rowCount(); i++) {
        comboIndexEmployerId[i] = employerModel->record(i).value("id").toInt();
        ui->employer->addItem(employerModel->record(i).value("firstname").toString());
    }

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(create()));

}

addPhone::~addPhone()
{
    delete ui;
}

void addPhone::init(QSqlRecord &record) {
    ui->employer->setCurrentIndex(comboIndexEmployerId.key(record.value("employeer_id").toInt()));
    ui->number->setText(record.value("number").toString());
}

void addPhone::claer() {
    ui->number->setText("");
    ui->employer->setCurrentIndex(0);
}

void addPhone::populateData(QSqlRecord &record) {
    record.setValue(record.indexOf("number"), QVariant(ui->number->text()));

    if (comboIndexEmployerId[ui->employer->currentIndex()] != 0) {
        record.setValue(record.indexOf("employeer_id"), QVariant(comboIndexEmployerId[ui->employer->currentIndex()]));
    }
}
