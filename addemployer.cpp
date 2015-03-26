#include "addemployer.h"
#include "ui_addemployer.h"
#include "mainwindow.h"
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
    tableName = "employer";

    ui->gender->insertItem(0, "Ա");
    ui->gender->insertItem(1, "Ի");

    ui->familyStatus->insertItem(0, "Այրի");
    ui->familyStatus->insertItem(1, "Ամուրի");

    populateLivingAddresses();
    populateRegisterAddresses();
    populateDepartments();
    populatePositions();
    populateSchedules();

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(create()));
}

addEmployer::~addEmployer()
{
    delete ui;
}

void addEmployer::subConnections()
{
    MainWindow *mainWindow = dynamic_cast<MainWindow*>(this->parent());
    connect(mainWindow->addItemDialog["address"], SIGNAL(ready(int)), this, SLOT(populateLivingAddresses(int)));
    connect(mainWindow->addItemDialog["address"], SIGNAL(ready(int)), this, SLOT(populateRegisterAddresses(int)));
    connect(mainWindow->addItemDialog["department"], SIGNAL(ready(int)), this, SLOT(populateDepartments(int)));
    connect(mainWindow->addItemDialog["position"], SIGNAL(ready(int)), this, SLOT(populatePositions(int)));
    connect(mainWindow->addItemDialog["schedule"], SIGNAL(ready(int)), this, SLOT(populateSchedules(int)));
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
    ui->registerAddress->setCurrentIndex(comboIndexAddressId.key(record.value("register_address_id").toInt()));
    ui->livingAddress->setCurrentIndex(comboIndexAddressId.key(record.value("living_address_id").toInt()));
    ui->department->setCurrentIndex(comboIndexDepartmentId.key(record.value("department_id").toInt()));
    ui->position->setCurrentIndex(comboIndexPositionId.key(record.value("position_id").toInt()));
    ui->schedule->setCurrentIndex(comboIndexScheduleId.key(record.value("schedule_id").toInt()));
}

/**
 * @brief addEmployer::claer
 */
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

/**
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

//===================================================================
//==================== Populating combo boxes =======================
//===================================================================

/**
 * @brief addEmployer::populateLivingAddresses
 * @param livingAddressId
 */
void addEmployer::populateLivingAddresses(int livingAddressId)
{
    QSqlTableModel *addressModel = new QSqlTableModel(this, db);
    addressModel->setTable("address");
    if (livingAddressId != 0) {
        model.setFilter(IdField + " = "+ QString::number(livingAddressId));
        addressModel->select();

        if (addressModel->rowCount() == 1) {
            comboIndexAddressId[i] = addressModel->record(0).value("id").toInt();

            ui->livingAddress->addItem(addressModel->record(0).value("street").toString() +
                                  " " + addressModel->record(0).value("h_number").toString());

            if (ui->livingAddress->currentIndex() == -1) {
                ui->livingAddress->setCurrentIndex(i);
            }
        }
    }
    else
    {
        addressModel->select();

        for (int i = 0; i < addressModel->rowCount(); i++) {
            comboIndexAddressId[i] = addressModel->record(i).value("id").toInt();

            ui->livingAddress->addItem(addressModel->record(i).value("street").toString() +
                                  " " + addressModel->record(i).value("h_number").toString());
        }
    }
}

/**
 * @brief addEmployer::populateRegisterAddresses
 * @param registesrAddressId
 */
void addEmployer::populateRegisterAddresses(int registesrAddressId)
{
    QSqlTableModel *addressModel = new QSqlTableModel(this, db);
    addressModel->setTable("address");
    addressModel->select();

    for (int i = 0; i < addressModel->rowCount(); i++) {
        comboIndexAddressId[i] = addressModel->record(i).value("id").toInt();

        ui->registerAddress->addItem(addressModel->record(i).value("street").toString() +
                              " " + addressModel->record(i).value("h_number").toString());

        //==============================================================================================
        if (comboIndexAddressId[i] == registesrAddressId && ui->registerAddress->currentIndex() == -1){
            ui->registerAddress->setCurrentIndex(i);
        }
        //==============================================================================================
    }
}

/**
 * @brief addEmployer::populateDepartments
 * @param departmentId
 */
void addEmployer::populateDepartments(int departmentId)
{
    QSqlTableModel *departmentModel = new QSqlTableModel(this, db);
    departmentModel->setTable("department");
    departmentModel->select();

    for (int i = 0; i < departmentModel->rowCount(); i++) {
        comboIndexDepartmentId[i] = departmentModel->record(i).value("id").toInt();
        ui->department->addItem(departmentModel->record(i).value("name").toString());

        //==============================================================================================
        if (comboIndexDepartmentId[i] == departmentId && ui->department->currentIndex() == -1) {
            ui->department->setCurrentIndex(i);
        }
        //==============================================================================================
    }
}

/**
 * @brief addEmployer::populatePositions
 * @param positionId
 */
void addEmployer::populatePositions(int positionId)
{
    QSqlTableModel *positionModel = new QSqlTableModel(this, db);
    positionModel->setTable("position");
    positionModel->select();

    for (int i = 0; i < positionModel->rowCount(); i++) {
        comboIndexPositionId[i] = positionModel->record(i).value("id").toInt();
        ui->position->addItem(positionModel->record(i).value("name").toString());

        //==============================================================================================
        if (comboIndexPositionId[i] == positionId && ui->position->currentIndex() == -1) {
            ui->position->setCurrentIndex(i);
        }
        //==============================================================================================
    }
}

/**
 * @brief addEmployer::populateSchedules
 * @param scheduleId
 */
void addEmployer::populateSchedules(int scheduleId)
{
    QSqlTableModel *scheduleModel = new QSqlTableModel(this, db);
    scheduleModel->setTable("schedule");
    scheduleModel->select();

    for (int i = 0; i < scheduleModel->rowCount(); i++) {
        comboIndexScheduleId[i] = scheduleModel->record(i).value("id").toInt();
        ui->schedule->addItem(scheduleModel->record(i).value("standart_in_time").toString());

        //===================================================================================
        if (comboIndexScheduleId[i] == scheduleId && ui->schedule->currentIndex() == -1) {
            ui->schedule->setCurrentIndex(i);
        }
        //===================================================================================
    }
}
