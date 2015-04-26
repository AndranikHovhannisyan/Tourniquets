#include "adddepartment.h"
#include "ui_adddepartment.h"
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDebug>

#include "Employer/employer.h"
#include "Schedule/schedule.h"
#include "Position/position.h"
#include "Department_Position/department_position.h"

/**
 * @brief addDepartment::addDepartment
 * @param tableModel
 * @param db
 * @param parent
 */
addDepartment::addDepartment(QSqlRelationalTableModel *tableModel, QSqlDatabase *db, QWidget *parent) :
    addDialog(tableModel, parent),
    ui(new Ui::addDepartment)
{
    ui->setupUi(this);
    this->setWindowTitle("Ավելացնել բաժին");

    ui->managers->setModel(Employer::create(model->database())->getModel());
    ui->schedule->setModel(Schedule::create(model->database())->getModel());
    ui->position->setModel(Position::create(model->database())->getModel());

    currentId = 0;
    connect(ui->add_position, SIGNAL(clicked()), this, SLOT(addPosition()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}

/**
 * @brief addDepartment::~addDepartment
 */
addDepartment::~addDepartment()
{
    delete ui;
}

/**
 * @brief addDepartment::init
 * @param record
 */
void addDepartment::init(QSqlRecord &record)
{
    ui->dep_name->setText(record.value("name").toString());

    //TODO: this is bad solution but can't find good solution yet
    QSqlRelationalTableModel* employerModel = Employer::create(model->database())->getModel();
    int employerCount = employerModel->rowCount();
    for(int i = 0; i < employerCount; i++) {
        if (employerModel->record(i).value("id").toInt() == record.value("manager_id").toInt()) {
            ui->managers->setCurrentIndex(i);
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

    //Save index of current opened department
    currentId = record.value("id").toInt();

    QSqlRelationalTableModel* depPositionModel = Department_Position::create(model->database())->getModel();
    depPositionModel->setFilter("department_id = " + QString::number(record.value("id").toInt()));
    depPositionModel->setRelation(2, QSqlRelation("position", "id", "name"));
    depPositionModel->select();
    ui->positionsTable->setModel(Department_Position::create(model->database())->getModel());
    ui->positionsTable->hideColumn(1);
}

/**
 * This slot is for add position button to add positions in add department window
 *
 * @brief addDepartment::addPosition
 */
void addDepartment::addPosition()
{
    QSqlRelationalTableModel* depPositionModel = Department_Position::create(model->database())->getModel();
    QSqlRecord positionRecord = Position::create(model->database())->getModel()->record(ui->position->currentIndex());
    QSqlRecord r = depPositionModel->record(-1);
    r.setValue(1, QVariant(QString::number(currentId)));
    r.setValue(2, QVariant(positionRecord.value("id").toInt()));
    depPositionModel->insertRecord(-1, r);
    depPositionModel->select();
}

/**
 * @brief addDepartment::clear
 */
void addDepartment::clear() {
    ui->dep_name->setText("");
    ui->managers->setCurrentIndex(-1);
    ui->schedule->setCurrentIndex(-1);
    ui->position->setCurrentIndex(-1);
}

/**
 * @brief addDepartment::populateData
 * @param record
 */
void addDepartment::populateData(QSqlRecord &record)
{
    record.setValue(record.indexOf("name"), QVariant(ui->dep_name->text()));

    int employerId = Employer::create(model->database())
                                        ->getModel()
                                        ->record(ui->managers->currentIndex())
                                        .value("id").toInt();
    record.setValue(record.indexOf("manager_id"), QVariant(employerId));


    int scheduleId = Schedule::create(model->database())
                                        ->getModel()
                                        ->record(ui->schedule->currentIndex())
                                        .value("id").toInt();
    record.setValue(record.indexOf("schedule_id"), QVariant(scheduleId));
}
