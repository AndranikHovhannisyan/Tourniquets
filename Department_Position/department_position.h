#ifndef DEPARTMENT_POSITION_H
#define DEPARTMENT_POSITION_H

#include "entity.h"
#include <QSqlRelationalTableModel>


class Department_Position
{
private:
    Department_Position(QSqlDatabase dbConnection);
    Department_Position(const Department_Position &);
    Department_Position& operator=(const Department_Position&);

    static Department_Position* department_position;

    QSqlRelationalTableModel *model;
    QSqlDatabase              db;
    QString                   tableName;

public:

    static Department_Position* create(QSqlDatabase dbConnection);

    //This function is used to return coressponding model
    QSqlRelationalTableModel* getModel();
};

#endif // DEPARTMENT_POSITION_H