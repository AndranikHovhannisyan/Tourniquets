#include "Position/position.h"
#include <QObject>
#include <QException>

Position* Position::position = NULL;

/**
 * Create singleton object of Position
 *
 * @brief Position::create
 * @param dbConnection
 * @param mainWindow
 * @return
 */
Position* Position::create(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    if (!position) {
        position = new Position(dbConnection, mainWindow);
    }

    return position;
}

/**
 * @brief Position::Position
 */
Position::Position(QSqlDatabase dbConnection, QMainWindow *mainWindow) {
    model       = NULL;
    db          = dbConnection;
    parent      = mainWindow;
    tableName   = "position";
}

/**
 * @brief Position::select
 * @param mainWindow
 */
void Position::select(QMainWindow *mainWindow)
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

    //Create addPosition instance
    add_position = new addPosition(getModel());

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton, SIGNAL(clicked()), add_position, SLOT(initialize()));
    QObject::connect(tableView, SIGNAL(doubleClicked(QModelIndex)), add_position, SLOT(initialize(QModelIndex)));

    //Connect mainWindow destroy with removeWidgets to remove dynamic objects
    QObject::connect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}

/**
 * @brief Position::getModel
 * @return
 */
QSqlRelationalTableModel* Position::getModel()
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
 * @brief Position::destroy
 */
void Position::destroy()
{
    delete tableView;
    delete addButton;
    delete mainLayout;

    tableView  = NULL;
    addButton  = NULL;
    mainLayout = NULL;

    QObject::disconnect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}
