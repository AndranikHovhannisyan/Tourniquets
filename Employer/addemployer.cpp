#include "addemployer.h"
#include "ui_addemployer.h"
#include "mainwindow.h"
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "Address/address.h"
#include "Department/department.h"
#include "Position/position.h"
#include "Schedule/schedule.h"
#include "Department_Position/department_position.h"
#include "Employer_DepPosition/employer_depposition.h"
#include "Employer/employer.h"
#include "EmployerId/employerid.h"
#include "Employer_EmployerId/employer_employerid.h"


addEmployer::addEmployer(QSqlRelationalTableModel *tableModel, QWidget *parent) :
    addDialog(tableModel, parent),
    ui(new Ui::addEmployer)
{
    departmentPositions = NULL;

    ui->setupUi(this);
    this->setWindowTitle("Ավելացնել աշխատակից");

    ui->gender->insertItem(0, "Ա");
    ui->gender->insertItem(1, "Ի");

    ui->familyStatus->insertItem(0, "Այրի");
    ui->familyStatus->insertItem(1, "Ամուրի");

    ui->registerAddress->setModel(Address::create(model->database())->getModel());
    ui->livingAddress->setModel(Address::create(model->database())->getModel());
    ui->schedule->setModel(Schedule::create(model->database())->getModel());
    ui->employerId->setModel(EmployerId::create(model->database())->getModel());


    ui->department->setModel(Department::create(model->database())->getModel());
    connect(ui->department, SIGNAL(currentIndexChanged(int)), this, SLOT(populateDepartmentPositions(int)));
    connect(this, SIGNAL(ready(int)), this, SLOT(employerDepartmentPositionEmployerIdSave(int)));

    ui->registerAddress->setModelColumn(3);
    ui->livingAddress->setModelColumn(3);
    ui->department->setModelColumn(1);

    //Connect add buttons with add dialogs
    connect(ui->add_living_address,   SIGNAL(clicked()), Address::create(model->database())->getAddDialog(),       SLOT(initialize()));
    connect(ui->add_register_address, SIGNAL(clicked()), Address::create(model->database())->getAddDialog(),       SLOT(initialize()));
    connect(ui->add_department,       SIGNAL(clicked()), Department::create(model->database())->getAddDialog(), SLOT(initialize()));
    connect(ui->add_position,         SIGNAL(clicked()), Position::create(model->database())->getAddDialog(),     SLOT(initialize()));
    connect(ui->add_schedule,         SIGNAL(clicked()), Schedule::create(model->database())->getAddDialog(),     SLOT(initialize()));

    //Connect add buttons with add initAddition
    connect(ui->add_living_address,   SIGNAL(clicked()), this, SLOT(initAddition()));
    connect(ui->add_register_address, SIGNAL(clicked()), this, SLOT(initAddition()));
    connect(ui->add_department,       SIGNAL(clicked()), this, SLOT(initAddition()));
    connect(ui->add_position,         SIGNAL(clicked()), this, SLOT(initAddition()));
    connect(ui->add_schedule,         SIGNAL(clicked()), this, SLOT(initAddition()));

    //Connect add dialogs ready with selectCreated
    connect(Address::create(model->database())->getAddDialog(),       SIGNAL(ready(int)), this, SLOT(selectCreated(int)));
    connect(Department::create(model->database())->getAddDialog(), SIGNAL(ready(int)), this, SLOT(selectCreated(int)));
    connect(Position::create(model->database())->getAddDialog(),     SIGNAL(ready(int)), this, SLOT(selectCreated(int)));
    connect(Schedule::create(model->database())->getAddDialog(),     SIGNAL(ready(int)), this, SLOT(selectCreated(int)));

    //Connect add dialogs rejected with rejectAddition
    connect(Address::create(model->database())->getAddDialog(),       SIGNAL(rejected()), this, SLOT(rejectAddition()));
    connect(Department::create(model->database())->getAddDialog(), SIGNAL(rejected()), this, SLOT(rejectAddition()));
    connect(Position::create(model->database())->getAddDialog(),     SIGNAL(rejected()), this, SLOT(rejectAddition()));
    connect(Schedule::create(model->database())->getAddDialog(),     SIGNAL(rejected()), this, SLOT(rejectAddition()));

    //Populate addInComboMap for combobox selection after addition
    addInComboMap["add_living_address"]   = ui->livingAddress;
    addInComboMap["add_register_address"] = ui->registerAddress;
    addInComboMap["add_department"]       = ui->department;
    addInComboMap["add_position"]         = ui->position;
    addInComboMap["add_schedule"]         = ui->schedule;


    relationComboBox = NULL;
    livingAddress   = -1;
    registerAddress = -1;

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}

addEmployer::~addEmployer()
{
    delete ui;
}

/**
 * @brief addEmployer::populateDepartmentPositions
 */
void addEmployer::populateDepartmentPositions(int departmentRow)
{
    int departmentId = Department::create(model->database())->getModel()->record(departmentRow).value("id").toInt();

    departmentPositions = departmentPositions ? departmentPositions : new QSqlQueryModel;
    departmentPositions->setQuery("SELECT p.id, p.name FROM position as p " \
                                  " JOIN dep_positions as dp ON dp.position_id = p.id AND dp.department_id = "
                                  + QString::number(departmentId));

    ui->position->setModel(departmentPositions);
    ui->position->setModelColumn(1);
}

