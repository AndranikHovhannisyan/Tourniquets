#include "Department/department.h"
#include <QObject>
#include <QException>

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
    tableView   = new QTableView(mainWindow);
    addButton   = new QPushButton("Ավելացնել Բաժին");
    mainLayout  = new QGridLayout;

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
    QObject::connect(parent, SIGNAL(destroyed()), tableView,  SLOT(deleteLater()));
    QObject::connect(parent, SIGNAL(destroyed()), addButton,  SLOT(deleteLater()));
    QObject::connect(parent, SIGNAL(destroyed()), mainLayout, SLOT(deleteLater()));
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

