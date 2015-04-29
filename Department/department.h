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
#include "entity.h"
#include <QLabel>

class Department : public Entity
{
private:
    Department(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    Department(const Department &);
    Department& operator=(const Department&);

    static Department* department;

    addDepartment            *add_department;
    QSqlRelationalTableModel *model;
    QSqlQueryModel           *viewModel;
    QSqlDatabase db;

    QMainWindow *parent;
    QTableView  *tableView;
    QGridLayout *mainLayout;
    QString      tableName;

    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *removeButton;

public:

    static Department* create(QSqlDatabase dbConnection, QMainWindow *mainWindow = NULL);

    //This function is used to return coressponding model
    QSqlRelationalTableModel* getModel();
    QSqlQueryModel* getViewModel();

    addDepartment* getAddDepartment();

    //======================= Positions ========================

    QTableView  *positions;
    QLabel      *positions_label;

public slots:
    //This function will draw all neccessary fields on the passed QMainWindow
    void select(QMainWindow *mainWindow = NULL);
    void destroy();

    void selectRow(const QModelIndex &modelIndex);
    void edit();
    void remove();

    void updateViewModel();
};

#endif // DEPARTMENT_H
