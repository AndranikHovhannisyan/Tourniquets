#ifndef ADDEMPLOYERID_H
#define ADDEMPLOYERID_H

#include "addDialog.h"
#include <QMap>

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
    QMap<int, int> comboIndexEmployerId;

    virtual void init();
    virtual void claer();
    virtual void populateData(QSqlRecord &);
};

#endif // ADDEMPLOYERID_H
