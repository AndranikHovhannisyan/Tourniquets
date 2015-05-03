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

/**
 * @brief ViewChangableEntity::setTableViewModel
 */
void ViewChangableEntity::setTableViewModel()
{
    EditableEntity::setTableViewModel();

    //Set tableView content
    tableView->setModel(getViewModel());
}

/**
 * @brief ViewChangableEntity::setSignalSlotConnections
 */
void ViewChangableEntity::setSignalSlotConnections()
{
    EditableEntity::setSignalSlotConnections();

    QObject::connect(getModel(), SIGNAL(primeInsert(int,QSqlRecord&)), this, SLOT(updateView(int,QSqlRecord&)));
    QObject::connect(getModel(), SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(updateView(QModelIndex,QModelIndex)));
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

/**
 * @brief ViewChangableEntity::updateViewModel
 */
void ViewChangableEntity::updateViewModel()
{
    errorLabel->setText(getModel()->lastError().text());
    errorLabel->setStyleSheet("QLabel { color: red; font: 8pt; }");
    errorLabel->setWordWrap(true);
}

