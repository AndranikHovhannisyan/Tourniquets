#include "ScheduleType/scheduletype.h"
#include <QObject>


ScheduleType* ScheduleType::scheduleType = NULL;

/**
 * Create singleton object of ScheduleType
 *
 * @brief ScheduleType::create
 * @param dbConnection
 * @param mainWindow
 * @return
 */
ScheduleType* ScheduleType::create(QSqlDatabase* dbConnection, QMainWindow *mainWindow)
{
    if (!scheduleType) {
        scheduleType = new ScheduleType(dbConnection, mainWindow);
    }

    return scheduleType;
}

/**
 * @brief ScheduleType::ScheduleType
 */
ScheduleType::ScheduleType(QSqlDatabase* dbConnection, QMainWindow *mainWindow) {
    model       = NULL;
    db          = dbConnection;
    parent      = mainWindow;
    tableName   = "schedule_type";
}

/**
 * @brief ScheduleType::select
 * @param mainWindow
 */
void ScheduleType::select(QMainWindow *mainWindow)
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

    //Create addScheduleType instance
    add_scheduleType = new addScheduleType(getModel());

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton, SIGNAL(clicked()), add_scheduleType, SLOT(initialize()));
    QObject::connect(tableView, SIGNAL(doubleClicked(QModelIndex)), add_scheduleType, SLOT(initialize(QModelIndex)));

    //Connect mainWindow destroy with removeWidgets to remove dynamic objects
    QObject::connect(mainWindow, SIGNAL(destroyed()), tableView,  SLOT(deleteLater()));
    QObject::connect(mainWindow, SIGNAL(destroyed()), addButton,  SLOT(deleteLater()));
    QObject::connect(mainWindow, SIGNAL(destroyed()), mainLayout, SLOT(deleteLater()));
}

/**
 * @brief ScheduleType::getModel
 * @return
 */
QSqlRelationalTableModel* ScheduleType::getModel()
{
    //Check if model isn't created create it
    if (!model) {
        model = new QSqlRelationalTableModel(parent, *db);
        model->setTable(tableName);
        model->select();
    }

    return model;
}
