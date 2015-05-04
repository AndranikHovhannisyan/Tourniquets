#include "address.h"
#include <QObject>
#include <QException>
#include <QMessageBox>
#include <QSqlError>

Address* Address::address = NULL;

/**
 * Create singleton object of Address
 *
 * @brief Address::create
 * @param dbConnection
 * @return
 */
Address* Address::create(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    if (!address) {
        address = new Address(dbConnection, mainWindow);
    }

    return address;
}

/**
 * @brief Address::setTableViewModel
 */
void Address::setTableViewModel()
{
    EditableEntity::setTableViewModel();

    getModel()->setHeaderData(0,  Qt::Horizontal, "ID");
    getModel()->setHeaderData(1,  Qt::Horizontal, "Երկիր");
    getModel()->setHeaderData(2,  Qt::Horizontal, "Քաղաք");
    getModel()->setHeaderData(3,  Qt::Horizontal, "Փողոց");
    getModel()->setHeaderData(4,  Qt::Horizontal, "Համար");
}


/**
 * @brief Address::Address
 */
Address::Address(QSqlDatabase dbConnection, QMainWindow *mainWindow):
    EditableEntity(dbConnection, mainWindow)
{
    tableName   = "address";
    add_address  = NULL;
}

/**
 * @brief Address::getAddDialog
 * @return
 */
addDialog* Address::getAddDialog()
{
    add_address = add_address ? add_address : new addAddress(getModel());
    return add_address;
}
