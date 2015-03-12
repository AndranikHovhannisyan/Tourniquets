#ifndef ADDDEPARTMENT_H
#define ADDDEPARTMENT_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class addDepartment;
}

class addDepartment : public QDialog
{
    Q_OBJECT

public:
    explicit addDepartment(QSqlDatabase db, QWidget *parent = 0);
    ~addDepartment();

private:
    Ui::addDepartment *ui;
};

#endif // ADDDEPARTMENT_H
