#include "address.h"
#include <QObject>
#include <QException>

Address* Address::address = NULL;

/**
 * Create singleton object of Address
 *
 * @brief Address::create
 * @param dbConnection
 * @return
 */
Address* Address::create(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    if (!address) {
        address = new Address(dbConnection, mainWindow);
    }

    return address;
}

/**
 * @brief Address::Address
 */
Address::Address(QSqlDatabase dbConnection, QMainWindow *mainWindow) {
    model       = NULL;
    db          = dbConnection;
    parent      = mainWindow;
    tableName   = "address";

    tableView   = NULL;
    addButton   = NULL;
    mainLayout  = NULL;
    add_address = NULL;
}

/**
 * @brief Address::select
 * @param mainWindow
 */
void Address::select(QMainWindow *mainWindow)
{
    if (mainWindow) {
        parent = mainWindow;
    }
    if (!parent) {
        throw new QException();
    }

    //Create widgets
    tableView   = tableView  ? tableView  : new QTableView();
    addButton   = addButton  ? addButton  : new QPushButton("Ավելացնել Հասցե");
    mainLayout  = mainLayout ? mainLayout : new QGridLayout;

    //Arrange widgets on window
    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
    parent->centralWidget()->setLayout(mainLayout);

    //Set tableView content
    tableView->setModel(getModel());

    //Create addAddress instance
    getAddAddress();

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton, SIGNAL(clicked()), add_address, SLOT(initialize()));
    QObject::connect(tableView, SIGNAL(doubleClicked(QModelIndex)), add_address, SLOT(initialize(QModelIndex)));

    //Connect parent destroy with removeWidgets to remove dynamic objects
    QObject::connect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}

/**
 * @brief Address::getModel
 * @return
 */
QSqlRelationalTableModel* Address::getModel()
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
 * @brief Address::destroy
 */
void Address::destroy()
{
    delete tableView;
    delete addButton;
    delete mainLayout;

    tableView  = NULL;
    addButton  = NULL;
    mainLayout = NULL;

    QObject::disconnect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}

/**
 * @brief Address::initAddAddress
 * @return
 */
addAddress* Address::getAddAddress()
{
    add_address = add_address ? add_address : new addAddress(getModel());
    return add_address;
}
