#ifndef ADDDEPARTMENT_H
#define ADDDEPARTMENT_H

#include "addDialog.h"

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
    virtual void init();
    virtual void claer();
};

#endif // ADDDEPARTMENT_H
