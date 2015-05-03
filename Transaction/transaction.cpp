#include "Transaction/transaction.h"
#include <QException>
#include <QObject>


Transaction* Transaction::transaction = NULL;

/**
 * Create singleton object of Transaction
 *
 * @brief Transaction::create
 * @param dbConnection
 * @param mainWindow
 * @return
 */
Transaction* Transaction::create(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    if (!transaction) {
        transaction = new Transaction(dbConnection, mainWindow);
    }

    return transaction;
}

/**
 * @brief Transaction::Transaction
 */
Transaction::Transaction(QSqlDatabase dbConnection, QMainWindow *mainWindow):
    EditableEntity(dbConnection, mainWindow)
{
    tableName   = "tourniquet_transaction";
}

/**
 * @brief Transaction::createWidgets
 */
void Transaction::createWidgets()
{
    errorLabel   = errorLabel   ? errorLabel   : new QLabel;
    tableView    = tableView    ? tableView    : new QTableView();
    mainLayout   = mainLayout   ? mainLayout   : new QGridLayout;
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
}

/**
 * @brief Transaction::setWidgetsInLayout
 */
void Transaction::setWidgetsInLayout()
{
//    mainLayout->addWidget(errorLabel, 0, 7, 1, 8);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
}

/**
 * @brief Transaction::setTableViewModel
 */
void Transaction::setTableViewModel()
{
    tableView->setModel(getModel());
}

/**
 * @brief Transaction::setSignalSlotConnections
 */
void Transaction::setSignalSlotConnections()
{
    QObject::connect(tableView,    SIGNAL(pressed(QModelIndex)),       this,           SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView,    SIGNAL(clicked(QModelIndex)),       this,           SLOT(selectRow(QModelIndex)));
//    QObject::connect(tableView,    SIGNAL(doubleClicked(QModelIndex)), getAddDialog(), SLOT(initialize(QModelIndex)));

    QObject::connect(parent,       SIGNAL(destroyed()),                this,           SLOT(destroy()));

    QObject::connect(getModel(), SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(reselect(QModelIndex,QModelIndex)));
    QObject::connect(this, SIGNAL(reselect(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
}
