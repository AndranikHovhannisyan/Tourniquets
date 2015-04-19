#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtSql/QSqlDatabase>
#include <QMainWindow>
#include <QMap>
#include <QSqlRelationalTableModel>

#include "addDialog.h"
#include "Department/adddepartment.h"
#include "Position/addposition.h"
#include "ScheduleType/addscheduletype.h"
#include "Schedule/addschedule.h"
#include "Tourniquet/addtourniquet.h"
#include "EmployerId/addemployerid.h"
#include "Employer/addemployer.h"
#include "Address/addaddress.h"
#include "Phone/addphone.h"
#include "entity.h"

#include <QModelIndex>
#include <QTableView>
#include <QGridLayout>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    QPushButton              *addButton;
    QTableView               *tableView;
    QGridLayout              *mainLayout;

    //Part of bad solution
    // ========================================================
    QMap<QString, Entity*>    entities;
    Entity                   *currentEntity;
    // ========================================================

    Ui::MainWindow           *ui;
    QSqlDatabase              db;
    QMap<QString, addDialog*> addItemDialog;
    QString                   table;
    QSqlRelationalTableModel *model;


public slots:
    void infoWindow();
};

#endif // MAINWINDOW_H
