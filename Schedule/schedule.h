#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QSqlRelationalTableModel>
#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QMainWindow>
#include <QSqlDatabase>
#include "addschedule.h"

class Schedule
{
private:
    Schedule(QSqlDatabase *dbConnection, QMainWindow *mainWindow);
    Schedule(const Schedule &);
    Schedule& operator=(const Schedule&);

    static Schedule* schedule;

    addSchedule *add_schedule;
    QSqlRelationalTableModel *model;
    QSqlDatabase* db;

    QMainWindow *parent;
    QTableView  *tableView;
    QPushButton *addButton;
    QGridLayout *mainLayout;
    QString      tableName;

public:

    static Schedule* create(QSqlDatabase *dbConnection, QMainWindow *mainWindow);

    //This function is used to return coressponding model
    QSqlRelationalTableModel* getModel();

public slots:
    //This function will draw all neccessary fields on the passed QMainWindow
    void select();
};

#endif // SCHEDULE_H
