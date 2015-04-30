#ifndef EMPLOYERID_H
#define EMPLOYERID_H


#include "addemployerid.h"
#include "viewchangableentity.h"

class EmployerId : public ViewChangableEntity
{
private:
    EmployerId(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    EmployerId(const EmployerId &);
    EmployerId& operator=(const EmployerId&);

    static EmployerId* employerId;

    addEmployerId *add_employerId;

    //============================ Employers ============================
    QTableView  *employers;
    QLabel      *employers_label;

public:

    static EmployerId* create(QSqlDatabase dbConnection, QMainWindow *mainWindow = NULL);

    addDialog* getAddDialog();

    void createWidgets();
    void setTableViewModel();

public slots:
    void destroy();
    void selectRow(const QModelIndex &modelIndex);
    void updateViewModel();
};

#endif // EMPLOYERID_H
