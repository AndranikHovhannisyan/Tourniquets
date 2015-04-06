#include "Schedule/schedule.h"
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
Schedule* Schedule::create(QSqlDatabase* dbConnection, QMainWindow *mainWindow)
{
    if (!schedule) {
        schedule = new Schedule(dbConnection, mainWindow);
    }

    return schedule;
}

/**
 * @brief Schedule::Schedule
 */
Schedule::Schedule(QSqlDatabase* dbConnection, QMainWindow *mainWindow) {
    model       = NULL;
    db          = dbConnection;
    parent      = mainWindow;
    tableName   = "schedule";
}

/**
 * @brief Schedule::select
 * @param mainWindow
 */
void Schedule::select(QMainWindow *mainWindow)
{
    //Create widgets
    tableView   = new QTableView(mainWindow);
    addButton   = new QPushButton("Ավելացնել Գրաֆիկ");
    mainLayout  = new QGridLayout;

    //Arrange widgets on window
    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
    mainWindow->centralWidget()->setLayout(mainLayout);

    //Set tableView content
    tableView->setModel(getModel());

    //Create addSchedule instance
    add_schedule = new addSchedule(getModel());

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton, SIGNAL(clicked()), add_schedule, SLOT(initialize()));
    QObject::connect(tableView, SIGNAL(doubleClicked(QModelIndex)), add_schedule, SLOT(initialize(QModelIndex)));

    //Connect mainWindow destroy with removeWidgets to remove dynamic objects
    QObject::connect(mainWindow, SIGNAL(destroyed()), tableView,  SLOT(deleteLater()));
    QObject::connect(mainWindow, SIGNAL(destroyed()), addButton,  SLOT(deleteLater()));
    QObject::connect(mainWindow, SIGNAL(destroyed()), mainLayout, SLOT(deleteLater()));
}

/**
 * @brief Schedule::getModel
 * @return
 */
QSqlRelationalTableModel* Schedule::getModel()
{
    //Check if model isn't created create it
    if (!model) {
        model = new QSqlRelationalTableModel(parent, *db);
        model->setTable(tableName);
        model->select();
    }

    return model;
}
