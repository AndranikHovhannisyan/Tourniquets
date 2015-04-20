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
#include "Position/position.h"
#include "Schedule/schedule.h"
#include "ScheduleType/scheduletype.h"
#include "Tourniquet/tourniquet.h"
#include "EmployerId/employerid.h"
#include "Employer/employer.h"
#include "Phone/phone.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentEntity = NULL;

    entities["department"]      = Department::create(db, this);
    entities["position"]        = Position::create(db, this);
    entities["address"]         = Address::create(db, this);

//    entities["schedule"]        = Schedule::create(db, this);
    entities["schedule_type"]   = ScheduleType::create(db, this);
//    entities["tourniquet"]      = Tourniquet::create(db, this);
    entities["employer_ids"]    = EmployerId::create(db, this);
    entities["employer"]        = Employer::create(db, this);
    entities["phone_number"]    = Phone::create(db, this);

    connect(ui->department,     SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->position,       SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->address,        SIGNAL(triggered()), this, SLOT(infoWindow()));

    connect(ui->schedule_type,  SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->employer,       SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->employer_ids,   SIGNAL(triggered()), this, SLOT(infoWindow()));
    connect(ui->phone_number,   SIGNAL(triggered()), this, SLOT(infoWindow()));

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
    QAction* action = dynamic_cast<QAction*>(sender());
    if (action != NULL) {
        if (currentEntity) {
            currentEntity->destroy();
        }

        currentEntity = entities[action->objectName()];
        currentEntity->select();
    }
}
