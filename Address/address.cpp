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
 * @brief Address::Address
 */
Address::Address(QSqlDatabase dbConnection, QMainWindow *mainWindow) {
    model       = NULL;
    db          = dbConnection;
    parent      = mainWindow;
    tableName   = "address";

    errorLabel   = NULL;
    tableView    = NULL;
    mainLayout   = NULL;
    add_address  = NULL;

    addButton    = NULL;
    editButton   = NULL;
    removeButton = NULL;
}

/**
 * @brief Address::select
 * @param mainWindow
 */
void Address::select(QMainWindow *mainWindow)
{
    if (mainWindow) {
        parent = mainWindow;
    }
    if (!parent) {
        throw new QException();
    }

    //Create widgets
    tableView    = tableView    ? tableView    : new QTableView();
    mainLayout   = mainLayout   ? mainLayout   : new QGridLayout;
    errorLabel   = errorLabel   ? errorLabel   : new QLabel();
    addButton    = addButton    ? addButton    : new QPushButton("Ավելացնել Հասցե");
    editButton   = editButton   ? editButton   : new QPushButton("Խմբագրել");
    removeButton = removeButton ? removeButton : new QPushButton("Հեռացնել");

    //Arrange widgets on window
    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
    mainLayout->addWidget(editButton, 0, 2, 1, 2);
    mainLayout->addWidget(removeButton, 0, 4, 1, 2);
    mainLayout->addWidget(errorLabel, 0, 7, 1, 8);
    parent->centralWidget()->setLayout(mainLayout);

    //Set tableView content
    tableView->setModel(getModel());

    //Create addAddress instance
    getAddAddress();

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton, SIGNAL(clicked()), add_address, SLOT(initialize()));
    QObject::connect(editButton,   SIGNAL(clicked()), this, SLOT(edit()));
    QObject::connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));

    QObject::connect(tableView, SIGNAL(pressed(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView, SIGNAL(doubleClicked(QModelIndex)), add_address, SLOT(initialize(QModelIndex)));

    //Connect parent destroy with removeWidgets to remove dynamic objects
    QObject::connect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}


/**
 * @brief Address::selectRow
 * @param modelIndex
 */
void Address::selectRow(const QModelIndex &modelIndex) {
    tableView->selectRow(modelIndex.row());
}

/**
 * @brief Address::edit
 */
void Address::edit()
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

    add_address->initByRowNumber(selectedRows.at(0).row());
}

/**
 * @brief Address::remove
 */
void Address::remove()
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
 * @brief Address::getModel
 * @return
 */
QSqlRelationalTableModel* Address::getModel()
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
 * @brief Address::destroy
 */
void Address::destroy()
{
    delete tableView;
    delete mainLayout;
    delete errorLabel;

    delete addButton;
    delete editButton;
    delete removeButton;

    tableView    = NULL;
    mainLayout   = NULL;
    errorLabel   = NULL;

    addButton    = NULL;
    editButton   = NULL;
    removeButton = NULL;

    QObject::disconnect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}

/**
 * @brief Address::initAddAddress
 * @return
 */
addAddress* Address::getAddAddress()
{
    add_address = add_address ? add_address : new addAddress(getModel());
    return add_address;
}
