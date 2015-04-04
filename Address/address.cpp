#include "address.h"
#include <QObject>

Address* Address::address = NULL;

/**
 * Create singleton object of Address
 *
 * @brief Address::create
 * @param dbConnection
 * @return
 */
Address* Address::create(QSqlDatabase* dbConnection)
{
    if (!address) {
        address = new Address(dbConnection);
    }

    return address;
}

/**
 * @brief Address::Address
 */
Address::Address(QSqlDatabase* dbConnection) {
    model = NULL;
    db = dbConnection;
    tableName  = "address";
}

/**
 * @brief Address::select
 * @param mainWindow
 */
void Address::select(QMainWindow *mainWindow)
{
    parent = mainWindow;

    tableView   = new QTableView(mainWindow);
    addButton   = new QPushButton("Ավելացնել Հասցե");
    mainLayout  = new QGridLayout;

    //Arrange widgets
    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
    mainWindow->centralWidget()->setLayout(mainLayout);

    tableView->setModel(getModel());

    //Connect mainWindow destroy with removeWidgets to remove dynamic objects
    QObject::connect(mainWindow, SIGNAL(destroyed()), tableView,  SLOT(deleteLater()));
    QObject::connect(mainWindow, SIGNAL(destroyed()), addButton,  SLOT(deleteLater()));
    QObject::connect(mainWindow, SIGNAL(destroyed()), mainLayout, SLOT(deleteLater()));
}

/**
 * @brief Address::getModel
 * @return
 */
QSqlRelationalTableModel* Address::getModel()
{
    //Check if model isn't created create it
    if (!model) {
        model = new QSqlRelationalTableModel(parent, *db);
        model->setTable(tableName);
        model->select();
    }

    return model;
}
