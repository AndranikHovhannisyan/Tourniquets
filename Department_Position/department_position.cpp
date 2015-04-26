#include "Department_Position/department_position.h"

#include <QObject>
#include <QException>

Department_Position* Department_Position::department_position = NULL;

/**
 * Create singleton object of Department_Position
 *
 * @brief Department_Position::create
 * @param dbConnection
 * @param mainWindow
 * @return
 */
Department_Position* Department_Position::create(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    if (!department_position) {
        department_position = new Department_Position(dbConnection, mainWindow);
    }

    return department_position;
}

/**
 * @brief Department_Position::Department_Position
 */
Department_Position::Department_Position(QSqlDatabase dbConnection) {
    model       = NULL;
    db          = dbConnection;
    tableName   = "dep_position";
}

/**
 * @brief Department::getModel
 * @return
 */
QSqlRelationalTableModel* Department_Position::getModel()
{
    //Check if model isn't created create it
    if (!model) {
        model = new QSqlRelationalTableModel(NULL, db);
        model->setTable(tableName);
        model->select();
    }

    return model;
}