/**
 * @brief addEmployer::selectCreated
 */
void addEmployer::selectCreated(int rowNumber)
{
    addDialog* add_dialog = dynamic_cast<addDialog*>(sender());
    if (add_dialog != NULL) {
        if (add_dialog->objectName() == "addPosition"){
            //If click add position in add employer window then if will be added to the correspondinf dep_positions table
            int positionId = Position::create(model->database())->getModel()
                                                                ->record(rowNumber)
                                                                .value("id").toInt();

            int departmentId = Department::create(model->database())->getModel()
                                                                ->record(ui->department->currentIndex())
                                                                .value("id").toInt();


            QSqlRelationalTableModel* depPositionModel = Department_Position::create(model->database())->getModel();
            QSqlRecord r = depPositionModel->record(-1);
            r.setValue(1, QVariant(QString::number(departmentId)));
            r.setValue(2, QVariant(QString::number(positionId)));
            depPositionModel->insertRecord(-1, r);
            depPositionModel->select();

            populateDepartmentPositions(ui->department->currentIndex());

            int positionCount = departmentPositions->rowCount();
            for(int i = 0; i < positionCount; i++) {
                if (departmentPositions->record(i).value("id").toInt() == positionId) {
                    ui->position->setCurrentIndex(i);
                    break;
                }
            }
        }
        else {
            if (livingAddress >= 0){
                ui->livingAddress->setCurrentIndex(livingAddress);
            }

            if (registerAddress >= 0) {
                ui->registerAddress->setCurrentIndex(registerAddress);
            }

            if (relationComboBox) {
                relationComboBox->setCurrentIndex(rowNumber);
                relationComboBox = NULL;
            }

            livingAddress   = -1;
            registerAddress = -1;
        }
    }
}

/**
 * @brief addEmployer::rejectAddition
 */
void addEmployer::rejectAddition()
{
    relationComboBox = NULL;
}

/**
 * @brief addEmployer::initAddition
 */
