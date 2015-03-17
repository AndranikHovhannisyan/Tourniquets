#ifndef ADDSCHEDULE_H
#define ADDSCHEDULE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QMap>
#include <QGridLayout>

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
    QSqlDatabase db;
};

#endif // ADDSCHEDULE_H
