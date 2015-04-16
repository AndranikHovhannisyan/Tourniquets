#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <QSqlRelationalTableModel>
#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QMainWindow>
#include <QSqlDatabase>
#include "adddepartment.h"

class Department
{
private:
    Department(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    Department(const Department &);
    Department& operator=(const Department&);

    static Department* department;

    addDepartment *add_department;
    QSqlRelationalTableModel *model;
    QSqlDatabase db;

    QMainWindow *parent;
    QTableView  *tableView;
    QPushButton *addButton;
    QGridLayout *mainLayout;
    QString      tableName;

public:

    static Department* create(QSqlDatabase dbConnection, QMainWindow *mainWindow);

    //This function is used to return coressponding model
    QSqlRelationalTableModel* getModel();

public slots:
    //This function will draw all neccessary fields on the passed QMainWindow
    void select(QMainWindow *mainWindow = NULL);
};

#endif // DEPARTMENT_H
