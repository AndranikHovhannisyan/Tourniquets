#ifndef ADDTRANSACTION_H
#define ADDTRANSACTION_H

#include "addDialog.h"

namespace Ui {
class addTransaction;
}

class addTransaction : public addDialog
{
    Q_OBJECT

public:
    explicit addTransaction(QSqlRelationalTableModel *tableModel, QWidget *parent = 0);
    ~addTransaction();

private:
    Ui::addTransaction *ui;

    virtual void init(QSqlRecord &);
    virtual void clear();
    virtual void populateData(QSqlRecord &);
};

#endif // ADDTRANSACTION_H
