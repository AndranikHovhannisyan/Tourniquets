#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QSqlRelationalTableModel>
#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QMainWindow>
#include <QSqlDatabase>
#include "addschedule.h"
#include "viewchangableentity.h"


class Schedule : public ViewChangableEntity
{
private:
    Schedule(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    Schedule(const Schedule &);
    Schedule& operator=(const Schedule&);

    static Schedule* schedule;
    addSchedule *add_schedule;

public:

    static Schedule* create(QSqlDatabase dbConnection, QMainWindow *mainWindow = NULL);
    addDialog* getAddDialog();

public slots:
    void updateViewModel();
};

#endif // SCHEDULE_H
