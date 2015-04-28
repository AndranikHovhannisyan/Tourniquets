#include "Employer_EmployerId/employer_employerid.h"
#include <QObject>
#include <QException>

Employer_EmployerId* Employer_EmployerId::employer_employerId = NULL;

/**
 * Create singleton object of Employer_EmployerId
 *
 * @brief Employer_EmployerId::create
 * @param dbConnection
 * @return
 */
Employer_EmployerId* Employer_EmployerId::create(QSqlDatabase dbConnection)
{
    if (!employer_employerId) {
        employer_employerId = new Employer_EmployerId(dbConnection);
    }

    return employer_employerId;
}

/**
 * @brief Employer_EmployerId::Employer_EmployerId
 */
Employer_EmployerId::Employer_EmployerId(QSqlDatabase dbConnection) {
    model       = NULL;
    db          = dbConnection;
    tableName   = "employer_employer_id";
}

/**
 * @brief Employer_EmployerId::getModel
 * @return
 */
QSqlRelationalTableModel* Employer_EmployerId::getModel()
{
    //Check if model isn't created create it
    if (!model) {
        model = new QSqlRelationalTableModel(NULL, db);
        model->setTable(tableName);
        model->select();
    }

    return model;
}
