#include "EmployerId/employerid.h"
#include <QObject>


EmployerId* EmployerId::employerId = NULL;

/**
 * Create singleton object of EmployerId
 *
 * @brief EmployerId::create
 * @param dbConnection
 * @param mainWindow
 * @return
 */
EmployerId* EmployerId::create(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    if (!employerId) {
        employerId = new EmployerId(dbConnection, mainWindow);
    }

    return employerId;
}

/**
 * @brief EmployerId::EmployerId
 */
EmployerId::EmployerId(QSqlDatabase dbConnection, QMainWindow *mainWindow) {
    model       = NULL;
    db          = dbConnection;
    parent      = mainWindow;
    tableName   = "employer_id";
}

/**
 * @brief EmployerId::select
 * @param mainWindow
 */
void EmployerId::select(QMainWindow *mainWindow)
{
    //Create widgets
    tableView   = new QTableView(mainWindow);
    addButton   = new QPushButton("Ավելացնել Բաժին");
    mainLayout  = new QGridLayout;

    //Arrange widgets on window
    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
    mainWindow->centralWidget()->setLayout(mainLayout);

    //Set tableView content
    tableView->setModel(getModel());

    //Create addEmployerId instance
    add_employerId = new addEmployerId(getModel());

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton, SIGNAL(clicked()), add_employerId, SLOT(initialize()));
    QObject::connect(tableView, SIGNAL(doubleClicked(QModelIndex)), add_employerId, SLOT(initialize(QModelIndex)));

    //Connect mainWindow destroy with removeWidgets to remove dynamic objects
    QObject::connect(mainWindow, SIGNAL(destroyed()), tableView,  SLOT(deleteLater()));
    QObject::connect(mainWindow, SIGNAL(destroyed()), addButton,  SLOT(deleteLater()));
    QObject::connect(mainWindow, SIGNAL(destroyed()), mainLayout, SLOT(deleteLater()));
}

/**
 * @brief EmployerId::getModel
 * @return
 */
QSqlRelationalTableModel* EmployerId::getModel()
{
    //Check if model isn't created create it
    if (!model) {
        model = new QSqlRelationalTableModel(parent, db);
        model->setTable(tableName);
        model->select();
    }

    return model;
}
