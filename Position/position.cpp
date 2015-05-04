#include "Position/position.h"
#include <QObject>
#include <QException>
#include <QMessageBox>
#include <QSqlError>

Position* Position::position = NULL;

/**
 * Create singleton object of Position
 *
 * @brief Position::create
 * @param dbConnection
 * @param mainWindow
 * @return
 */
Position* Position::create(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    if (!position) {
        position = new Position(dbConnection, mainWindow);
    }

    return position;
}

/**
 * @brief Position::Position
 */
Position::Position(QSqlDatabase dbConnection, QMainWindow *mainWindow):
    EditableEntity(dbConnection, mainWindow)
{
    tableName   = "position";
    add_position = NULL;
}

/**
 * @brief Position::initAddPosition
 * @return
 */
addDialog* Position::getAddDialog()
{
    add_position = add_position ? add_position : new addPosition(getModel());
    return add_position;
}

/**
 * @brief Position::setTableViewModel
 */
void Position::setTableViewModel()
{
    EditableEntity::setTableViewModel();

    getModel()->setHeaderData(0,  Qt::Horizontal, "ID");
    getModel()->setHeaderData(1,  Qt::Horizontal, "Անվանում");
    getModel()->setHeaderData(2,  Qt::Horizontal, "Գրաֆիկ");

}
