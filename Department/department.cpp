#include "Department/department.h"
#include <QObject>
#include <QException>
#include <QMessageBox>
#include <QComboBox>
#include <QDebug>
#include <QSqlError>
#include <QScrollBar>

Department* Department::department = NULL;

/**
 * Create singleton object of Department
 *
 * @brief Department::create
 * @param dbConnection
 * @param mainWindow
 * @return
 */
Department* Department::create(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    if (!department) {
        department = new Department(dbConnection, mainWindow);
    }

    return department;
}

/**
 * @brief Department::Department
 */
Department::Department(QSqlDatabase dbConnection, QMainWindow *mainWindow) {
    model           = NULL;
    viewModel       = NULL;
    db              = dbConnection;
    parent          = mainWindow;
    tableName       = "department";

    errorLabel      = NULL;

    tableView       = NULL;
    addButton       = NULL;
    editButton      = NULL;
    removeButton    = NULL;
    mainLayout      = NULL;
    add_department  = NULL;

    positions       = NULL;
    positions_label = NULL;
}

/**
 * @brief Department::select
 * @param mainWindow
 */
void Department::select(QMainWindow *mainWindow)
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
    tableView->setFixedWidth(520);
    mainLayout   = mainLayout   ? mainLayout   : new QGridLayout;

    addButton    = addButton    ? addButton    : new QPushButton("Ավելացնել Բաժին");
    editButton   = editButton   ? editButton   : new QPushButton("Խմբագրել");
    removeButton = removeButton ? removeButton : new QPushButton("Հեռացնել");

    //Arrange widgets on window
    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(editButton, 0, 2, 1, 2);
    mainLayout->addWidget(removeButton, 0, 4, 1, 2);
    mainLayout->addWidget(errorLabel, 0, 7, 1, 8);
    mainLayout->addWidget(tableView, 1, 0, 15, 6);
    parent->centralWidget()->setLayout(mainLayout);

    //Set tableView content
    tableView->setModel(getViewModel());
    tableView->resizeColumnsToContents();

    //Create addDepartment instance
    getAddDepartment();

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton, SIGNAL(clicked()), add_department, SLOT(initialize()));
    QObject::connect(editButton,   SIGNAL(clicked()), this, SLOT(edit()));
    QObject::connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));

    QObject::connect(tableView, SIGNAL(pressed(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView, SIGNAL(doubleClicked(QModelIndex)), add_department, SLOT(initialize(QModelIndex)));

    //Connect mainWindow destroy with removeWidgets to remove dynamic objects
    QObject::connect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));

    QObject::connect(getModel(), SIGNAL(primeInsert(int,QSqlRecord&)), this, SLOT(updateView(int,QSqlRecord&)));
    QObject::connect(getModel(), SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(updateView(QModelIndex,QModelIndex)));
}

/**
 * @brief Department::selectRow
 * @param modelIndex
 */
void Department::selectRow(const QModelIndex &modelIndex) {
    tableView->selectRow(modelIndex.row());

    int department_id = getModel()->record(modelIndex.row()).value("id").toInt();

    //============================================================
    //========================= Positions ========================
    //============================================================

    QSqlQueryModel *positionModel = new QSqlQueryModel;
    positionModel->setQuery("SELECT p.id, p.name FROM dep_positions as dp " \
                            "JOIN position as p ON p.id = dp.position_id "\
                            "WHERE dp.department_id = " + QString::number(department_id));

    if (positionModel->rowCount())
    {
        positions = positions ? positions : new QTableView;
        positions->setModel(positionModel);
        positions->setColumnWidth(0, 70);
        positions->setColumnWidth(1, 150);
        positions->setFixedWidth(250);

        positions->verticalScrollBar()->setStyleSheet(
            "QScrollBar:vertical { width: 1px; }");

        positions_label = positions_label ? positions_label : new QLabel("<b>Պաշտոններ</b>");
        positions_label->setAlignment(Qt::AlignCenter);
        positions_label->setFixedWidth(250);

        mainLayout->addWidget(positions_label, 1, 8, 1, 2);
        mainLayout->addWidget(positions, 2, 8, 10, 2);
    }
    else {
        delete positions;
        delete positions_label;
        positions       = NULL;
        positions_label = NULL;
    }

    //============================================================
    //======================== End Positions =====================
    //============================================================

}

/**
 * @brief Department::edit
 */
void Department::edit()
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

    add_department->initByRowNumber(selectedRows.at(0).row());
}

/**
 * @brief Department::remove
 */
void Department::remove()
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
 * @brief Department::getModel
 * @return
 */
QSqlRelationalTableModel* Department::getModel()
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
 * @brief Department::getViewModel
 * @return
 */
QSqlQueryModel* Department::getViewModel()
{
    if (!viewModel){
        getModel();
    }

    return viewModel;
}

/**
 * @brief Department::destroy
 */
void Department::destroy()
{
    delete tableView;
    delete mainLayout;
    delete errorLabel;

    delete addButton;
    delete editButton;
    delete removeButton;

    errorLabel     = NULL;
    tableView      = NULL;
    addButton      = NULL;
    editButton     = NULL;
    removeButton   = NULL;
    mainLayout     = NULL;

    QObject::disconnect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}

/**
 * @brief Department::initAddDepartment
 * @return
 */
addDepartment* Department::getAddDepartment()
{
    add_department = add_department ? add_department : new addDepartment(getModel());
    return add_department;
}

/**
 * @brief updateViewModel
 */
void Department::updateViewModel()
{
    viewModel->setQuery("SELECT d.id, d.name, CONCAT(e.firstname, ' ', e.lastname), d.schedule_id "\
                        "FROM department as d "\
                        "JOIN employer as e ON e.id = d.manager_id");

    viewModel->setHeaderData(0,  Qt::Horizontal, "ID");
    viewModel->setHeaderData(1,  Qt::Horizontal, "Անվանում");
    viewModel->setHeaderData(2,  Qt::Horizontal, "Անուն Ազգանուն");
    viewModel->setHeaderData(3,  Qt::Horizontal, "Գրաֆիկի ID");
}

