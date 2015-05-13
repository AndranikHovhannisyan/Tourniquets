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

    QObject::disconnect(tableView,    SIGNAL(doubleClicked(QModelIndex)), getAddDialog(), SLOT(initialize(QModelIndex)));
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

        addButton->hide();
        editButton->hide();
        removeButton->hide();
    }
    else {
        transactionTableName = "tourniquet_transaction ";

        addButton->show();
        editButton->show();
        removeButton->show();
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
    delete showOriginal;

    importButton = NULL;
    showOriginal = NULL;
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



***************************************************************************************



DROP PROCEDURE IF EXISTS statistic;
DELIMITER $$
CREATE PROCEDURE statistic(department_id INT, employer_id INT, date_from DATE, date_to DATE)
BEGIN


SELECT d.name, CONCAT(e.firstname, ' ', e.lastname), DATE(tt1.date_time),

CASE
WHEN (TIMEDIFF(TIME(tt1.date_time), TIME(sh.standart_in_time)) < TIME(sh_ty.allow_lag)) AND
     (TIMEDIFF(TIME(sh.standart_in_time), TIME(tt1.date_time)) < TIME(sh_ty.ignore_time))
THEN TIME(sh.standart_in_time)
ELSE TIME(tt1.date_time)
END as in_time,

CASE
WHEN (TIMEDIFF(TIME(tt2.date_time), TIME(sh.standart_out_time)) < TIME(sh_ty.ignore_time)) AND
     (TIMEDIFF(TIME(sh.standart_out_time), TIME(tt2.date_time)) < TIME(sh_ty.allow_lag))
THEN TIME(sh.standart_out_time)
ELSE TIME(tt2.date_time)
END as out_time,

TIMEDIFF(
    CASE
    WHEN (TIMEDIFF(TIME(tt2.date_time), TIME(sh.standart_out_time)) < TIME(sh_ty.ignore_time)) AND
         (TIMEDIFF(TIME(sh.standart_out_time), TIME(tt2.date_time)) < TIME(sh_ty.allow_lag))
    THEN TIME(sh.standart_out_time)
    ELSE TIME(tt2.date_time)
    END,

    CASE
    WHEN (TIMEDIFF(TIME(tt1.date_time), TIME(sh.standart_in_time)) < TIME(sh_ty.allow_lag)) AND
         (TIMEDIFF(TIME(sh.standart_in_time), TIME(tt1.date_time)) < TIME(sh_ty.ignore_time))
    THEN TIME(sh.standart_in_time)
    ELSE TIME(tt1.date_time)
    END
) as workingTime,


CASE
WHEN
(TIMEDIFF(
    TIME(sh.standart_in_time),

    CASE
    WHEN (TIMEDIFF(TIME(tt1.date_time), TIME(sh.standart_in_time)) < TIME(sh_ty.allow_lag)) AND
         (TIMEDIFF(TIME(sh.standart_in_time), TIME(tt1.date_time)) < TIME(sh_ty.ignore_time))
    THEN TIME(sh.standart_in_time)
    ELSE TIME(tt1.date_time)
    END
) < 0)
THEN (TIMEDIFF(
    CASE
    WHEN (TIMEDIFF(TIME(tt1.date_time), TIME(sh.standart_in_time)) < TIME(sh_ty.allow_lag)) AND
         (TIMEDIFF(TIME(sh.standart_in_time), TIME(tt1.date_time)) < TIME(sh_ty.ignore_time))
    THEN TIME(sh.standart_in_time)
    ELSE TIME(tt1.date_time)
    END,

    TIME(sh.standart_in_time)
))
ELSE null
END as inLag,

CASE
WHEN
(TIMEDIFF(
    TIME(sh.standart_in_time),

    CASE
    WHEN (TIMEDIFF(TIME(tt1.date_time), TIME(sh.standart_in_time)) < TIME(sh_ty.allow_lag)) AND
         (TIMEDIFF(TIME(sh.standart_in_time), TIME(tt1.date_time)) < TIME(sh_ty.ignore_time))
    THEN TIME(sh.standart_in_time)
    ELSE TIME(tt1.date_time)
    END
) > 0)
THEN (TIMEDIFF(
    TIME(sh.standart_in_time),

    CASE
    WHEN (TIMEDIFF(TIME(tt1.date_time), TIME(sh.standart_in_time)) < TIME(sh_ty.allow_lag)) AND
         (TIMEDIFF(TIME(sh.standart_in_time), TIME(tt1.date_time)) < TIME(sh_ty.ignore_time))
    THEN TIME(sh.standart_in_time)
    ELSE TIME(tt1.date_time)
    END
))
ELSE null
END as inSoon,


CASE
WHEN
(TIMEDIFF(
    CASE
    WHEN (TIMEDIFF(TIME(tt2.date_time), TIME(sh.standart_out_time)) < TIME(sh_ty.ignore_time)) AND
         (TIMEDIFF(TIME(sh.standart_out_time), TIME(tt2.date_time)) < TIME(sh_ty.allow_lag))
    THEN TIME(sh.standart_out_time)
    ELSE TIME(tt2.date_time)
    END,
    TIME(sh.standart_out_time)
) < 0)
THEN (TIMEDIFF(
    TIME(sh.standart_out_time),

    CASE
    WHEN (TIMEDIFF(TIME(tt2.date_time), TIME(sh.standart_out_time)) < TIME(sh_ty.ignore_time)) AND
         (TIMEDIFF(TIME(sh.standart_out_time), TIME(tt2.date_time)) < TIME(sh_ty.allow_lag))
    THEN TIME(sh.standart_out_time)
    ELSE TIME(tt2.date_time)
    END
))
ELSE null
END as outSoon,


CASE
WHEN
(TIMEDIFF(
    CASE
    WHEN (TIMEDIFF(TIME(tt2.date_time), TIME(sh.standart_out_time)) < TIME(sh_ty.ignore_time)) AND
         (TIMEDIFF(TIME(sh.standart_out_time), TIME(tt2.date_time)) < TIME(sh_ty.allow_lag))
    THEN TIME(sh.standart_out_time)
    ELSE TIME(tt2.date_time)
    END,
    TIME(sh.standart_out_time)
) > 0)
THEN (TIMEDIFF(
    CASE
    WHEN (TIMEDIFF(TIME(tt2.date_time), TIME(sh.standart_out_time)) < TIME(sh_ty.ignore_time)) AND
         (TIMEDIFF(TIME(sh.standart_out_time), TIME(tt2.date_time)) < TIME(sh_ty.allow_lag))
    THEN TIME(sh.standart_out_time)
    ELSE TIME(tt2.date_time)
    END,
    TIME(sh.standart_out_time)
))
ELSE null
END as outLag


FROM tourniquet_transaction as tt1

JOIN employer_employer_ids as eei
ON tt1.emp_number = eei.emp_number AND eei.to IS NULL

JOIN employer as e
ON eei.employer_id = e.id

JOIN employer_dep_positions as edp
ON e.id = edp.employer_id AND edp.to IS NULL

JOIN dep_positions as dp
ON edp.dep_positions_id = dp.id

JOIN department as d
ON dp.department_id = d.id

JOIN tourniquet_transaction as tt2
ON DATE(tt1.date_time) = DATE(tt2.date_time) AND tt1.emp_number = tt2.emp_number

JOIN tourniquet as t1
ON tt1.tourniquet_number = t1.number AND t1.type = 0

JOIN tourniquet as t2
ON tt2.tourniquet_number = t2.number AND t2.type = 1

JOIN schedule as sh
ON e.schedule_id = sh.id

JOIN schedule_type as sh_ty
ON sh.schedule_type_id = sh_ty.id

WHERE (department_id = 0 OR d.id = department_id)
AND (employer_id = 0 OR e.id = employer_id)
AND (date_from IS NULL OR DATE(tt1.date_time) >= date_from)
AND (date_to IS NULL OR DATE(tt1.date_time) <= date_to);

END $$
DELIMITER ;


*/
