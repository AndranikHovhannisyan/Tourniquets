#include "Transaction/transaction.h"
#include <QException>
#include <QObject>
#include <QFile>
#include <QFileDialog>
#include <QDir>

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

    importButton = NULL;
}

/**
 * @brief Transaction::createWidgets
 */
void Transaction::createWidgets()
{
    errorLabel   = errorLabel   ? errorLabel   : new QLabel;
    tableView    = tableView    ? tableView    : new QTableView();
    mainLayout   = mainLayout   ? mainLayout   : new QGridLayout;

    importButton = importButton ? importButton : new QPushButton("Ներմուծել");
}

/**
 * @brief Transaction::setWidgetsInLayout
 */
void Transaction::setWidgetsInLayout()
{
    mainLayout->addWidget(importButton, 0, 0, 1, 2);
    mainLayout->addWidget(errorLabel, 0, 7, 1, 8);
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

    QObject::connect(parent,       SIGNAL(destroyed()),                this,           SLOT(destroy()));


    QObject::connect(importButton, SIGNAL(clicked()), this, SLOT(importData()));

    QObject::connect(getModel(), SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(reselect(QModelIndex,QModelIndex)));
    QObject::connect(this, SIGNAL(reselect(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
}

#include <QDebug>

#include <QDateTime>

/**
 * @brief Transaction::importData
 */
void Transaction::importData()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        "Open Image", QDir::currentPath(), "Text Files (*.txt)");

    QFile file(fileName);
    //Check if file exists write it's name in the input
    if(file.exists()) {

        if(!file.open(QFile::ReadOnly | QFile::Text)) {
            return;
        }


        //Read from file and write in view edit
        QTextStream in(&file);
        in.readLine();
        QString lineStr = "";
        QStringList lineList;
        while(!in.atEnd()) {
            lineStr = in.readLine();
            lineList = lineStr.split('\t');

            QSqlRecord record = getModel()->record(-1);
            record.setValue(record.indexOf("tourniquet_id"), QVariant(lineList.at(1)));
            record.setValue(record.indexOf("emp_number"), QVariant(lineList.at(2)));
            record.setValue(record.indexOf("date_time"), QVariant(QDateTime::fromString(lineList.at(6), "d/M/yyyy hh:mm:ss")));
            getModel()->insertRecord(-1, record);
        }

        file.close();
        getModel()->select();
    }
}
