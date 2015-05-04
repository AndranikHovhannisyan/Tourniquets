#include "Schedule/schedule.h"
#include <QObject>


Schedule* Schedule::schedule = NULL;

/**
 * Create singleton object of Schedule
 *
 * @brief Schedule::create
 * @param dbConnection
 * @param mainWindow
 * @return
 */
Schedule* Schedule::create(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    if (!schedule) {
        schedule = new Schedule(dbConnection, mainWindow);
    }

    return schedule;
}

/**
 * @brief Schedule::Schedule
 */
Schedule::Schedule(QSqlDatabase dbConnection, QMainWindow *mainWindow) :
    ViewChangableEntity(dbConnection, mainWindow)
{
    tableName   = "schedule";
    add_schedule = NULL;
}


/**
 * @brief Schedule::getAddDialog
 * @return
 */
addDialog* Schedule::getAddDialog()
{
    add_schedule = add_schedule ? add_schedule : new addSchedule(getModel());
    return add_schedule;
}

/**
 * @brief updateViewModel
 */
void Schedule::updateViewModel()
{
    viewModel->setQuery("SELECT s.id, s.standart_in_time, s.standart_out_time, st.name "\
                        "FROM schedule as s "\
                        "JOIN schedule_type as st ON st.id = s.schedule_type_id "\
                        "ORDER BY s.id");

    viewModel->setHeaderData(0,  Qt::Horizontal, "ID");
    viewModel->setHeaderData(1,  Qt::Horizontal, "Ստանդարտ մուտք");
    viewModel->setHeaderData(2,  Qt::Horizontal, "Ստանդարտ ելք");
    viewModel->setHeaderData(3,  Qt::Horizontal, "Ռեժիմ");
}
