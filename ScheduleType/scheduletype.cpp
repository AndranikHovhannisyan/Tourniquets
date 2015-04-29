#include "ScheduleType/scheduletype.h"
#include <QException>
#include <QObject>
#include <QMessageBox>
#include <QSqlError>


ScheduleType* ScheduleType::scheduleType = NULL;

/**
 * Create singleton object of ScheduleType
 *
 * @brief ScheduleType::create
 * @param dbConnection
 * @param mainWindow
 * @return
 */
ScheduleType* ScheduleType::create(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    if (!scheduleType) {
        scheduleType = new ScheduleType(dbConnection, mainWindow);
    }

    return scheduleType;
}

/**
 * @brief ScheduleType::ScheduleType
 */
ScheduleType::ScheduleType(QSqlDatabase dbConnection, QMainWindow *mainWindow) {
    model       = NULL;
    db          = dbConnection;
    parent      = mainWindow;
    tableName   = "schedule_type";

    add_scheduleType = NULL;

    errorLabel   = NULL;
    tableView    = NULL;
    mainLayout   = NULL;

    addButton    = NULL;
    editButton   = NULL;
    removeButton = NULL;
}

/**
 * @brief ScheduleType::select
 * @param mainWindow
 */
void ScheduleType::select(QMainWindow *mainWindow)
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

    //Create addScheduleType instance
    add_scheduleType = new addScheduleType(getModel());

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton, SIGNAL(clicked()), add_scheduleType, SLOT(initialize()));
    QObject::connect(editButton,   SIGNAL(clicked()), this, SLOT(edit()));
    QObject::connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));

    QObject::connect(tableView,    SIGNAL(pressed(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView,    SIGNAL(clicked(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView, SIGNAL(doubleClicked(QModelIndex)), add_scheduleType, SLOT(initialize(QModelIndex)));

    //Connect mainWindow destroy with removeWidgets to remove dynamic objects
    QObject::connect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}

/**
 * @brief ScheduleType::selectRow
 * @param modelIndex
 */
void ScheduleType::selectRow(const QModelIndex &modelIndex) {
    tableView->selectRow(modelIndex.row());
}

/**
 * @brief ScheduleType::edit
 */
void ScheduleType::edit()
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

    add_scheduleType->initByRowNumber(selectedRows.at(0).row());
}

/**
 * @brief ScheduleType::remove
 */
void ScheduleType::remove()
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
 * @brief ScheduleType::getModel
 * @return
 */
QSqlRelationalTableModel* ScheduleType::getModel()
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
 * @brief ScheduleType::destroy
 */
void ScheduleType::destroy()
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
