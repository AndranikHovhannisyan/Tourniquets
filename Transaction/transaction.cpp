#include "Transaction/transaction.h"
#include <QException>
#include <QObject>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QDateTime>
#include <QTextStream>

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
    ViewChangableEntity(dbConnection, mainWindow)
{
    tableName       = "tourniquet_transaction";

    add_transaction = NULL;
    importButton    = NULL;

    showOriginal    = NULL;
}

/**
 * @brief Transaction::createWidgets
 */
void Transaction::createWidgets()
{
    ViewChangableEntity::createWidgets();

    importButton = importButton ? importButton : new QPushButton("Ներմուծել");
    showOriginal = showOriginal ? showOriginal : new QCheckBox("Սկզբնականը");
}

/**
 * @brief Transaction::getAddDialog
 * @return
 */
addDialog* Transaction::getAddDialog()
{
    add_transaction = add_transaction ? add_transaction : new addTransaction(getModel());
    return add_transaction;
}

/**
 * @brief Transaction::setWidgetsInLayout
 */
void Transaction::setWidgetsInLayout()
{
    ViewChangableEntity::setWidgetsInLayout();

    mainLayout->addWidget(importButton, 0, 6, 1, 2);
    mainLayout->addWidget(showOriginal, 0, 8, 1, 2);
}

/**
 * @brief Transaction::setSignalSlotConnections
 */
void Transaction::setSignalSlotConnections()
{
    ViewChangableEntity::setSignalSlotConnections();

    QObject::connect(importButton, SIGNAL(clicked()), this, SLOT(importData()));
    QObject::connect(showOriginal, SIGNAL(stateChanged(int)), this, SLOT(changeModel(int)));
}

#include <QDebug>

/**
 * @brief Transaction::changeModel
 */
void Transaction::changeModel(int isOriginal)
{
    //TODO:: need to change this solution
    QString transactionTableName = "";
    if (isOriginal){
        transactionTableName = "original_tourniquet_transaction ";
    }
    else {
        transactionTableName = "tourniquet_transaction ";

    }

    viewModel->setQuery("SELECT tt.id, CONCAT(e.firstname, ' ', e.lastname), tt.tourniquet_number, "\

                        "CASE "\
                        "WHEN t.type = 0 "\
                        "THEN 'Մուտք' "\
                        "ELSE 'Ելք' "\
                        "END as type, "\

                        "tt.date_time "\
                        "FROM " + transactionTableName + " as tt "\
                        "LEFT JOIN employer_employer_ids as eei ON eei.emp_number = tt.emp_number AND eei.to IS NULL "\
                        "LEFT JOIN employer_ids as ei ON ei.emp_number = tt.emp_number "\
                        "LEFT JOIN employer as e ON e.id = eei.employer_id "\
                        "LEFT JOIN tourniquet as t ON t.number = tt.tourniquet_number "\
                        "ORDER BY tt.id");

    viewModel->setHeaderData(0,  Qt::Horizontal, "ID");
    viewModel->setHeaderData(1,  Qt::Horizontal, "Անունը");
    viewModel->setHeaderData(2,  Qt::Horizontal, "Տուրնիկետը");
    viewModel->setHeaderData(3,  Qt::Horizontal, "Մուտք/Ելք");
    viewModel->setHeaderData(4,  Qt::Horizontal, "Անցման պահը");
}

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

        QSqlRelationalTableModel *originalTransactionModel = new QSqlRelationalTableModel(parent, db);
        originalTransactionModel->setTable("original_tourniquet_transaction");
        originalTransactionModel->select();


        //Read from file and write in view edit
        QTextStream in(&file);
        in.readLine();
        QString lineStr = "";
        QStringList lineList;
        while(!in.atEnd()) {
            lineStr = in.readLine();
            lineList = lineStr.split('\t');

            QSqlRecord record = originalTransactionModel->record(-1);
            record.setValue(record.indexOf("tourniquet_number"), QVariant(lineList.at(1)));
            record.setValue(record.indexOf("emp_number"), QVariant(lineList.at(2)));
            record.setValue(record.indexOf("date_time"), QVariant(QDateTime::fromString(lineList.at(6), "d/M/yyyy hh:mm:ss")));
            originalTransactionModel->insertRecord(-1, record);
        }

        file.close();
        getModel()->select();
        updateViewModel();
    }
}


/**
 * @brief Transaction::destroy
 */
void Transaction::destroy()
{
    ViewChangableEntity::destroy();

    delete importButton;
    importButton = NULL;
}

/**
 * @brief Transaction::updateViewModel
 */
void Transaction::updateViewModel()
{
    viewModel->setQuery("SELECT tt.id, CONCAT(e.firstname, ' ', e.lastname), tt.tourniquet_number, "\

                        "CASE "\
                        "WHEN t.type = 0 "\
                        "THEN 'Մուտք' "\
                        "ELSE 'Ելք' "\
                        "END as type, "\

                        "tt.date_time "\
                        "FROM tourniquet_transaction as tt "\
                        "LEFT JOIN employer_employer_ids as eei ON eei.emp_number = tt.emp_number AND eei.to IS NULL "\
                        "LEFT JOIN employer_ids as ei ON ei.emp_number = tt.emp_number "\
                        "LEFT JOIN employer as e ON e.id = eei.employer_id "\
                        "LEFT JOIN tourniquet as t ON t.number = tt.tourniquet_number "\
                        "ORDER BY tt.id");

    viewModel->setHeaderData(0,  Qt::Horizontal, "ID");
    viewModel->setHeaderData(1,  Qt::Horizontal, "Անունը");
    viewModel->setHeaderData(2,  Qt::Horizontal, "Տուրնիկետը");
    viewModel->setHeaderData(3,  Qt::Horizontal, "Մուտք/Ելք");
    viewModel->setHeaderData(4,  Qt::Horizontal, "Անցման պահը");
}

/*

DELIMITER $$
CREATE TRIGGER aftre_transaction_import
AFTER INSERT ON original_tourniquet_transaction
FOR EACH ROW
BEGIN
    INSERT INTO tourniquet_transaction (date_time, tourniquet_number, emp_number)
           VALUES (NEW.date_time, NEW.tourniquet_number, NEW.emp_number);
END; $$
DELIMITER ;

*/
