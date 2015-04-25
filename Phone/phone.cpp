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
Phone::Phone(QSqlDatabase dbConnection, QMainWindow *mainWindow) {
    model       = NULL;
    db          = dbConnection;
    parent      = mainWindow;
    tableName   = "employer_phone_number";
}

/**
 * @brief Phone::select
 * @param mainWindow
 */
void Phone::select(QMainWindow *mainWindow)
{
    if (mainWindow) {
        parent = mainWindow;
    }
    if (!parent) {
        throw new QException();
    }

    //Create widgets
    tableView   = new QTableView(mainWindow);
    addButton   = new QPushButton("Ավելացնել Բաժին");
    mainLayout  = new QGridLayout;

    //Arrange widgets on window
    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
    parent->centralWidget()->setLayout(mainLayout);

    //Set tableView content
    tableView->setModel(getModel());

    //Create addPhone instance
    add_phone = new addPhone(getModel());

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton, SIGNAL(clicked()), add_phone, SLOT(initialize()));
    QObject::connect(tableView, SIGNAL(doubleClicked(QModelIndex)), add_phone, SLOT(initialize(QModelIndex)));

    //Connect mainWindow destroy with removeWidgets to remove dynamic objects
    QObject::connect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}

/**
 * @brief Phone::getModel
 * @return
 */
QSqlRelationalTableModel* Phone::getModel()
{
    //Check if model isn't created create it
    if (!model) {
        model = new QSqlRelationalTableModel(parent, db);
        model->setTable(tableName);
    }

    model->setFilter("");
    model->select();

    return model;
}

/**
 * @brief Phone::destroy
 */
void Phone::destroy()
{
    delete tableView;
    delete addButton;
    delete mainLayout;

    tableView  = NULL;
    addButton  = NULL;
    mainLayout = NULL;

    QObject::disconnect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}
