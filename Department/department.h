#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "adddepartment.h"
#include <QLabel>
#include "viewchangableentity.h"

class Department : public ViewChangableEntity
{
private:
    Department(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    Department(const Department &);
    Department& operator=(const Department&);

    static Department* department;

    addDepartment            *add_department;

    //======================= Positions ========================
    QTableView  *positions;
    QLabel      *positions_label;

public:

    static Department* create(QSqlDatabase dbConnection, QMainWindow *mainWindow = NULL);

    addDialog* getAddDialog();
    void createWidgets();
    void setTableViewModel();


public slots:
    void selectRow(const QModelIndex &modelIndex);
    void updateViewModel();
    void destroy();
};

#endif // DEPARTMENT_H
