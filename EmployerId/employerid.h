#ifndef EMPLOYERID_H
#define EMPLOYERID_H

#include <QSqlRelationalTableModel>
#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QMainWindow>
#include <QSqlDatabase>
#include "addemployerid.h"

class EmployerId
{
private:
    EmployerId(QSqlDatabase *dbConnection, QMainWindow *mainWindow);
    EmployerId(const EmployerId &);
    EmployerId& operator=(const EmployerId&);

    static EmployerId* employerId;

    addEmployerId *add_employerId;
    QSqlRelationalTableModel *model;
    QSqlDatabase* db;

    QMainWindow *parent;
    QTableView  *tableView;
    QPushButton *addButton;
    QGridLayout *mainLayout;
    QString      tableName;

public:

    static EmployerId* create(QSqlDatabase *dbConnection, QMainWindow *mainWindow = NULL);

    //This function is used to return coressponding model
    QSqlRelationalTableModel* getModel();

public slots:
    //This function will draw all neccessary fields on the passed QMainWindow
    void select(QMainWindow *mainWindow = NULL);
};

#endif // EMPLOYERID_H
