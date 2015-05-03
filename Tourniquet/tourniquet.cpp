#include "Tourniquet/tourniquet.h"
#include <QException>
#include <QObject>


Tourniquet* Tourniquet::tourniquet = NULL;

/**
 * Create singleton object of Tourniquet
 *
 * @brief Tourniquet::create
 * @param dbConnection
 * @param mainWindow
 * @return
 */
Tourniquet* Tourniquet::create(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    if (!tourniquet) {
        tourniquet = new Tourniquet(dbConnection, mainWindow);
    }

    return tourniquet;
}

/**
 * @brief Tourniquet::Tourniquet
 */
Tourniquet::Tourniquet(QSqlDatabase dbConnection, QMainWindow *mainWindow):
    ViewChangableEntity(dbConnection, mainWindow)
{
    tableName   = "tourniquet";
    add_tourniquet = NULL;
}

/**
 * @brief Tourniquet::getAddDialog
 * @return
 */
addDialog* Tourniquet::getAddDialog()
{
    add_tourniquet = add_tourniquet ? add_tourniquet : new addTourniquet(getModel());
    return add_tourniquet;
}

/**
 * @brief Tourniquet::updateViewModel
 */
void Tourniquet::updateViewModel()
{
    viewModel->setQuery("SELECT * FROM tourniquet as t");
}

