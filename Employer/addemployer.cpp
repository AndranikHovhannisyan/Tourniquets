#include "addemployer.h"
#include "ui_addemployer.h"
#include "mainwindow.h"
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

#include "Address/address.h"
#include "Department/department.h"
#include "Position/position.h"
#include "Schedule/schedule.h"


addEmployer::addEmployer(QSqlRelationalTableModel *tableModel, QWidget *parent) :
    addDialog(tableModel, parent),
    ui(new Ui::addEmployer)
{
    ui->setupUi(this);
    this->setWindowTitle("Ավելացնել աշխատակից");

    ui->gender->insertItem(0, "Ա");
    ui->gender->insertItem(1, "Ի");

    ui->familyStatus->insertItem(0, "Այրի");
    ui->familyStatus->insertItem(1, "Ամուրի");

    ui->registerAddress->setModel(Address::create(model->database())->getModel());
    ui->livingAddress->setModel(Address::create(model->database())->getModel());
    ui->department->setModel(Department::create(model->database())->getModel());
    ui->position->setModel(Position::create(model->database())->getModel());
    ui->schedule->setModel(Schedule::create(model->database())->getModel());

    ui->registerAddress->setModelColumn(3);
    ui->livingAddress->setModelColumn(3);
    ui->department->setModelColumn(1);
    ui->position->setModelColumn(1);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}

addEmployer::~addEmployer()
{
    delete ui;
}

/**
 * @brief addEmployer::init
 * @param record
 */
void addEmployer::init(QSqlRecord &record)
{
    ui->firstname->setText(record.value("firstname").toString());
    ui->lastname->setText(record.value("lastname").toString());
    ui->middlename->setText(record.value("middlename").toString());
    ui->birthdate->setDate(record.value("birth_date").toDate());
    ui->passSeria->setText(record.value("passport_series").toString());
    ui->passNumber->setText(record.value("passport_number").toString());
    ui->givenDate->setDate(record.value("given_date").toDate());
    ui->givenFrom->setText(record.value("given_from").toString());
    ui->gender->setCurrentIndex(record.value("gender").toInt());
    ui->isConscript->setChecked(record.value("is_conscript").toBool());
    ui->familyStatus->setCurrentIndex(record.value("family_status").toInt());
    ui->childrenNumber->setText(record.value("children_num").toString());
    ui->minorNumber->setText(record.value("minor_children_num").toString());



    QSqlRelationalTableModel* addressModel = Address::create(model->database())->getModel();
    int addressCount = addressModel->rowCount();
    int completedCount = 0;
    for(int i = 0; i < addressCount && completedCount != 2; i++) {
        if (addressModel->record(i).value("id").toInt() == record.value("register_address_id").toInt()) {
            ui->registerAddress->setCurrentIndex(i);
            completedCount++;
        }
        if (addressModel->record(i).value("id").toInt() == record.value("living_address_id").toInt()) {
            ui->livingAddress->setCurrentIndex(i);
            completedCount++;
        }
    }


    QSqlRelationalTableModel* departmentModel = Department::create(model->database())->getModel();
    int departmentCount = departmentModel->rowCount();
    for(int i = 0; i < departmentCount; i++) {
        if (departmentModel->record(i).value("id").toInt() == record.value("department_id").toInt()) {
            ui->department->setCurrentIndex(i);
            break;
        }
    }

    QSqlRelationalTableModel* positionModel = Position::create(model->database())->getModel();
    int positionCount = positionModel->rowCount();
    for(int i = 0; i < positionCount; i++) {
        if (positionModel->record(i).value("id").toInt() == record.value("position_id").toInt()) {
            ui->position->setCurrentIndex(i);
            break;
        }
    }

    QSqlRelationalTableModel* scheduleModel = Schedule::create(model->database())->getModel();
    int scheduleCount = scheduleModel->rowCount();
    for(int i = 0; i < scheduleCount; i++) {
        if (scheduleModel->record(i).value("id").toInt() == record.value("schedule_id").toInt()) {
            ui->schedule->setCurrentIndex(i);
            break;
        }
    }
}

/**
 * @brief addEmployer::clear
 */
void addEmployer::clear() {
    ui->firstname->setText("");
    ui->lastname->setText("");
    ui->middlename->setText("");
    ui->birthdate->clear();
    ui->passSeria->setText("");
    ui->passNumber->setText("");
    ui->givenDate->clear();
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

/**
 * This function is used to populate data to the record from widgets
 *
 * @brief addEmployer::populateData
 * @param record
 */
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

    int registerAddressId = Address::create(model->database())
                                        ->getModel()
                                        ->record(ui->registerAddress->currentIndex())
                                        .value("id").toInt();
    record.setValue(record.indexOf("register_address_id"), QVariant(registerAddressId));


    int livingAddressId = Address::create(model->database())
                                        ->getModel()
                                        ->record(ui->livingAddress->currentIndex())
                                        .value("id").toInt();
    record.setValue(record.indexOf("living_address_id"), QVariant(livingAddressId));


    int departmentId = Department::create(model->database())
                                        ->getModel()
                                        ->record(ui->department->currentIndex())
                                        .value("id").toInt();
    record.setValue(record.indexOf("department_id"), QVariant(departmentId));


    int positionId = Position::create(model->database())
                                        ->getModel()
                                        ->record(ui->position->currentIndex())
                                        .value("id").toInt();
    record.setValue(record.indexOf("position_id"), QVariant(positionId));


    int scheduleId = Schedule::create(model->database())
                                        ->getModel()
                                        ->record(ui->schedule->currentIndex())
                                        .value("id").toInt();
    record.setValue(record.indexOf("schedule_id"), QVariant(scheduleId));
}
