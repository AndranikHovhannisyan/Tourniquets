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
    explicit addDepartment(QSqlRelationalTableModel *tableModel, QSqlDatabase *db = 0, QWidget *parent = 0);
    ~addDepartment();

private:
    Ui::addDepartment *ui;
    QMap<int, int> comboIndexManagerId;
    QMap<int, int> comboIndexScheduleId;
    int currentId;

    virtual void init(QSqlRecord &record);
    virtual void clear();
    virtual void populateData(QSqlRecord &record);

private slots:
    void addPosition();
    void selectRow(const QModelIndex &modelIndex);
    void removeDepartmentPosition();
};

#endif // ADDDEPARTMENT_H
