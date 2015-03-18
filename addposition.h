#ifndef ADDPOSITION_H
#define ADDPOSITION_H

#include "addDialog.h"

namespace Ui {
class addPosition;
}

class addPosition : public addDialog
{
    Q_OBJECT

public:
    explicit addPosition(QSqlDatabase db, QWidget *parent = 0);
    ~addPosition();

private:
    Ui::addPosition *ui;
    virtual void init();
};

#endif // ADDPOSITION_H
