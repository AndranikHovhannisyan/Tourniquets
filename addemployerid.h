#ifndef ADDEMPLOYERID_H
#define ADDEMPLOYERID_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class addEmployerId;
}

class addEmployerId : public QDialog
{
    Q_OBJECT

public:
    explicit addEmployerId(QSqlDatabase db, QWidget *parent = 0);
    ~addEmployerId();

private:
    Ui::addEmployerId *ui;
    QSqlDatabase db;
};

#endif // ADDEMPLOYERID_H
