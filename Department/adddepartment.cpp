#include "adddepartment.h"
#include "ui_adddepartment.h"
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDebug>
#include <QScrollBar>

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
    ui->managers->setModelColumn(1);
    ui->schedule->setModel(Schedule::create(model->database())->getModel());
    ui->position->setModel(Position::create(model->database())->getModel());
    ui->position->setModelColumn(1);

    currentId = 0;
    connect(ui->add_position, SIGNAL(clicked()), this, SLOT(addPosition()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));

    connect(ui->positionsTable, SIGNAL(pressed(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    connect(ui->positionsTable, SIGNAL(clicked(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    connect(ui->remove_depPosition, SIGNAL(clicked()), this, SLOT(removeDepartmentPosition()));
}

/**
 * @brief addDepartment::~addDepartment
 */
addDepartment::~addDepartment()
{
    delete ui;
}

/**
 * @brief addDepartment::selectRow
 * @param modelIndex
 */
void addDepartment::selectRow(const QModelIndex &modelIndex)
{
    ui->positionsTable->selectRow(modelIndex.row());
}

/**
 * @brief addDepartment::remove
 */
void addDepartment::removeDepartmentPosition()
{
    QModelIndexList selectedRows = ui->positionsTable->selectionModel()->selectedRows();
    for( int i = 0; i < selectedRows.count(); i++) {
        Department_Position::create(model->database())->getModel()->removeRow(selectedRows.at(i).row());
    }

    Department_Position::create(model->database())->getModel()->select();
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

    //******************************************************************************************************
    //****************************************** Department Positions **************************************
    //******************************************************************************************************

    QSqlRelationalTableModel* depPositionModel = Department_Position::create(model->database())->getModel();
    depPositionModel->setFilter("department_id = " + QString::number(record.value("id").toInt()));
    depPositionModel->setRelation(2, QSqlRelation("position", "id", "name"));
    depPositionModel->select();

    ui->positionsTable->setModel(Department_Position::create(model->database())->getModel());
    ui->positionsTable->hideColumn(1);
    ui->positionsTable->setColumnWidth(0, 80);
    ui->positionsTable->setColumnWidth(2, 150);

    ui->positionsTable->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical { width: 2px; }");

    ui->positionsTable->show();
    ui->add_position->show();
    ui->position->show();
    ui->label_position->show();
    this->setFixedHeight(350);

    //******************************************************************************************************
    //**************************************** End Department Positions ************************************
    //******************************************************************************************************
}

/**
 * This slot is for add position button to add positions in add department window
 *
 * @brief addDepartment::addPosition
 */
void addDepartment::addPosition()
{
    QSqlRecord positionRecord = Position::create(model->database())->getModel()->record(ui->position->currentIndex());

    QSqlRelationalTableModel* depPositionModel = Department_Position::create(model->database())->getModel();
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

    ui->positionsTable->hide();
    ui->add_position->hide();
    ui->position->hide();
    ui->label_position->hide();
    this->setFixedHeight(170);
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
