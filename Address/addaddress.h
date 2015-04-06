#ifndef ADDADDRESS_H
#define ADDADDRESS_H

#include "addDialog.h"

namespace Ui {
class addAddress;
}

class addAddress : public addDialog
{
    Q_OBJECT

public:
    explicit addAddress(QSqlRelationalTableModel *tableModel, QWidget *parent = 0);
    ~addAddress();

private:
    Ui::addAddress *ui;
    virtual void init(QSqlRecord &record);
    virtual void clear();
    virtual void populateData(QSqlRecord &);
};

#endif // ADDADDRESS_H
