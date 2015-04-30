#include "EmployerId/employerid.h"
#include <QObject>
#include <QException>
#include <QMessageBox>
#include <QSqlError>

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
    tableName   = "employer_ids";
    add_employerId = NULL;
}


/**
 * @brief EmployerId::selectRow
 * @param modelIndex
 */
void EmployerId::selectRow(const QModelIndex &modelIndex)
{
    ViewChangableEntity::selectRow(modelIndex);
}



/**
 * @brief EmployerId::destroy
 */
void EmployerId::destroy()
{
    ViewChangableEntity::destroy();
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
