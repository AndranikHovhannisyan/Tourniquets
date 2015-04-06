#include "Phone/phone.h"
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
Phone* Phone::create(QSqlDatabase* dbConnection, QMainWindow *mainWindow)
{
    if (!phone) {
        phone = new Phone(dbConnection, mainWindow);
    }

    return phone;
}

/**
 * @brief Phone::Phone
 */
Phone::Phone(QSqlDatabase* dbConnection, QMainWindow *mainWindow) {
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
    //Create widgets
    tableView   = new QTableView(mainWindow);
    addButton   = new QPushButton("Ավելացնել Բաժին");
    mainLayout  = new QGridLayout;

    //Arrange widgets on window
    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
    mainWindow->centralWidget()->setLayout(mainLayout);

    //Set tableView content
    tableView->setModel(getModel());

    //Create addPhone instance
    add_phone = new addPhone(getModel());

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton, SIGNAL(clicked()), add_phone, SLOT(initialize()));
    QObject::connect(tableView, SIGNAL(doubleClicked(QModelIndex)), add_phone, SLOT(initialize(QModelIndex)));

    //Connect mainWindow destroy with removeWidgets to remove dynamic objects
    QObject::connect(mainWindow, SIGNAL(destroyed()), tableView,  SLOT(deleteLater()));
    QObject::connect(mainWindow, SIGNAL(destroyed()), addButton,  SLOT(deleteLater()));
    QObject::connect(mainWindow, SIGNAL(destroyed()), mainLayout, SLOT(deleteLater()));
}

/**
 * @brief Phone::getModel
 * @return
 */
QSqlRelationalTableModel* Phone::getModel()
{
    //Check if model isn't created create it
    if (!model) {
        model = new QSqlRelationalTableModel(parent, *db);
        model->setTable(tableName);
        model->select();
    }

    return model;
}
