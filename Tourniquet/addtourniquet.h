#ifndef ADDTOURNIQUET_H
#define ADDTOURNIQUET_H

#include "addDialog.h"

namespace Ui {
class addTourniquet;
}

class addTourniquet : public addDialog
{
    Q_OBJECT

public:
    explicit addTourniquet(QSqlDatabase db, QWidget *parent = 0);
    ~addTourniquet();

private:
    Ui::addTourniquet *ui;

    virtual void init(QSqlRecord &);
    virtual void clear();
    virtual void populateData(QSqlRecord &);
};

#endif // ADDTOURNIQUET_H
