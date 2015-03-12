#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlTableModel>
#include <QRegExp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->department, SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->position, SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->schedule, SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->schedule_type, SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->tourniquet, SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->employer_ids, SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->employer, SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->address, SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->phone_number, SIGNAL(triggered()), this, SLOT(infoWindow()));

    //Need to change
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addItem()));


    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("tourniquets");
    db.setUserName("root");
    db.setPassword("root");
    db.open();

    addItemDialog["department"]     = new addDepartment(db, this);
    addItemDialog["position"]       = new addPosition(db, this);
    addItemDialog["schedule"]       = new addSchedule(db, this);
    addItemDialog["schedule_type"]  = new addScheduleType(db, this);
    addItemDialog["tourniquet"]     = new addTourniquet(db, this);
    addItemDialog["employer_ids"]   = new addEmployerId(db, this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::infoWindow()
{
    QAction* action = dynamic_cast<QAction*>(sender());
    if (action != NULL) {

        QSqlTableModel *model = new QSqlTableModel(this, db);
        model->setTable(action->objectName());
        model->select();
        ui->tableView->setModel(model);
        ui->addButton->setText("Add " + action->objectName());
    }
}

void MainWindow::addItem()
{
    QPushButton* addButton = dynamic_cast<QPushButton*>(sender());
    if (addButton != NULL) {
        QString buttonText = addButton->text();
        QString str = buttonText.split(QRegExp("\\s"))[1];
        addItemDialog[str]->show();
    }
}
