#ifndef ADDEMPLOYER_H
#define ADDEMPLOYER_H

#include "addDialog.h"

namespace Ui {
class addEmployer;
}

class addEmployer : public addDialog
{
    Q_OBJECT

public:
    explicit addEmployer(QSqlDatabase db, QWidget *parent = 0);
    ~addEmployer();

private:
    Ui::addEmployer *ui;
    virtual void init();
};

#endif // ADDEMPLOYER_H
