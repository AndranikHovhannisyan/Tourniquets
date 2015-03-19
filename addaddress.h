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
    explicit addAddress(QSqlDatabase db, QWidget *parent = 0);
    ~addAddress();

private:
    Ui::addAddress *ui;
    virtual void init();
    virtual void claer();
    virtual void populateData(QSqlRecord &);

private slots:
    void createAddress();
};

#endif // ADDADDRESS_H
