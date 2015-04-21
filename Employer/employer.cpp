#include "Employer/employer.h"
#include <QException>
#include <QSqlRelation>
#include <QObject>


#include <QModelIndexList>
#include <QMessageBox>


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
    tableView    = new QTableView(mainWindow);
    addButton    = new QPushButton("Ավելացնել");
    editButton   = new QPushButton("Խմբագրել");
    removeButton = new QPushButton("Հեռացնել");
    mainLayout   = new QGridLayout;

    //Arrange widgets on window
    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(editButton, 0, 2, 1, 2);
    mainLayout->addWidget(removeButton, 0, 4, 1, 2);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
    parent->centralWidget()->setLayout(mainLayout);

    //Set tableView content
    tableView->setModel(getModel());
    tableView->resizeColumnsToContents();

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
    QObject::connect(addButton,    SIGNAL(clicked()), add_employer, SLOT(initialize()));
    QObject::connect(editButton,   SIGNAL(clicked()), this, SLOT(edit()));
    QObject::connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));

    QObject::connect(tableView, SIGNAL(pressed(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(selectRow(QModelIndex)));

//    QObject::connect(tableView, SIGNAL(doubleClicked(QModelIndex)), add_employer, SLOT(initialize(QModelIndex)));

    //Connect mainWindow destroy with removeWidgets to remove dynamic objects
    QObject::connect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}

/**
 * @brief Employer::selectRow
 * @param modelIndex
 */
void Employer::selectRow(const QModelIndex &modelIndex) {
    tableView->selectRow(modelIndex.row());
}

/**
 * @brief Employer::edit
 */
void Employer::edit()
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

    add_employer->initByRowNumber(selectedRows.at(0).row());
}

/**
 * @brief Employer::remove
 */
void Employer::remove()
{
//    QModelIndexList selectedRows = tableView->selectionModel()->selectedRows();
//    for( int i = 0; i < selectedRows.count(); i++)
//            QMessageBox::information(this,"", QString::number(selectedRows.at(i).row()));
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
//        model->setRelation(14, QSqlRelation("address", "id", "street"));
//        model->setRelation(15, QSqlRelation("address", "id", "street"));
        model->setRelation(17, QSqlRelation("department", "id", "name"));

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
    delete editButton;
    delete removeButton;

    tableView    = NULL;
    addButton    = NULL;
    mainLayout   = NULL;
    editButton   = NULL;
    removeButton = NULL;

    QObject::disconnect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}
