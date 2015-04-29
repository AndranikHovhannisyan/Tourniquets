#include "editableentity.h"
#include <QObject>
#include <QException>
#include <QMessageBox>
#include <QSqlError>


/**
 * @brief EditableEntity::EditableEntity
 * @param dbConnection
 * @param mainWindow
 */
EditableEntity::EditableEntity(QSqlDatabase dbConnection, QMainWindow *mainWindow) {
    model       = NULL;
    db          = dbConnection;
    parent      = mainWindow;

    errorLabel   = NULL;
    tableView    = NULL;
    mainLayout   = NULL;

    addButton    = NULL;
    editButton   = NULL;
    removeButton = NULL;
}

/**
 * @brief EditableEntity::select
 * @param mainWindow
 */
void EditableEntity::select(QMainWindow *mainWindow)
{
    if (mainWindow) {
        parent = mainWindow;
    }
    if (!parent) {
        throw new QException();
    }

    //Create widgets
    createWidgets();

    //Arrange widgets on window
    setWidgetsInLayout();

    parent->centralWidget()->setLayout(mainLayout);

    //Set tableView content
    setTableViewModel();

    //Create addDialog instance
    getAddDialog();

    //Connect add new and edit SIGNAL / SLOTS
    setSignalSlotConnections();
}


//************************************ Select parts ***************************************

/**
 * @brief EditableEntity::createWidgets
 */
void EditableEntity::createWidgets()
{
    errorLabel   = errorLabel   ? errorLabel   : new QLabel;
    tableView    = tableView    ? tableView    : new QTableView();
    mainLayout   = mainLayout   ? mainLayout   : new QGridLayout;

    addButton    = addButton    ? addButton    : new QPushButton("Ավելացնել");
    editButton   = editButton   ? editButton   : new QPushButton("Խմբագրել");
    removeButton = removeButton ? removeButton : new QPushButton("Հեռացնել");
}

/**
 * @brief EditableEntity::setWidgetsInLayout
 */
void EditableEntity::setWidgetsInLayout()
{
    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(editButton, 0, 2, 1, 2);
    mainLayout->addWidget(removeButton, 0, 4, 1, 2);
    mainLayout->addWidget(errorLabel, 0, 7, 1, 8);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
}

/**
 * @brief EditableEntity::setTableViewModel
 */
void EditableEntity::setTableViewModel()
{
    tableView->setModel(getModel());
}

/**
 * @brief EditableEntity::setSignalSlotConnections
 */
void EditableEntity::setSignalSlotConnections()
{
    QObject::connect(addButton,    SIGNAL(clicked()),                  getAddDialog(), SLOT(initialize()));
    QObject::connect(editButton,   SIGNAL(clicked()),                  this,           SLOT(edit()));
    QObject::connect(removeButton, SIGNAL(clicked()),                  this,           SLOT(remove()));

    QObject::connect(tableView,    SIGNAL(pressed(QModelIndex)),       this,           SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView,    SIGNAL(clicked(QModelIndex)),       this,           SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView,    SIGNAL(doubleClicked(QModelIndex)), getAddDialog(), SLOT(initialize(QModelIndex)));

    QObject::connect(parent,       SIGNAL(destroyed()),                this,           SLOT(destroy()));
}


//**************************** Create/edit/delete button slots ****************************

/**
 * @brief EditableEntity::selectRow
 * @param modelIndex
 */
void EditableEntity::selectRow(const QModelIndex &modelIndex) {
    tableView->selectRow(modelIndex.row());
}

/**
 * @brief EditableEntity::edit
 */
void EditableEntity::edit()
{
    QModelIndexList selectedRows = tableView->selectionModel()->selectedRows();
    if (selectedRows.count() == 0) {
        QMessageBox::warning(NULL, "Error", "Ոչ մի տող նշված չէ");
        return;
    }

    if (selectedRows.count() > 1) {
        QMessageBox::warning(NULL, "Error", "Խմբագրման համար անհրաժեշտ է նշել ճիշտ մեկ տող");
        return;
    }

    getAddDialog()->initByRowNumber(selectedRows.at(0).row());
}

/**
 * @brief EditableEntity::remove
 */
void EditableEntity::remove()
{
    QModelIndexList selectedRows = tableView->selectionModel()->selectedRows();
    for( int i = 0; i < selectedRows.count(); i++) {
        getModel()->removeRow(selectedRows.at(i).row());

        errorLabel->setText(getModel()->lastError().text());
        errorLabel->setStyleSheet("QLabel { color: red; font: 8pt; }");
        errorLabel->setWordWrap(true);
    }

    getModel()->select();
}


/**
 * @brief EditableEntity::getModel
 * @return
 */
QSqlRelationalTableModel* EditableEntity::getModel()
{
    //Check if model isn't created create it
    if (!model) {
        model = new QSqlRelationalTableModel(parent, db);
        model->setTable(tableName);
        model->select();
    }

    return model;
}

/**
 * @brief Position::destroy
 */
void EditableEntity::destroy()
{
    delete errorLabel;
    delete tableView;
    delete mainLayout;

    delete addButton;
    delete editButton;
    delete removeButton;

    errorLabel   = NULL;
    tableView    = NULL;
    mainLayout   = NULL;

    addButton    = NULL;
    editButton   = NULL;
    removeButton = NULL;

    QObject::disconnect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}
