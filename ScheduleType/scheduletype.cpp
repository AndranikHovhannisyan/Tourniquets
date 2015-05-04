#include "ScheduleType/scheduletype.h"
#include <QException>
#include <QObject>
#include <QMessageBox>
#include <QSqlError>


ScheduleType* ScheduleType::scheduleType = NULL;

/**
 * Create singleton object of ScheduleType
 *
 * @brief ScheduleType::create
 * @param dbConnection
 * @param mainWindow
 * @return
 */
ScheduleType* ScheduleType::create(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    if (!scheduleType) {
        scheduleType = new ScheduleType(dbConnection, mainWindow);
    }

    return scheduleType;
}

/**
 * @brief ScheduleType::setTableViewModel
 */
void ScheduleType::setTableViewModel()
{
    EditableEntity::setTableViewModel();

    getModel()->setHeaderData(0,  Qt::Horizontal, "ID");
    getModel()->setHeaderData(1,  Qt::Horizontal, "Անվանում");
    getModel()->setHeaderData(2,  Qt::Horizontal, "Թույլատրելի ուշացում");
    getModel()->setHeaderData(3,  Qt::Horizontal, "Անտեսվող շուտ եկած ժ․");
}

/**
 * @brief ScheduleType::ScheduleType
 */
ScheduleType::ScheduleType(QSqlDatabase dbConnection, QMainWindow *mainWindow):
    EditableEntity(dbConnection, mainWindow)
{
    tableName   = "schedule_type";
    add_scheduleType = NULL;
}

/**
 * @brief ScheduleType::getAddDialog
 * @return
 */
addDialog* ScheduleType::getAddDialog()
{
    add_scheduleType = add_scheduleType ? add_scheduleType : new addScheduleType(getModel());
    return add_scheduleType;
}
