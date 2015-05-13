#include "Report/report.h"
#include "Department/department.h"
#include "Employer/employer.h"
#include <QException>

Report* Report::report = NULL;

/**
 * Create singleton object of Report
 *
 * @brief Report::create
 * @param dbConnection
 * @param mainWindow
 * @return
 */
Report* Report::create(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    if (!report) {
        report = new Report(dbConnection, mainWindow);
    }

    return report;
}

/**
 * @brief Report::Report
 * @param dbConnection
 * @param mainWindow
 */
Report::Report(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    model       = NULL;
    db          = dbConnection;
    parent      = mainWindow;
    tableView   = NULL;
    mainLayout  = NULL;
    errorLabel  = NULL;

    departments = NULL;
    employers   = NULL;
    dateFrom    = NULL;
    dateTo      = NULL;

    filterButton = NULL;
    cancelFilterButton = NULL;
}

/**
 * @brief Report::select
 * @param mainWindow
 */
void Report::select(QMainWindow *mainWindow)
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

    departments  = departments  ? departments  : new QComboBox;
    employers    = employers    ? employers    : new QComboBox;
    dateFrom     = dateFrom     ? dateFrom     : new QDateEdit;
    dateTo       = dateTo       ? dateTo       : new QDateEdit;

    filterButton = filterButton ? filterButton : new QPushButton("Ֆիլտրել");
    cancelFilterButton = cancelFilterButton ? cancelFilterButton : new QPushButton("Չեղարկել");

    //Arrange widgets on window
    mainLayout->addWidget(departments, 0, 0, 1, 2);
    mainLayout->addWidget(employers, 0, 2, 1, 2);
    mainLayout->addWidget(dateFrom, 0, 4, 1, 2);
    mainLayout->addWidget(dateTo, 0, 6, 1, 2);
    mainLayout->addWidget(filterButton, 0, 8, 1, 2);
    mainLayout->addWidget(cancelFilterButton, 0, 10, 1, 2);

    mainLayout->addWidget(tableView, 1, 0, 15, 15);

    parent->centralWidget()->setLayout(mainLayout);

    departments->setModel(Department::create(db)->getModel());
    departments->setModelColumn(1);

    employers->setModel(Employer::create(db)->getModel());
    employers->setModelColumn(1);

    cancelFilter();

    tableView->setModel(getModel());
    tableView->resizeColumnsToContents();

    QObject::connect(filterButton, SIGNAL(clicked()), this, SLOT(filter()));
    QObject::connect(cancelFilterButton, SIGNAL(clicked()), this, SLOT(cancelFilter()));

    QObject::connect(tableView, SIGNAL(pressed(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    QObject::connect(parent,    SIGNAL(destroyed()),          this, SLOT(destroy()));
}

/**
 * @brief Report::destroy
 */
void Report::destroy()
{
    delete tableView;
    delete mainLayout;

    delete departments;
    delete employers;
    delete dateFrom;
    delete dateTo;
    delete filterButton;
    delete cancelFilterButton;

    tableView    = NULL;
    mainLayout   = NULL;

    departments  = NULL;
    employers    = NULL;
    dateFrom     = NULL;
    dateTo       = NULL;
    filterButton = NULL;
    cancelFilterButton = NULL;
}

/**
 * @brief Report::selectRow
 * @param modelIndex
 */
void Report::selectRow(const QModelIndex &modelIndex) {
    tableView->selectRow(modelIndex.row());
}

#include <QDebug>
#include <QSqlError>

/**
 * @brief Report::setModel
 */
void Report::filter(){

    int departmentId = Department::create(db)->getModel()
                                    ->record(departments->currentIndex())
                                    .value("id").toInt();

    int employerId = Employer::create(db)->getModel()
                                    ->record(employers->currentIndex())
                                    .value("id").toInt();

    QDate from = dateFrom->date();
    QDate to   = dateTo->date();

    getModel()->setQuery("CALL statistic(" + QString::number(departmentId) + ", " + QString::number(employerId) +
                    ", '" + from.toString("yyyy-M-d") + "', '" + to.toString("yyyy-M-d") + "')");

    getModel()->setHeaderData(0,  Qt::Horizontal, "Բաժնի անունը");
    getModel()->setHeaderData(1,  Qt::Horizontal, "Անուն ազգանուն");
    getModel()->setHeaderData(2,  Qt::Horizontal, "Օրը");
    getModel()->setHeaderData(3,  Qt::Horizontal, "Եկել է");
    getModel()->setHeaderData(4,  Qt::Horizontal, "Գնացել է");
    getModel()->setHeaderData(5,  Qt::Horizontal, "Աշխատած ժամանակը");
    getModel()->setHeaderData(6,  Qt::Horizontal, "ՈՒշ է եկել");
    getModel()->setHeaderData(7,  Qt::Horizontal, "Շուտ է եկել");
    getModel()->setHeaderData(8,  Qt::Horizontal, "Շուտ է դուրս եկել");
    getModel()->setHeaderData(9,  Qt::Horizontal, "Ուշ է դուրս եկել");
}

/**
 * @brief Report::cancelFilter
 */
void Report::cancelFilter()
{
    departments->setCurrentIndex(-1);
    employers->setCurrentIndex(-1);
    dateFrom->setDate(QDate(QDate::currentDate().year(), 1, 1));
    dateTo->setDate(QDate(QDate::currentDate().year() + 1, 1, 1));

    filter();
}

/**
 * @brief Report::getModel
 * @return
 */
QSqlQueryModel* Report::getModel()
{
    //Check if model isn't created create it
    if (!model) {
        model = new QSqlQueryModel();
        filter();
    }

    return model;
}