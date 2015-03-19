#include "addemployer.h"
#include "ui_addemployer.h"
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDebug>


addEmployer::addEmployer(QSqlDatabase db, QWidget *parent) :
    addDialog(db, parent),
    ui(new Ui::addEmployer)
{
    ui->setupUi(this);
    this->setWindowTitle("Ավելացնել աշխատակից");

    ui->gender->insertItem(0, "Ա");
    ui->gender->insertItem(1, "Ի");

    ui->familyStatus->insertItem(0, "Այրի");
    ui->familyStatus->insertItem(1, "Ամուրի");


    //================================ Insert addresses ================================
    QSqlTableModel *addressModel = new QSqlTableModel(this, db);
    addressModel->setTable("address");
    addressModel->select();

    for (int i = 0; i < addressModel->rowCount(); i++) {
        comboIndexAddressId[i] = addressModel->record(i).value("id").toInt();

        ui->livingAddress->addItem(addressModel->record(i).value("street").toString() +
                              " " + addressModel->record(i).value("h_number").toString());

        ui->registerAddress->addItem(addressModel->record(i).value("street").toString() +
                              " " + addressModel->record(i).value("h_number").toString());
    }
    //============================== End address insertion ==============================

    //================================ Insert department ================================
    QSqlTableModel *departmentModel = new QSqlTableModel(this, db);
    departmentModel->setTable("department");
    departmentModel->select();

    for (int i = 0; i < departmentModel->rowCount(); i++) {
        comboIndexDepartmentId[i] = departmentModel->record(i).value("id").toInt();
        ui->department->addItem(departmentModel->record(i).value("name").toString());
    }
    //============================== End department insertion ===========================

    //================================== Insert position ================================
    QSqlTableModel *positionModel = new QSqlTableModel(this, db);
    positionModel->setTable("position");
    positionModel->select();

    for (int i = 0; i < positionModel->rowCount(); i++) {
        comboIndexPositionId[i] = positionModel->record(i).value("id").toInt();
        ui->position->addItem(positionModel->record(i).value("name").toString());
    }
    //================================ End position insertion ===========================

    //================================== Insert schedule ================================
    QSqlTableModel *scheduleModel = new QSqlTableModel(this, db);
    scheduleModel->setTable("schedule");
    scheduleModel->select();

    for (int i = 0; i < scheduleModel->rowCount(); i++) {
        comboIndexScheduleId[i] = scheduleModel->record(i).value("id").toInt();
        ui->schedule->addItem(scheduleModel->record(i).value("standart_in_time").toString());
    }
    //================================ End schedule insertion ===========================

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(createEmployer()));


}

addEmployer::~addEmployer()
{
    delete ui;
}

void addEmployer::createEmployer()
{
//    QSqlRelationalTableModel model(this, db);
//    model.setTable("employer");
//    model.select();

//    if (id == 0) {
//        QSqlRecord record = model.record();

//        record.setValue(1, QVariant(ui->employerId->text()));
//        record.setValue(1, QVariant(comboIndexEmployerId[ui->employer->currentIndex()]));
//        record.setValue(2, QVariant(ui->idType->currentIndex()));

//        model.insertRecord(-1, record);

//        qDebug() << model.lastError();
//    }
//    else {
//        model.setFilter("emp_number = "+ QString::number(id));
//        model.select();
//        QSqlRecord record = model.record(0);
//        record.setValue(0, QVariant(ui->employerId->text()));
//        record.setValue(1, QVariant(comboIndexEmployerId[ui->employer->currentIndex()]));
//        record.setValue(2, QVariant(ui->idType->currentIndex()));
//        model.setRecord(0, record);
//    }

//    emit ready();
}

void addEmployer::init() {
    qDebug() << "id =" << id;
}

void addEmployer::claer() {

}
