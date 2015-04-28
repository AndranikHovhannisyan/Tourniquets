#include "EmployerId/employerid.h"
#include <QObject>
#include <QException>

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
    tableName   = "employer_ids";
}

/**
 * @brief EmployerId::select
 * @param mainWindow
 */
void EmployerId::select(QMainWindow *mainWindow)
{
    if (mainWindow) {
        parent = mainWindow;
    }
    if (!parent) {
        throw new QException();
    }

    //Create widgets
    tableView   = new QTableView(mainWindow);
    addButton   = new QPushButton("Ավելացնել աշխատակցի իդենտիֆիկատոր");
    mainLayout  = new QGridLayout;

    //Arrange widgets on window
    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
    parent->centralWidget()->setLayout(mainLayout);

    //Set tableView content
    tableView->setModel(getModel());

    //Create addEmployerId instance
    add_employerId = new addEmployerId(getModel());

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton, SIGNAL(clicked()), add_employerId, SLOT(initialize()));
    QObject::connect(tableView, SIGNAL(doubleClicked(QModelIndex)), add_employerId, SLOT(initialize(QModelIndex)));

    //Connect mainWindow destroy with removeWidgets to remove dynamic objects
    QObject::connect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
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

/**
 * @brief EmployerId::destroy
 */
void EmployerId::destroy()
{
    delete tableView;
    delete addButton;
    delete mainLayout;

    tableView  = NULL;
    addButton  = NULL;
    mainLayout = NULL;

    QObject::disconnect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}
