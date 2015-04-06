#ifndef ADDSCHEDULE_H
#define ADDSCHEDULE_H

#include "addDialog.h"
#include <QMap>
#include <QGridLayout>

namespace Ui {
class addSchedule;
}

class addSchedule : public addDialog
{
    Q_OBJECT

public:
    explicit addSchedule(QSqlDatabase db, QWidget *parent = 0);
    ~addSchedule();

private:
    Ui::addSchedule *ui;

    virtual void init(QSqlRecord &);
    virtual void clear();
    virtual void populateData(QSqlRecord &);
};

#endif // ADDSCHEDULE_H
