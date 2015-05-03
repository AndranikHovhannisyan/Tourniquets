#include "Phone/phone.h"
#include <QException>
#include <QObject>


Phone* Phone::phone = NULL;

/**
 * Create singleton object of Phone
 *
 * @brief Phone::create
 * @param dbConnection
 * @param mainWindow
 * @return
 */
Phone* Phone::create(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    if (!phone) {
        phone = new Phone(dbConnection, mainWindow);
    }

    return phone;
}

/**
 * @brief Phone::Phone
 */
Phone::Phone(QSqlDatabase dbConnection, QMainWindow *mainWindow):
    ViewChangableEntity(dbConnection, mainWindow)
{
    tableName = "employer_phone_number";
    add_phone = NULL;
}

/**
 * @brief Phone::getAddDialog
 * @return
 */
addDialog* Phone::getAddDialog()
{
    add_phone = add_phone ? add_phone : new addPhone(getModel());
    return add_phone;
}

/**
 * @brief Phone::updateViewModel
 */
void Phone::updateViewModel()
{
    ViewChangableEntity::updateViewModel();

    viewModel->setQuery("SELECT CONCAT(e.firstname, ' ', e.lastname) as employer, epn.phone_number, epn.from, epn.to "\
                        "FROM employer_phone_number as epn "\
                        "JOIN employer as e ON e.id = epn.employer_id");

    viewModel->setHeaderData(0,  Qt::Horizontal, "Աշխատակից");
    viewModel->setHeaderData(1,  Qt::Horizontal, "Հեռախոսահամար");
}
