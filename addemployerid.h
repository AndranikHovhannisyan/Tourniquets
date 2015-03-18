#ifndef ADDEMPLOYERID_H
#define ADDEMPLOYERID_H

#include "addDialog.h"

namespace Ui {
class addEmployerId;
}

class addEmployerId : public addDialog
{
    Q_OBJECT

public:
    explicit addEmployerId(QSqlDatabase db, QWidget *parent = 0);
    ~addEmployerId();

private:
    Ui::addEmployerId *ui;
    virtual void init();
};

#endif // ADDEMPLOYERID_H
