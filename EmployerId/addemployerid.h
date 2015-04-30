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
    explicit addEmployerId(QSqlRelationalTableModel *tableModel, QWidget *parent = 0);
    ~addEmployerId();

    QMap<int, QString> idTypes;

private:
    Ui::addEmployerId *ui;
    QMap<int, int> comboIndexEmployerId;

    virtual void init(QSqlRecord &);
    virtual void clear();
    virtual void populateData(QSqlRecord &);
};

#endif // ADDEMPLOYERID_H
