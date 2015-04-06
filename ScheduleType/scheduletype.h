#ifndef SCHEDULETYPE_H
#define SCHEDULETYPE_H

#include <QSqlRelationalTableModel>
#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QMainWindow>
#include <QSqlDatabase>
#include "addscheduletype.h"

class ScheduleType
{
private:
    ScheduleType(QSqlDatabase *dbConnection, QMainWindow *mainWindow);
    ScheduleType(const ScheduleType &);
    ScheduleType& operator=(const ScheduleType&);

    static ScheduleType* scheduleType;

    addScheduleType *add_scheduleType;
    QSqlRelationalTableModel *model;
    QSqlDatabase* db;

    QMainWindow *parent;
    QTableView  *tableView;
    QPushButton *addButton;
    QGridLayout *mainLayout;
    QString      tableName;

public:

    static ScheduleType* create(QSqlDatabase *dbConnection, QMainWindow *mainWindow);

    //This function is used to return coressponding model
    QSqlRelationalTableModel* getModel();

public slots:
    //This function will draw all neccessary fields on the passed QMainWindow
    void select();
};

#endif // SCHEDULETYPE_H
