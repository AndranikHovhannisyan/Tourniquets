#include "Schedule/schedule.h"
#include <QObject>
#include <QMessageBox>
#include <QSqlError>
#include <QException>

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

    errorLabel   = NULL;
    tableView    = NULL;
    mainLayout   = NULL;

    addButton    = NULL;
    editButton   = NULL;
    removeButton = NULL;
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
    errorLabel   = errorLabel   ? errorLabel   : new QLabel;
    tableView    = tableView    ? tableView    : new QTableView();
    mainLayout   = mainLayout   ? mainLayout   : new QGridLayout;

    addButton    = addButton    ? addButton    : new QPushButton("Ավելացնել Գրաֆիկ");
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

    getAddSchedule();

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton,    SIGNAL(clicked()), add_schedule, SLOT(initialize()));
    QObject::connect(editButton,   SIGNAL(clicked()), this, SLOT(edit()));
    QObject::connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));

    QObject::connect(tableView,    SIGNAL(pressed(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView,    SIGNAL(clicked(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView,    SIGNAL(doubleClicked(QModelIndex)), add_schedule, SLOT(initialize(QModelIndex)));

    QObject::connect(parent,       SIGNAL(destroyed()), this,  SLOT(destroy()));
}

/**
 * @brief Schedule::selectRow
 * @param modelIndex
 */
void Schedule::selectRow(const QModelIndex &modelIndex) {
    tableView->selectRow(modelIndex.row());
}

/**
 * @brief Schedule::edit
 */
void Schedule::edit()
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

    add_schedule->initByRowNumber(selectedRows.at(0).row());
}

/**
 * @brief Schedule::remove
 */
void Schedule::remove()
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
    delete mainLayout;

    delete addButton;
    delete editButton;
    delete removeButton;

    tableView    = NULL;
    mainLayout   = NULL;

    addButton    = NULL;
    editButton   = NULL;
    removeButton = NULL;

    QObject::disconnect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}

/**
 * @brief Schedule::getAddSchedule
 * @return
 */
addSchedule* Schedule::getAddSchedule()
{
    add_schedule = add_schedule ? add_schedule : new addSchedule(getModel());
    return add_schedule;
}