void addEmployer::initAddition()
{
    QPushButton* add_button = dynamic_cast<QPushButton*>(sender());
    if (add_button != NULL) {
        relationComboBox = addInComboMap[add_button->objectName()];

        livingAddress   = ui->livingAddress->currentIndex();
        registerAddress = ui->registerAddress->currentIndex();
    }
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


    QSqlRelationalTableModel* scheduleModel = Schedule::create(model->database())->getModel();
    int scheduleCount = scheduleModel->rowCount();
    for(int i = 0; i < scheduleCount; i++) {
        if (scheduleModel->record(i).value("id").toInt() == record.value("schedule_id").toInt()) {
            ui->schedule->setCurrentIndex(i);
            break;
        }
    }



    int employerId = record.value("id").toInt();


    QSqlQueryModel *employerIdQueryModel = new QSqlQueryModel;
    employerIdQueryModel->setQuery("SELECT eei.emp_number FROM employer_employer_ids as eei " \
                         " WHERE eei.employer_id = " + QString::number(employerId) +
                         " AND eei.to IS NULL");

    QString employerNumber = employerIdQueryModel->record(0).value("emp_number").toString();
    QSqlRelationalTableModel* employerIdModel = EmployerId::create(model->database())->getModel();
    int employerIdCount = employerIdModel->rowCount();
    for(int i = 0; i < employerIdCount; i++) {
        if (employerIdModel->record(i).value("emp_number").toString() == employerNumber) {
            ui->employerId->setCurrentIndex(i);
            break;
        }
    }





    QSqlQueryModel *employerDepPositionModel = new QSqlQueryModel;
    employerDepPositionModel->setQuery("SELECT dp.department_id, dp.position_id FROM employer_dep_positions as edp " \
                         "JOIN dep_positions as dp ON edp.dep_positions_id = dp.id " \
                         "WHERE edp.employer_id = " + QString::number(employerId) +
                         " AND edp.to IS NULL");

    int department_id = employerDepPositionModel->record(0).value("department_id").toInt();
    int position_id = employerDepPositionModel->record(0).value("position_id").toInt();

    QSqlRelationalTableModel* departmentModel = Department::create(model->database())->getModel();
    int departmentCount = departmentModel->rowCount();
    for(int i = 0; i < departmentCount; i++) {
        if (departmentModel->record(i).value("id").toInt() == department_id) {
            ui->department->setCurrentIndex(i);
            break;
        }
    }

    int positionCount = departmentPositions->rowCount();
    for(int i = 0; i < positionCount; i++) {
        if (departmentPositions->record(i).value("id").toInt() == position_id) {
            ui->position->setCurrentIndex(i);
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
    ui->gender->setCurrentIndex(-1);
    ui->isConscript->setChecked(false);
    ui->familyStatus->setCurrentIndex(-1);
    ui->childrenNumber->setText("");
    ui->minorNumber->setText("");
    ui->registerAddress->setCurrentIndex(-1);
    ui->livingAddress->setCurrentIndex(-1);
    ui->department->setCurrentIndex(-1);
    ui->position->setCurrentIndex(-1);
    ui->employerId->setCurrentIndex(-1);
    ui->schedule->setCurrentIndex(-1);
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


    int scheduleId = Schedule::create(model->database())
                                        ->getModel()
                                        ->record(ui->schedule->currentIndex())
                                        .value("id").toInt();
    record.setValue(record.indexOf("schedule_id"), QVariant(scheduleId));
}


/**
 * This function is used to save employer_department_position record to tha database
 *
 * @brief addEmployer::employerDepartmentPositionEmployerIdSave
 * @param rowNumber
 */
void addEmployer::employerDepartmentPositionEmployerIdSave(int rowNumber)
{
    int employerId = Employer::create(model->database())
                                        ->getModel()
                                        ->record(rowNumber)
                                        .value("id").toInt();


    //==================================== Department Position ======================================

    int departmentId = Department::create(model->database())
                                        ->getModel()
                                        ->record(ui->department->currentIndex())
                                        .value("id").toInt();

    int positionId = departmentPositions->record(ui->position->currentIndex())
                                        .value("id").toInt();

    QSqlRelationalTableModel *dep_position =  Department_Position::create(model->database())->getModel();
    dep_position->setFilter("department_id = " + QString::number(departmentId) +
                            " AND position_id = " + QString::number(positionId));
    dep_position->select();

    if (dep_position->rowCount() == 1){
        int departmentPositionId = dep_position->record(0).value("id").toInt();

        QSqlQueryModel *lastEmployerDepPositionModel = new QSqlQueryModel;

        //Check if this position is new create it
        lastEmployerDepPositionModel->setQuery("SELECT edp.id FROM employer_dep_positions as edp " \
                             " JOIN dep_positions as dp ON edp.dep_positions_id = dp.id"\
                             " WHERE edp.employer_id = " + QString::number(employerId) +
                             " AND edp.to IS NULL AND dp.id = " + QString::number(departmentPositionId));

        if (lastEmployerDepPositionModel->rowCount() == 0)
        {


            lastEmployerDepPositionModel->setQuery("UPDATE employer_dep_positions as edp " \
                                 " SET edp.to = '" +  QDate::currentDate().toString("yyyy-M-d") + "'"\
                                 " WHERE edp.employer_id = " + QString::number(employerId) +
                                 " AND edp.to IS NULL");


            QSqlRelationalTableModel *employer_depPosition = Employer_DepPosition::create(model->database())->getModel();
            QSqlRecord employer_depPositionRecord = employer_depPosition->record();
            employer_depPositionRecord.setValue(employer_depPositionRecord.indexOf("employer_id"), QVariant(employerId));
            employer_depPositionRecord.setValue(employer_depPositionRecord.indexOf("dep_positions_id"), QVariant(departmentPositionId));
            employer_depPositionRecord.setValue(employer_depPositionRecord.indexOf("from"), QVariant(QDate::currentDate().toString("yyyy-M-d")));
            employer_depPosition->insertRecord(-1, employer_depPositionRecord);
            employer_depPosition->select();
        }
    }

    //======================================== Employer ID ==========================================


    QString employerNumber = EmployerId::create(model->database())
                                                    ->getModel()
                                                    ->record(ui->employerId->currentIndex())
                                                    .value("emp_number").toString();

    QSqlQueryModel *lastEmployerIdModel = new QSqlQueryModel;

    lastEmployerIdModel->setQuery("SELECT eei.id FROM employer_employer_ids as eei " \
                         " WHERE eei.employer_id = " + QString::number(employerId) +
                         " AND eei.to IS NULL AND eei.emp_number = '" + employerNumber + "'");

    if (lastEmployerIdModel->rowCount() == 0)
    {
        int employerIdType = EmployerId::create(model->database())
                                                        ->getModel()
                                                        ->record(ui->employerId->currentIndex())
                                                        .value("id_type").toInt();

        lastEmployerIdModel->setQuery("UPDATE employer_employer_ids as eei " \
                             " JOIN employer_ids as ei ON eei.emp_number = ei.emp_number "\
                             " SET eei.to = '" +  QDate::currentDate().toString("yyyy-M-d") + "'"\
                             " WHERE eei.employer_id = " + QString::number(employerId) +
                             " AND eei.to IS NULL AND ei.id_type = " + QString::number(employerIdType));


        QSqlRelationalTableModel *employer_employerId = Employer_EmployerId::create(model->database())->getModel();
        QSqlRecord employer_employerIdRecord = employer_employerId->record();
        employer_employerIdRecord.setValue(employer_employerIdRecord.indexOf("employer_id"), QVariant(employerId));
        employer_employerIdRecord.setValue(employer_employerIdRecord.indexOf("emp_number"), QVariant(employerNumber));
        employer_employerIdRecord.setValue(employer_employerIdRecord.indexOf("from"), QVariant(QDate::currentDate().toString("yyyy-M-d")));
        employer_employerId->insertRecord(-1, employer_employerIdRecord);
        employer_employerId->select();
    }
}
