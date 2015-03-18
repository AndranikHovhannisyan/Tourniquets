#ifndef ADDEMPLOYERID_H
#define ADDEMPLOYERID_H

#include "addDialog.h"
#include <QSqlTableModel>
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
    QSqlTableModel *employerModel;
    QMap<QString, int> types;

    virtual void init();
    virtual void claer();

private slots:
    void createEmployerId();
};

#endif // ADDEMPLOYERID_H
