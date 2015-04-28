#include "Department/department.h"
#include <QObject>
#include <QException>
#include <QMessageBox>
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

    errorLabel= NULL;

    tableView    = NULL;
    addButton    = NULL;
    editButton   = NULL;
    removeButton = NULL;
    mainLayout   = NULL;
    add_department = NULL;
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

    errorLabel = errorLabel ? errorLabel : new QLabel;

    //Create widgets
    tableView    = tableView    ? tableView    : new QTableView();
    addButton    = addButton    ? addButton    : new QPushButton("Ավելացնել Բաժին");
    editButton   = editButton   ? editButton   : new QPushButton("Խմբագրել");
    removeButton = removeButton ? removeButton : new QPushButton("Հեռացնել");
    mainLayout   = mainLayout   ? mainLayout   : new QGridLayout;

    //Arrange widgets on window
    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(editButton, 0, 2, 1, 2);
    mainLayout->addWidget(removeButton, 0, 4, 1, 2);
    mainLayout->addWidget(errorLabel, 0, 7, 1, 8);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
    parent->centralWidget()->setLayout(mainLayout);


    //Set tableView content
    tableView->setModel(getModel());

    //Create addDepartment instance
    getAddDepartment();

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton, SIGNAL(clicked()), add_department, SLOT(initialize()));
    QObject::connect(editButton,   SIGNAL(clicked()), this, SLOT(edit()));
    QObject::connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));

    QObject::connect(tableView, SIGNAL(pressed(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView, SIGNAL(doubleClicked(QModelIndex)), add_department, SLOT(initialize(QModelIndex)));

    //Connect mainWindow destroy with removeWidgets to remove dynamic objects
    QObject::connect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}

/**
 * @brief Department::selectRow
 * @param modelIndex
 */
void Department::selectRow(const QModelIndex &modelIndex) {
    tableView->selectRow(modelIndex.row());
}

/**
 * @brief Department::edit
 */
void Department::edit()
{
    QModelIndexList selectedRows = tableView->selectionModel()->selectedRows();
    if (selectedRows.count() == 0) {
        QMessageBox::warning(NULL, "Error", "Ոչ մի տող նշված չէ");
        return;
    }

    if (selectedRows.count() > 1) {
        QMessageBox::warning(NULL, "Error", "Խմբագրման համար անհրաժեշտ է նշել ճիշտ մեկ տող");
        return;
    }

    add_department->initByRowNumber(selectedRows.at(0).row());
}
#include <QDebug>
#include <QSqlError>

/**
 * @brief Department::remove
 */
void Department::remove()
{
    QModelIndexList selectedRows = tableView->selectionModel()->selectedRows();
    for( int i = 0; i < selectedRows.count(); i++) {
        getModel()->removeRow(selectedRows.at(i).row());

        errorLabel->setText(getModel()->lastError().text());
        errorLabel->setStyleSheet("QLabel { color: red; font: 8pt; }");
        errorLabel->setWordWrap(true);
    }

    getModel()->select();
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
    delete editButton;
    delete removeButton;
    delete mainLayout;
    delete errorLabel;

    errorLabel     = NULL;
    tableView      = NULL;
    addButton      = NULL;
    editButton     = NULL;
    removeButton   = NULL;
    mainLayout     = NULL;
    add_department = NULL;

    QObject::disconnect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}

/**
 * @brief Department::initAddDepartment
 * @return
 */
addDepartment* Department::getAddDepartment()
{
    add_department = add_department ? add_department : new addDepartment(getModel());
    return add_department;
}

