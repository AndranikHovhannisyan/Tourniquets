#ifndef ADDPHONE_H
#define ADDPHONE_H

#include "addDialog.h"

namespace Ui {
class addPhone;
}

class addPhone : public addDialog
{
    Q_OBJECT

public:
    explicit addPhone(QSqlDatabase db, QWidget *parent = 0);
    ~addPhone();

private:
    Ui::addPhone *ui;
    virtual void init();
    virtual void claer();
};

#endif // ADDPHONE_H
