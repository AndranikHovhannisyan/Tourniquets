#ifndef ADDPHONE_H
#define ADDPHONE_H

#include "addDialog.h"
#include <QMap>

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
    QMap<int, int> comboIndexEmployerId;

    virtual void init(QSqlRecord &);
    virtual void clear();
    virtual void populateData(QSqlRecord &);
};

#endif // ADDPHONE_H
