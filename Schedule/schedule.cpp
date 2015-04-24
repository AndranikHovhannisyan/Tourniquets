#include "Schedule/schedule.h"
#include <QException>
#include <QObject>


Schedule* Schedule::schedule = NULL;

/**
 * Create singleton object of Schedule
 *
 * @brief Schedule::create
 * @param dbConnection
 * @param mainWindow
 * @return
 */
Schedule* Schedule::create(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    if (!schedule) {
        schedule = new Schedule(dbConnection, mainWindow);
    }

    return schedule;
}

/**
 * @brief Schedule::Schedule
 */
Schedule::Schedule(QSqlDatabase dbConnection, QMainWindow *mainWindow) {
    model       = NULL;
    db          = dbConnection;
    parent      = mainWindow;
    tableName   = "schedule";

    add_schedule = NULL;
}

/**
 * @brief Schedule::select
 * @param mainWindow
 */
void Schedule::select(QMainWindow *mainWindow)
{
    if (mainWindow) {
        parent = mainWindow;
    }
    if (!parent) {
        throw new QException();
    }

    //Create widgets
    tableView   = new QTableView(mainWindow);
    addButton   = new QPushButton("Ավելացնել Գրաֆիկ");
    mainLayout  = new QGridLayout;

    //Arrange widgets on window
    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
    parent->centralWidget()->setLayout(mainLayout);

    //Set tableView content
    tableView->setModel(getModel());

    //Create addSchedule instance
    getAddSchedule();

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton, SIGNAL(clicked()), add_schedule, SLOT(initialize()));
    QObject::connect(tableView, SIGNAL(doubleClicked(QModelIndex)), add_schedule, SLOT(initialize(QModelIndex)));

    //Connect mainWindow destroy with removeWidgets to remove dynamic objects
    QObject::connect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}

/**
 * @brief Schedule::getModel
 * @return
 */
QSqlRelationalTableModel* Schedule::getModel()
{
    //Check if model isn't created create it
    if (!model) {
        model = new QSqlRelationalTableModel(parent, db);
        model->setTable(tableName);
        model->select();
    }

    return model;
}

/**
 * @brief Schedule::destroy
 */
void Schedule::destroy()
{
    delete tableView;
    delete addButton;
    delete mainLayout;

    tableView  = NULL;
    addButton  = NULL;
    mainLayout = NULL;

    QObject::disconnect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}

/**
 * @brief Schedule::initAddSchedule
 * @return
 */
addSchedule* Schedule::getAddSchedule()
{
    add_schedule = add_schedule ? add_schedule : new addSchedule(getModel());
    return add_schedule;
}
