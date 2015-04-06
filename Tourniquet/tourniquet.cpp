#include "Tourniquet/tourniquet.h"
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
Tourniquet* Tourniquet::create(QSqlDatabase* dbConnection, QMainWindow *mainWindow)
{
    if (!tourniquet) {
        tourniquet = new Tourniquet(dbConnection, mainWindow);
    }

    return tourniquet;
}

/**
 * @brief Tourniquet::Tourniquet
 */
Tourniquet::Tourniquet(QSqlDatabase* dbConnection, QMainWindow *mainWindow) {
    model       = NULL;
    db          = dbConnection;
    parent      = mainWindow;
    tableName   = "tourniquet";
}

/**
 * @brief Tourniquet::select
 * @param mainWindow
 */
void Tourniquet::select(QMainWindow *mainWindow)
{
    //Create widgets
    tableView   = new QTableView(mainWindow);
    addButton   = new QPushButton("Ավելացնել Գրաֆիկ");
    mainLayout  = new QGridLayout;

    //Arrange widgets on window
    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
    mainWindow->centralWidget()->setLayout(mainLayout);

    //Set tableView content
    tableView->setModel(getModel());

    //Create addTourniquet instance
    add_tourniquet = new addTourniquet(getModel());

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton, SIGNAL(clicked()), add_tourniquet, SLOT(initialize()));
    QObject::connect(tableView, SIGNAL(doubleClicked(QModelIndex)), add_tourniquet, SLOT(initialize(QModelIndex)));

    //Connect mainWindow destroy with removeWidgets to remove dynamic objects
    QObject::connect(mainWindow, SIGNAL(destroyed()), tableView,  SLOT(deleteLater()));
    QObject::connect(mainWindow, SIGNAL(destroyed()), addButton,  SLOT(deleteLater()));
    QObject::connect(mainWindow, SIGNAL(destroyed()), mainLayout, SLOT(deleteLater()));
}

/**
 * @brief Tourniquet::getModel
 * @return
 */
QSqlRelationalTableModel* Tourniquet::getModel()
{
    //Check if model isn't created create it
    if (!model) {
        model = new QSqlRelationalTableModel(parent, *db);
        model->setTable(tableName);
        model->select();
    }

    return model;
}
