#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QRegExp>


#include <QAction>
#include <QSqlRecord>
#include <QDebug>

#include "Address/address.h"
#include "Department/department.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Connect menu actions
    connect(ui->department,     SIGNAL(triggered()), Department::create(db, this), SLOT(select()));
    connect(ui->position,       SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->schedule,       SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->schedule_type,  SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->tourniquet,     SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->employer_ids,   SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->employer,       SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->address,        SIGNAL(triggered()), Address::create(db, this), SLOT(select()));
    connect(ui->phone_number,   SIGNAL(triggered()), this, SLOT(infoWindow()));

    connect(ui->position,       SIGNAL(triggered()), Department::create(db, this), SLOT(destroy()));

    //Create a database connection
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("tourniquets");
    db.setUserName("root");
    db.setPassword("root");
    db.open();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::infoWindow
 */
void MainWindow::infoWindow()
{
    //Get an action from which the signal come here
    QAction* action = dynamic_cast<QAction*>(sender());
    if (action != NULL) {

//        Address* address = Address::create(db, this);
//        address->select();

        Department* department = Department::create(db, this);
        department->select();

//        mainLayout->addWidget(addButton, 0, 0, 1, 2);
//        mainLayout->addWidget(tableView, 1, 0, 15, 15);
//        this->centralWidget()->setLayout(mainLayout);

        //Change also button name
//        addButton->setText("Add " + action->objectName());
//        this->table = action->objectName();
//        this->refresh();
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
//    addItemDialog[this->table]->create_edit(0);
//    connect(addItemDialog[this->table], SIGNAL(ready(int)), this, SLOT(refresh(int)));
}

/**
 * @brief MainWindow::edit
 * @param a
 */
void MainWindow::edit(QModelIndex a) {
//    int id = model->data(model->index(a.row(), 0)).toInt();
//    addItemDialog[this->table]->create_edit(id);

//    connect(addItemDialog[this->table], SIGNAL(ready(int)), this, SLOT(refresh(int)));
}

/**
 * @brief MainWindow::subTables
 */
void MainWindow::subTables() {
//    if (this->table == "employer") {
        QTableView *t = new QTableView;
//    }
}
