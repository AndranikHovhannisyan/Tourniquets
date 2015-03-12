#ifndef ADDSCHEDULE_H
#define ADDSCHEDULE_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class addSchedule;
}

class addSchedule : public QDialog
{
    Q_OBJECT

public:
    explicit addSchedule(QSqlDatabase db, QWidget *parent = 0);
    ~addSchedule();

private:
    Ui::addSchedule *ui;
};

#endif // ADDSCHEDULE_H
