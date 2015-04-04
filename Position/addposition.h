#ifndef ADDPOSITION_H
#define ADDPOSITION_H

#include "addDialog.h"
#include <QMap>

namespace Ui {
class addPosition;
}

class addPosition : public addDialog
{
    Q_OBJECT

public:
    explicit addPosition(QSqlDatabase db, QWidget *parent = 0);
    ~addPosition();

private:
    Ui::addPosition *ui;
    QMap<int, int> comboIndexScheduleId;

    virtual void init(QSqlRecord &record);
    virtual void claer();
    virtual void populateData(QSqlRecord &);
};

#endif // ADDPOSITION_H
