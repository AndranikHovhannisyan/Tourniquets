#ifndef ADDSCHEDULETYPE_H
#define ADDSCHEDULETYPE_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class addScheduleType;
}

class addScheduleType : public QDialog
{
    Q_OBJECT

public:
    explicit addScheduleType(QSqlDatabase db, QWidget *parent = 0);
    ~addScheduleType();

private:
    Ui::addScheduleType *ui;
    QSqlDatabase db;
};

#endif // ADDSCHEDULETYPE_H
