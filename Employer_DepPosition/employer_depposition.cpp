#include "Employer_DepPosition/employer_depposition.h"
#include <QObject>
#include <QException>

Employer_DepPosition* Employer_DepPosition::employer_depposition = NULL;

/**
 * Create singleton object of Employer_DepPosition
 *
 * @brief Employer_DepPosition::create
 * @param dbConnection
 * @return
 */
Employer_DepPosition* Employer_DepPosition::create(QSqlDatabase dbConnection)
{
    if (!employer_depposition) {
        employer_depposition = new Employer_DepPosition(dbConnection);
    }

    return employer_depposition;
}

/**
 * @brief Employer_DepPosition::Employer_DepPosition
 */
Employer_DepPosition::Employer_DepPosition(QSqlDatabase dbConnection) {
    model       = NULL;
    db          = dbConnection;
    tableName   = "employer_dep_positions";
}

/**
 * @brief Employer_DepPosition::getModel
 * @return
 */
QSqlRelationalTableModel* Employer_DepPosition::getModel()
{
    //Check if model isn't created create it
    if (!model) {
        model = new QSqlRelationalTableModel(NULL, db);
        model->setTable(tableName);
        model->select();
    }

    return model;
}
