#ifndef ADDEMPLOYER_H
#define ADDEMPLOYER_H

#include "addDialog.h"
#include <QMap>

namespace Ui {
class addEmployer;
}

class addEmployer : public addDialog
{
    Q_OBJECT

public:
    explicit addEmployer(QSqlRelationalTableModel *tableModel, QWidget *parent = 0);
    ~addEmployer();

private:
    Ui::addEmployer *ui;
    QMap<int, int> comboIndexAddressId;
    QMap<int, int> comboIndexDepartmentId;
    QMap<int, int> comboIndexPositionId;
    QMap<int, int> comboIndexScheduleId;

    virtual void init(QSqlRecord &record);
    virtual void clear();
    virtual void populateData(QSqlRecord &record);
};

#endif // ADDEMPLOYER_H
