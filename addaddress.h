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

private slots:
    void createAddress();

signals:
    void ready();
};

#endif // ADDADDRESS_H
