#include "viewchangableentity.h"
#include <QObject>
#include <QException>
#include <QMessageBox>
#include <QComboBox>
#include <QDebug>
#include <QSqlError>
#include <QScrollBar>


/**
 * @brief ViewChangableEntity::ViewChangableEntity
 */
ViewChangableEntity::ViewChangableEntity(QSqlDatabase dbConnection, QMainWindow *mainWindow):
    EditableEntity(dbConnection, mainWindow)
{
    viewModel = NULL;
}


void ViewChangableEntity::setTableViewModel()
{
    //Set tableView content
    tableView->setModel(getViewModel());
    tableView->resizeColumnsToContents();
}



/**
 * @brief ViewChangableEntity::getModel
 * @return
 */
QSqlRelationalTableModel* ViewChangableEntity::getModel()
{
    //Check if model isn't created create it
    if (!model) {
        model = new QSqlRelationalTableModel(parent, db);
        model->setTable(tableName);
        model->select();

        viewModel = new QSqlQueryModel;
        updateViewModel();
    }

    return model;
}

/**
 * @brief ViewChangableEntity::getViewModel
 * @return
 */
QSqlQueryModel* ViewChangableEntity::getViewModel()
{
    if (!viewModel){
        getModel();
    }

    return viewModel;
}

