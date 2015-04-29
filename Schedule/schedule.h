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
#include "entity.h"

class Schedule : public Entity
{
private:
    Schedule(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    Schedule(const Schedule &);
    Schedule& operator=(const Schedule&);

    static Schedule* schedule;

    addSchedule *add_schedule;
    QSqlRelationalTableModel *model;
    QSqlDatabase db;

    QMainWindow *parent;
    QTableView  *tableView;
    QGridLayout *mainLayout;
    QString      tableName;


    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *removeButton;

public:

    static Schedule* create(QSqlDatabase dbConnection, QMainWindow *mainWindow = NULL);

    //This function is used to return coressponding model
    QSqlRelationalTableModel* getModel();

    addSchedule* getAddSchedule();

public slots:
    //This function will draw all neccessary fields on the passed QMainWindow
    void select(QMainWindow *mainWindow = NULL);
    void destroy();

    void selectRow(const QModelIndex &modelIndex);
    void edit();
    void remove();
};

#endif // SCHEDULE_H
