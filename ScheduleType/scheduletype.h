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
#include "entity.h"

class ScheduleType : public Entity
{
private:
    ScheduleType(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    ScheduleType(const ScheduleType &);
    ScheduleType& operator=(const ScheduleType&);

    static ScheduleType* scheduleType;

    addScheduleType *add_scheduleType;
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

    static ScheduleType* create(QSqlDatabase dbConnection, QMainWindow *mainWindow = NULL);

    //This function is used to return coressponding model
    QSqlRelationalTableModel* getModel();

public slots:
    //This function will draw all neccessary fields on the passed QMainWindow
    void select(QMainWindow *mainWindow = NULL);
    void destroy();

    void selectRow(const QModelIndex &modelIndex);
    void edit();
    void remove();
};

#endif // SCHEDULETYPE_H
