#include "Employer/employer.h"
#include <QException>
#include <QObject>


Employer* Employer::employer = NULL;

/**
 * Create singleton object of Employer
 *
 * @brief Employer::create
 * @param dbConnection
 * @param mainWindow
 * @return
 */
Employer* Employer::create(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    if (!employer) {
        employer = new Employer(dbConnection, mainWindow);
    }

    return employer;
}

/**
 * @brief Employer::Employer
 */
Employer::Employer(QSqlDatabase dbConnection, QMainWindow *mainWindow) {
    model       = NULL;
    db          = dbConnection;
    parent      = mainWindow;
    tableName   = "employer";
}

/**
 * @brief Employer::select
 * @param mainWindow
 */
void Employer::select(QMainWindow *mainWindow)
{
    if (mainWindow) {
        parent = mainWindow;
    }
    if (!parent) {
        throw new QException();
    }

    //Create widgets
    tableView   = new QTableView(mainWindow);
    addButton   = new QPushButton("Ավելացնել աշխատակից");
    mainLayout  = new QGridLayout;

    //Arrange widgets on window
    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
    parent->centralWidget()->setLayout(mainLayout);

    //Set tableView content
    tableView->setModel(getModel());

    getModel()->setHeaderData(1,  Qt::Horizontal, "Անուն");
    getModel()->setHeaderData(2,  Qt::Horizontal, "Ազգանուն");
    getModel()->setHeaderData(3,  Qt::Horizontal, "Հայրանուն");
    getModel()->setHeaderData(4,  Qt::Horizontal, "Ծննդյան ամսաթիվ");
    getModel()->setHeaderData(5,  Qt::Horizontal, "Անձնագրի սերիա");
    getModel()->setHeaderData(6,  Qt::Horizontal, "Անձնագրի համար");
    getModel()->setHeaderData(7,  Qt::Horizontal, "Տրման ամսաթիվ");
    getModel()->setHeaderData(8,  Qt::Horizontal, "Ում կողմից");
    getModel()->setHeaderData(9,  Qt::Horizontal, "Սեռը");
    getModel()->setHeaderData(10, Qt::Horizontal, "Զինապարտություն");
    getModel()->setHeaderData(11, Qt::Horizontal, "Ընտանեկան վիճակ");
    getModel()->setHeaderData(12, Qt::Horizontal, "Երեխաների քանակ");
    getModel()->setHeaderData(13, Qt::Horizontal, "Անչափահաս երեխաների քանակ");
    getModel()->setHeaderData(14, Qt::Horizontal, "Գրանցման հասցե");
    getModel()->setHeaderData(15, Qt::Horizontal, "Բնակության հասցե");
    getModel()->setHeaderData(16, Qt::Horizontal, "Գրաֆիկ");
    getModel()->setHeaderData(17, Qt::Horizontal, "Բաժին");



    tableView->hideColumn(0);



    //Create addEmployer instance
    add_employer = new addEmployer(getModel());

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton, SIGNAL(clicked()), add_employer, SLOT(initialize()));
    QObject::connect(tableView, SIGNAL(doubleClicked(QModelIndex)), add_employer, SLOT(initialize(QModelIndex)));

    //Connect mainWindow destroy with removeWidgets to remove dynamic objects
    QObject::connect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}

/**
 * @brief Employer::getModel
 * @return
 */
QSqlRelationalTableModel* Employer::getModel()
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
 * @brief Employer::destroy
 */
void Employer::destroy()
{
    delete tableView;
    delete addButton;
    delete mainLayout;

    tableView  = NULL;
    addButton  = NULL;
    mainLayout = NULL;

    QObject::disconnect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}
