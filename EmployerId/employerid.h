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
#include "entity.h"

#include "viewchangableentity.h"

class EmployerId : public ViewChangableEntity
{
private:
    EmployerId(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    EmployerId(const EmployerId &);
    EmployerId& operator=(const EmployerId&);

    static EmployerId* employerId;

    addEmployerId *add_employerId;


public:

    static EmployerId* create(QSqlDatabase dbConnection, QMainWindow *mainWindow = NULL);

    addDialog* getAddDialog();

public slots:
    void destroy();
    void selectRow(const QModelIndex &modelIndex);
    void updateViewModel();
};

#endif // EMPLOYERID_H
