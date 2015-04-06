#ifndef ADDSCHEDULETYPE_H
#define ADDSCHEDULETYPE_H

#include "addDialog.h"

namespace Ui {
class addScheduleType;
}

class addScheduleType : public addDialog
{
    Q_OBJECT

public:
    explicit addScheduleType(QSqlRelationalTableModel *tableModel, QWidget *parent = 0);
    ~addScheduleType();

private:
    Ui::addScheduleType *ui;

    virtual void init(QSqlRecord &);
    virtual void clear();
    virtual void populateData(QSqlRecord &);
};

#endif // ADDSCHEDULETYPE_H
