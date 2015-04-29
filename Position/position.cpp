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
Position::Position(QSqlDatabase dbConnection, QMainWindow *mainWindow) {
    model       = NULL;
    db          = dbConnection;
    parent      = mainWindow;
    tableName   = "position";

    add_position = NULL;

    errorLabel   = NULL;
    tableView    = NULL;
    mainLayout   = NULL;

    addButton    = NULL;
    editButton   = NULL;
    removeButton = NULL;
}

/**
 * @brief Position::select
 * @param mainWindow
 */
void Position::select(QMainWindow *mainWindow)
{
    if (mainWindow) {
        parent = mainWindow;
    }
    if (!parent) {
        throw new QException();
    }

    //Create widgets
    errorLabel   = errorLabel   ? errorLabel   : new QLabel;
    tableView    = tableView    ? tableView    : new QTableView();
    mainLayout   = mainLayout   ? mainLayout   : new QGridLayout;

    addButton    = addButton    ? addButton    : new QPushButton("Ավելացնել Պաշտոն");
    editButton   = editButton   ? editButton   : new QPushButton("Խմբագրել");
    removeButton = removeButton ? removeButton : new QPushButton("Հեռացնել");

    //Arrange widgets on window
    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(editButton, 0, 2, 1, 2);
    mainLayout->addWidget(removeButton, 0, 4, 1, 2);
    mainLayout->addWidget(errorLabel, 0, 7, 1, 8);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
    parent->centralWidget()->setLayout(mainLayout);

    //Set tableView content
    tableView->setModel(getModel());

    //Create addPosition instance
    getAddPosition();

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton,    SIGNAL(clicked()), add_position, SLOT(initialize()));
    QObject::connect(editButton,   SIGNAL(clicked()), this, SLOT(edit()));
    QObject::connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));

    QObject::connect(tableView,    SIGNAL(pressed(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView,    SIGNAL(clicked(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView,    SIGNAL(doubleClicked(QModelIndex)), add_position, SLOT(initialize(QModelIndex)));

    QObject::connect(parent,       SIGNAL(destroyed()), this,  SLOT(destroy()));
}

/**
 * @brief Position::selectRow
 * @param modelIndex
 */
void Position::selectRow(const QModelIndex &modelIndex) {
    tableView->selectRow(modelIndex.row());
}

/**
 * @brief Position::edit
 */
void Position::edit()
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

    add_position->initByRowNumber(selectedRows.at(0).row());
}

/**
 * @brief Position::remove
 */
void Position::remove()
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
 * @brief Position::getModel
 * @return
 */
QSqlRelationalTableModel* Position::getModel()
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
void Position::destroy()
{
    delete tableView;
    delete mainLayout;

    delete addButton;
    delete editButton;
    delete removeButton;

    tableView    = NULL;
    mainLayout   = NULL;

    addButton    = NULL;
    editButton   = NULL;
    removeButton = NULL;

    QObject::disconnect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}

/**
 * @brief Position::initAddPosition
 * @return
 */
addPosition* Position::getAddPosition()
{
    add_position = add_position ? add_position : new addPosition(getModel());
    return add_position;
}
