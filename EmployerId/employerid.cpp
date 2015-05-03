#include "EmployerId/employerid.h"
#include <QObject>
#include <QException>
#include <QMessageBox>
#include <QSqlError>
#include <QScrollBar>

EmployerId* EmployerId::employerId = NULL;

/**
 * Create singleton object of EmployerId
 *
 * @brief EmployerId::create
 * @param dbConnection
 * @param mainWindow
 * @return
 */
EmployerId* EmployerId::create(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    if (!employerId) {
        employerId = new EmployerId(dbConnection, mainWindow);
    }

    return employerId;
}

/**
 * @brief EmployerId::EmployerId
 */
EmployerId::EmployerId(QSqlDatabase dbConnection, QMainWindow *mainWindow):
    ViewChangableEntity(dbConnection, mainWindow)
{
    tableName       = "employer_ids";
    add_employerId  = NULL;
    employers       = NULL;
    employers_label = NULL;
}


/**
 * @brief EmployerId::createWidgets
 */
void EmployerId::createWidgets()
{
    ViewChangableEntity::createWidgets();

    tableView->setFixedWidth(520);
}

/**
 * @brief EmployerId::setTableViewModel
 */
void EmployerId::setTableViewModel()
{
    ViewChangableEntity::setTableViewModel();

    tableView->resizeColumnsToContents();
}


/**
 * @brief EmployerId::selectRow
 * @param modelIndex
 */
void EmployerId::selectRow(const QModelIndex &modelIndex)
{
    ViewChangableEntity::selectRow(modelIndex);

    QString employerID_empNumber = getModel()->record(modelIndex.row()).value("emp_number").toString();

    //============================================================
    //========================= Employers ========================
    //============================================================

    QSqlQueryModel *employerModel = new QSqlQueryModel;
    employerModel->setQuery("SELECT eei.id, CONCAT(e.firstname, ' ', lastname), eei.from, eei.to "\
                            "FROM employer_employer_ids as eei " \
                            "JOIN employer as e ON e.id = eei.employer_id "\
                            "WHERE eei.emp_number = '" + employerID_empNumber + "'");

    if (employerModel->rowCount())
    {
        employers = employers ? employers : new QTableView;
        employers->setModel(employerModel);
        employers->setFixedWidth(430);

        employers->verticalScrollBar()->setStyleSheet(
            "QScrollBar:vertical { width: 1px; }");

        employers_label = employers_label ? employers_label : new QLabel("<b>Աշխատակիցներ</b>");
        employers_label->setAlignment(Qt::AlignCenter);
        employers_label->setFixedWidth(350);

        mainLayout->addWidget(employers_label, 1, 7, 1, 7);
        mainLayout->addWidget(employers, 2, 7, 5, 7);
    }
    else {
        delete employers;
        delete employers_label;
        employers       = NULL;
        employers_label = NULL;
    }

    //============================================================
    //======================== End Positions =====================
    //============================================================
}



/**
 * @brief EmployerId::destroy
 */
void EmployerId::destroy()
{
    ViewChangableEntity::destroy();

    delete employers;
    delete employers_label;
    employers       = NULL;
    employers_label = NULL;
}

/**
 * @brief EmployerId::updateViewModel
 */
void EmployerId::updateViewModel()
{
    viewModel->setQuery("SELECT ei.emp_number, "\
                        "CASE "\
                        "WHEN ei.id_type = 0 "\
                        "THEN 'Քարտ' "\
                        "ELSE 'Մատնահետք' "\
                        "END as IdType "\
                        " FROM employer_ids as ei ");

    viewModel->setHeaderData(0,  Qt::Horizontal, "ID");
    viewModel->setHeaderData(1,  Qt::Horizontal, "Տիպը");
}

/**
 * @brief EmployerId::getAddDialog
 * @return
 */
addDialog* EmployerId::getAddDialog()
{
    add_employerId = add_employerId ? add_employerId : new addEmployerId(getModel());
    return add_employerId;
}
