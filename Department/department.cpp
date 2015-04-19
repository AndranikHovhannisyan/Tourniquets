#include "Department/department.h"
#include <QObject>
#include <QException>

#include <QComboBox>

Department* Department::department = NULL;

/**
 * Create singleton object of Department
 *
 * @brief Department::create
 * @param dbConnection
 * @param mainWindow
 * @return
 */
Department* Department::create(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    if (!department) {
        department = new Department(dbConnection, mainWindow);
    }

    return department;
}

/**
 * @brief Department::Department
 */
Department::Department(QSqlDatabase dbConnection, QMainWindow *mainWindow) {
    model       = NULL;
    db          = dbConnection;
    parent      = mainWindow;
    tableName   = "department";

    tableView  = NULL;
    addButton  = NULL;
    mainLayout = NULL;
}

/**
 * @brief Department::select
 * @param mainWindow
 */
void Department::select(QMainWindow *mainWindow)
{
    if (mainWindow) {
        parent = mainWindow;
    }
    if (!parent) {
        throw new QException();
    }

    //Create widgets
    tableView   = tableView  ? tableView  : new QTableView();
    addButton   = addButton  ? addButton  : new QPushButton("Ավելացնել Բաժին");
    mainLayout  = mainLayout ? mainLayout : new QGridLayout;

    //Arrange widgets on window
    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
    parent->centralWidget()->setLayout(mainLayout);


    //Set tableView content
    tableView->setModel(getModel());

    //Create addDepartment instance
    add_department = new addDepartment(getModel());

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton, SIGNAL(clicked()), add_department, SLOT(initialize()));
    QObject::connect(tableView, SIGNAL(doubleClicked(QModelIndex)), add_department, SLOT(initialize(QModelIndex)));

    //Connect mainWindow destroy with removeWidgets to remove dynamic objects
    QObject::connect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}

/**
 * @brief Department::getModel
 * @return
 */
QSqlRelationalTableModel* Department::getModel()
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
 * @brief Department::destroy
 */
void Department::destroy()
{
    delete tableView;
    delete addButton;
    delete mainLayout;

    tableView  = NULL;
    addButton  = NULL;
    mainLayout = NULL;

    QObject::disconnect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}

