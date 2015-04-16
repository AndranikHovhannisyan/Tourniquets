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
    tableView   = new QTableView(parent);
    addButton   = new QPushButton("Ավելացնել Հասցե");
    mainLayout  = new QGridLayout;

    //Arrange widgets on window
    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
    parent->centralWidget()->setLayout(mainLayout);

    //Set tableView content
    tableView->setModel(getModel());

    //Create addAddress instance
    add_address = new addAddress(getModel());

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton, SIGNAL(clicked()), add_address, SLOT(initialize()));
    QObject::connect(tableView, SIGNAL(doubleClicked(QModelIndex)), add_address, SLOT(initialize(QModelIndex)));

    //Connect parent destroy with removeWidgets to remove dynamic objects
    QObject::connect(parent, SIGNAL(destroyed()), tableView,  SLOT(deleteLater()));
    QObject::connect(parent, SIGNAL(destroyed()), addButton,  SLOT(deleteLater()));
    QObject::connect(parent, SIGNAL(destroyed()), mainLayout, SLOT(deleteLater()));
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
