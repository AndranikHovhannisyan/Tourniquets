#include "addemployer.h"
#include "ui_addemployer.h"
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QSqlError>
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
    QSqlRelationalTableModel model(this, db);
    model.setTable("employer");
    model.select();

    if (id == 0) {
        QSqlRecord record = model.record();
        populateData(record);
        model.insertRecord(-1, record);

        qDebug() << model.lastError();
    }
    else {
        model.setFilter("id = "+ QString::number(id));
        model.select();
        QSqlRecord record = model.record(0);
        populateData(record);
        model.setRecord(0, record);
    }

    emit ready();
}

void addEmployer::init() {

    if (id != 0) {

        QSqlTableModel model(this, db);
        model.setTable("employer");
        model.setFilter("id = "+ QString::number(id));
        model.select();

        if (model.rowCount() == 1) {

            ui->firstname->setText(model.record(0).value("firstname").toString());
            ui->lastname->setText(model.record(0).value("lastname").toString());
            ui->middlename->setText(model.record(0).value("middlename").toString());
            ui->birthdate->setDate(model.record(0).value("birth_date").toDate());
            ui->passSeria->setText(model.record(0).value("passport_series").toString());
            ui->passNumber->setText(model.record(0).value("passport_number").toString());
            ui->givenDate->setDate(model.record(0).value("given_date").toDate());
            ui->givenFrom->setText(model.record(0).value("given_from").toString());
            ui->gender->setCurrentIndex(model.record(0).value("gender").toInt());
            ui->isConscript->setChecked(model.record(0).value("is_conscript").toBool());
            ui->familyStatus->setCurrentIndex(model.record(0).value("family_status").toInt());
            ui->childrenNumber->setText(model.record(0).value("children_num").toString());
            ui->minorNumber->setText(model.record(0).value("minor_children_num").toString());
            ui->registerAddress->setCurrentIndex(comboIndexAddressId.key(model.record(0).value("register_address_id").toInt()));
            ui->livingAddress->setCurrentIndex(comboIndexAddressId.key(model.record(0).value("living_address_id").toInt()));
            ui->department->setCurrentIndex(comboIndexDepartmentId.key(model.record(0).value("department_id").toInt()));
            ui->position->setCurrentIndex(comboIndexPositionId.key(model.record(0).value("position_id").toInt()));
            ui->schedule->setCurrentIndex(comboIndexScheduleId.key(model.record(0).value("schedule_id").toInt()));
        }
        else {
            this->claer();
        }
    }
    else {
        this->claer();
    }
}

void addEmployer::claer() {
    ui->firstname->setText("");
    ui->lastname->setText("");
    ui->middlename->setText("");
    ui->birthdate->setDate(QDate());
    ui->passSeria->setText("");
    ui->passNumber->setText("");
    ui->givenDate->setDate(QDate());
    ui->givenFrom->setText("");
    ui->gender->setCurrentIndex(0);
    ui->isConscript->setChecked(false);
    ui->familyStatus->setCurrentIndex(0);
    ui->childrenNumber->setText("");
    ui->minorNumber->setText("");
    ui->registerAddress->setCurrentIndex(0);
    ui->livingAddress->setCurrentIndex(0);
    ui->department->setCurrentIndex(0);
    ui->position->setCurrentIndex(0);
    ui->schedule->setCurrentIndex(0);
}

void addEmployer::populateData(QSqlRecord &record)
{
    record.setValue(record.indexOf("firstname"), QVariant(ui->firstname->text()));
    record.setValue(record.indexOf("lastname"), QVariant(ui->lastname->text()));
    record.setValue(record.indexOf("middlename"), QVariant(ui->middlename->text()));
    record.setValue(record.indexOf("birth_date"), QVariant(ui->birthdate->date()));
    record.setValue(record.indexOf("passport_series"), QVariant(ui->passSeria->text()));
    record.setValue(record.indexOf("passport_number"), QVariant(ui->passNumber->text()));
    record.setValue(record.indexOf("given_date"), QVariant(ui->givenDate->date()));
    record.setValue(record.indexOf("given_from"), QVariant(ui->givenFrom->text()));
    record.setValue(record.indexOf("gender"), QVariant(ui->gender->currentIndex()));
    record.setValue(record.indexOf("is_conscript"), QVariant(ui->isConscript->isChecked()));
    record.setValue(record.indexOf("family_status"), QVariant(ui->familyStatus->currentIndex()));
    record.setValue(record.indexOf("children_num"), QVariant(ui->childrenNumber->text()));
    record.setValue(record.indexOf("minor_children_num"), QVariant(ui->minorNumber->text()));

    if (comboIndexAddressId[ui->registerAddress->currentIndex()] != 0) {
        record.setValue(record.indexOf("register_address_id"), QVariant(comboIndexAddressId[ui->registerAddress->currentIndex()]));
    }

    if (comboIndexAddressId[ui->livingAddress->currentIndex()] != 0) {
        record.setValue(record.indexOf("living_address_id"), QVariant(comboIndexAddressId[ui->livingAddress->currentIndex()]));
    }

    if (comboIndexDepartmentId[ui->department->currentIndex()] != 0) {
    record.setValue(record.indexOf("department_id"), QVariant(comboIndexDepartmentId[ui->department->currentIndex()]));
    }

    if (comboIndexPositionId[ui->position->currentIndex()] != 0) {
        record.setValue(record.indexOf("position_id"), QVariant(comboIndexPositionId[ui->position->currentIndex()]));
    }

    if (comboIndexScheduleId[ui->schedule->currentIndex()] != 0) {
        record.setValue(record.indexOf("schedule_id"), QVariant(comboIndexScheduleId[ui->schedule->currentIndex()]));
    }
}
