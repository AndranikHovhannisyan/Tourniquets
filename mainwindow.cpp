#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QRegExp>


#include <QAction>
#include <QSqlRecord>
#include <QDebug>

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    addButton = new QPushButton;
    tableView = new QTableView;
    mainLayout = new QGridLayout;

    //Connect menu actions
    connect(ui->department,     SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->position,       SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->schedule,       SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->schedule_type,  SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->tourniquet,     SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->employer_ids,   SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->employer,       SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->address,        SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->phone_number,   SIGNAL(triggered()), this, SLOT(infoWindow()));

    connect(addButton, SIGNAL(clicked()), this, SLOT(addItem()));
    connect(tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(edit(QModelIndex)));


    //Create a database connection
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("tourniquets");
    db.setUserName("root");
    db.setPassword("root");
    db.open();

    //Add addDialog elements to add data and sent to their constructor db connection object
    addItemDialog["department"]     = new addDepartment(db, this);
    addItemDialog["position"]       = new addPosition(db, this);
    addItemDialog["schedule"]       = new addSchedule(db, this);
    addItemDialog["schedule_type"]  = new addScheduleType(db, this);
    addItemDialog["tourniquet"]     = new addTourniquet(db, this);
    addItemDialog["employer_ids"]   = new addEmployerId(db, this);
    addItemDialog["employer"]       = new addEmployer(db, this);
    addItemDialog["address"]        = new addAddress(db, this);
    addItemDialog["phone_number"]   = new addPhone(db, this);

    foreach(addDialog * add_dialog, addItemDialog) {
        add_dialog->subConnections();
    }
}

MainWindow::~MainWindow()
{
    delete ui;

//    delete addButton;
//    delete tableView;
//    delete mainLayout;
}

/**
 * @brief MainWindow::infoWindow
 */
void MainWindow::infoWindow()
{
    //Get an action from which the signal come here
    QAction* action = dynamic_cast<QAction*>(sender());
    if (action != NULL) {

        mainLayout->addWidget(addButton, 0, 0, 1, 2);
        mainLayout->addWidget(tableView, 1, 0, 15, 15);
        this->centralWidget()->setLayout(mainLayout);

        //Change also button name
        addButton->setText("Add " + action->objectName());
        this->table = action->objectName();
        this->refresh();
    }
}

/**
 * @brief MainWindow::refresh
 */
void MainWindow::refresh(int)
{
    model = new QSqlRelationalTableModel(this, db);
    model->setTable(this->table);

    if (this->table == "employer_ids") {
        model->setRelation(1, QSqlRelation("employer", "id", "firstname"));
    }

    model->select();
    tableView->setModel(model);
}

/**
 * @brief MainWindow::addItem
 */
void MainWindow::addItem()
{
    addItemDialog[this->table]->editShow(0);
    connect(addItemDialog[this->table], SIGNAL(ready(int)), this, SLOT(refresh(int)));
}

/**
 * @brief MainWindow::edit
 * @param a
 */
void MainWindow::edit(QModelIndex a) {
    int id = model->data(model->index(a.row(), 0)).toInt();
    addItemDialog[this->table]->editShow(id);

    connect(addItemDialog[this->table], SIGNAL(ready(int)), this, SLOT(refresh(int)));
}

/**
 * @brief MainWindow::subTables
 */
void MainWindow::subTables() {
//    if (this->table == "employer") {
        QTableView *t = new QTableView;
//    }
}
