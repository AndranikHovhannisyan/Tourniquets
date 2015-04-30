#ifndef SCHEDULETYPE_H
#define SCHEDULETYPE_H

#include "addscheduletype.h"
#include "editableentity.h"

class ScheduleType : public EditableEntity
{
private:
    ScheduleType(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    ScheduleType(const ScheduleType &);
    ScheduleType& operator=(const ScheduleType&);

    static ScheduleType* scheduleType;

    addScheduleType *add_scheduleType;
    addDialog* getAddDialog();
public:

    static ScheduleType* create(QSqlDatabase dbConnection, QMainWindow *mainWindow = NULL);

public slots:
};

#endif // SCHEDULETYPE_H
