#ifndef ADDDEPARTMENT_H
#define ADDDEPARTMENT_H

#include "addDialog.h"
#include <QMap>

namespace Ui {
class addDepartment;
}

class addDepartment : public addDialog
{
    Q_OBJECT

public:
    explicit addDepartment(QSqlRelationalTableModel *tableModel, QWidget *parent = 0);
    ~addDepartment();

private:
    Ui::addDepartment *ui;
    QMap<int, int> comboIndexManagerId;
    QMap<int, int> comboIndexScheduleId;

    virtual void init(QSqlRecord &record);
    virtual void clear();
    virtual void populateData(QSqlRecord &record);
};

#endif // ADDDEPARTMENT_H
