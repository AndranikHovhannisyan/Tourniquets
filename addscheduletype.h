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
    explicit addScheduleType(QSqlDatabase db, QWidget *parent = 0);
    ~addScheduleType();

private:
    Ui::addScheduleType *ui;
    virtual void init();
    virtual void claer();
};

#endif // ADDSCHEDULETYPE_H
