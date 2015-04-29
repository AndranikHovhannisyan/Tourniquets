#include "EmployerId/employerid.h"
#include <QObject>
#include <QException>
#include <QMessageBox>
#include <QSqlError>

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

    errorLabel     = NULL;
    tableView      = NULL;
    addButton      = NULL;
    editButton     = NULL;
    removeButton   = NULL;
    mainLayout     = NULL;
    add_employerId = NULL;
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
    errorLabel  = errorLabel    ? errorLabel   : new QLabel;
    tableView   = tableView     ? tableView    : new QTableView(mainWindow);
    mainLayout  = mainLayout    ? mainLayout   : new QGridLayout;

    addButton    = addButton    ? addButton    : new QPushButton("Ավելացնել ԻԴ");
    editButton   = editButton   ? editButton   : new QPushButton("Խմբագրել");
    removeButton = removeButton ? removeButton : new QPushButton("Հեռացնել");

    //Arrange widgets on window
    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(editButton, 0, 2, 1, 2);
    mainLayout->addWidget(removeButton, 0, 4, 1, 2);
    mainLayout->addWidget(errorLabel, 0, 7, 1, 8);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
    parent->centralWidget()->setLayout(mainLayout);

    //Set tableView content
    tableView->setModel(getModel());

    //Create addEmployerId instance
    add_employerId = new addEmployerId(getModel());

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton, SIGNAL(clicked()), add_employerId, SLOT(initialize()));
    QObject::connect(editButton,   SIGNAL(clicked()), this, SLOT(edit()));
    QObject::connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));

    QObject::connect(tableView, SIGNAL(pressed(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView, SIGNAL(doubleClicked(QModelIndex)), add_employerId, SLOT(initialize(QModelIndex)));

    //Connect mainWindow destroy with removeWidgets to remove dynamic objects
    QObject::connect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}

/**
 * @brief EmployerId::selectRow
 * @param modelIndex
 */
void EmployerId::selectRow(const QModelIndex &modelIndex) {
    tableView->selectRow(modelIndex.row());
}

/**
 * @brief EmployerId::edit
 */
void EmployerId::edit()
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

    add_employerId->initByRowNumber(selectedRows.at(0).row());
}

/**
 * @brief EmployerId::remove
 */
void EmployerId::remove()
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
    delete mainLayout;
    delete errorLabel;

    delete addButton;
    delete editButton;
    delete removeButton;


    tableView      = NULL;
    mainLayout     = NULL;
    errorLabel     = NULL;
    addButton      = NULL;
    editButton     = NULL;
    removeButton   = NULL;

    QObject::disconnect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}
