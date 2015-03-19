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
    explicit addDepartment(QSqlDatabase db, QWidget *parent = 0);
    ~addDepartment();

private:
    Ui::addDepartment *ui;
    QMap<int, int> comboIndexEmployerId;
    QMap<int, int> comboIndexScheduleId;

    virtual void init();
    virtual void claer();
    virtual void populateData(QSqlRecord &);
};

#endif // ADDDEPARTMENT_H
