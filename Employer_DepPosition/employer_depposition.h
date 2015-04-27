#ifndef EMPLOYER_DEPPOSITION_H
#define EMPLOYER_DEPPOSITION_H

#include "entity.h"
#include <QSqlRelationalTableModel>


class Employer_DepPosition
{
private:
    Employer_DepPosition(QSqlDatabase dbConnection);
    Employer_DepPosition(const Employer_DepPosition &);
    Employer_DepPosition& operator=(const Employer_DepPosition&);

    static Employer_DepPosition* employer_depposition;

    QSqlRelationalTableModel *model;
    QSqlDatabase              db;
    QString                   tableName;

public:

    static Employer_DepPosition* create(QSqlDatabase dbConnection);

    //This function is used to return coressponding model
    QSqlRelationalTableModel* getModel();
};


#endif // EMPLOYER_DEPPOSITION_H
