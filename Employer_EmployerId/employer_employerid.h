#ifndef EMPLOYER_EMPLOYERID_H
#define EMPLOYER_EMPLOYERID_H

#include "entity.h"
#include <QSqlRelationalTableModel>


class Employer_EmployerId
{
private:
    Employer_EmployerId(QSqlDatabase dbConnection);
    Employer_EmployerId(const Employer_EmployerId &);
    Employer_EmployerId& operator=(const Employer_EmployerId&);

    static Employer_EmployerId* employer_employerId;

    QSqlRelationalTableModel *model;
    QSqlDatabase              db;
    QString                   tableName;

public:

    static Employer_EmployerId* create(QSqlDatabase dbConnection);

    //This function is used to return coressponding model
    QSqlRelationalTableModel* getModel();
};

#endif // EMPLOYER_EMPLOYERID_H
