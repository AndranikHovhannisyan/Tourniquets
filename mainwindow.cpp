#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlTableModel>
#include <QRegExp>

#include <QTableView>

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

    //Need to change
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addItem()));

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
        this->lastTable = action->objectName();
        this->refresh();
    }
}

void MainWindow::addItem()
{
    //Get button name and determine which dialog will be open
    QPushButton* addButton = dynamic_cast<QPushButton*>(sender());
    if (addButton != NULL) {
        QString buttonText = addButton->text();
        QString str = buttonText.split(QRegExp("\\s"))[1];
        addItemDialog[str]->show();

        connect(addItemDialog[str], SIGNAL(accepted()), this, SLOT(refresh()));
    }
}

void MainWindow::refresh()
{
    //Depends on action name determine table and get data from it
    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable(this->lastTable);
    model->select();
    ui->tableView->setModel(model);
}
