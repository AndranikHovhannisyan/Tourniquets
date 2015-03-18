#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlTableModel>
#include <QRegExp>


#include <QAction>
#include <QSqlRecord>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addItem()));
    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(edit(QModelIndex)));



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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::infoWindow()
{
    //Get an action from which the signal come here
    QAction* action = dynamic_cast<QAction*>(sender());
    if (action != NULL) {
        //Change also button name
        ui->addButton->setText("Add " + action->objectName());
        this->table = action->objectName();
        this->refresh();
    }
}

void MainWindow::refresh()
{
    model = new QSqlTableModel(this, db);
    model->setTable(this->table);
    model->select();
    ui->tableView->setModel(model);
}

void MainWindow::addItem()
{
    addItemDialog[this->table]->editShow(0);
    connect(addItemDialog[this->table], SIGNAL(ready()), this, SLOT(refresh()));
}

void MainWindow::edit(QModelIndex a) {
    int id = model->data(model->index(a.row(), 0)).toInt();
    addItemDialog[this->table]->editShow(id);

    connect(addItemDialog[this->table], SIGNAL(ready()), this, SLOT(refresh()));
}
