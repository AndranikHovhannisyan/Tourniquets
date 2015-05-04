#include "Department/department.h"
#include <QObject>
#include <QException>
#include <QMessageBox>
#include <QComboBox>
#include <QDebug>
#include <QSqlError>
#include <QScrollBar>

Department* Department::department = NULL;

/**
 * Create singleton object of Department
 *
 * @brief Department::create
 * @param dbConnection
 * @param mainWindow
 * @return
 */
Department* Department::create(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    if (!department) {
        department = new Department(dbConnection, mainWindow);
    }

    return department;
}

/**
 * @brief Department::Department
 */
Department::Department(QSqlDatabase dbConnection, QMainWindow *mainWindow):
    ViewChangableEntity(dbConnection, mainWindow)
{
    tableName       = "department";
    add_department  = NULL;
    positions       = NULL;
    positions_label = NULL;
}

/**
 * @brief Department::createWidgets
 */
void Department::createWidgets()
{
    ViewChangableEntity::createWidgets();

//    tableView->setFixedWidth(520);
}

/**
 * @brief Department::setTableViewModel
 */
void Department::setTableViewModel()
{
    ViewChangableEntity::setTableViewModel();

    tableView->resizeColumnsToContents();
}


/**
 * @brief Department::selectRow
 * @param modelIndex
 */
void Department::selectRow(const QModelIndex &modelIndex) {

    ViewChangableEntity::selectRow(modelIndex);

    int department_id = getModel()->record(modelIndex.row()).value("id").toInt();

    //============================================================
    //========================= Positions ========================
    //============================================================

    QSqlQueryModel *positionModel = new QSqlQueryModel;
    positionModel->setQuery("SELECT p.id, p.name FROM dep_positions as dp " \
                            "JOIN position as p ON p.id = dp.position_id "\
                            "WHERE dp.department_id = " + QString::number(department_id));

    if (positionModel->rowCount())
    {
        positions = positions ? positions : new QTableView;
        positions->setModel(positionModel);
        positions->setColumnWidth(0, 70);
        positions->setColumnWidth(1, 150);
        positions->setFixedWidth(250);

        positions->verticalScrollBar()->setStyleSheet(
            "QScrollBar:vertical { width: 1px; }");

        positions_label = positions_label ? positions_label : new QLabel("<b>Պաշտոններ</b>");
        positions_label->setAlignment(Qt::AlignCenter);
        positions_label->setFixedWidth(250);

        mainLayout->addWidget(positions_label, 1, 8, 1, 2);
        mainLayout->addWidget(positions, 2, 8, 10, 2);
    }
    else {
        delete positions;
        delete positions_label;
        positions       = NULL;
        positions_label = NULL;
    }

    //============================================================
    //======================== End Positions =====================
    //============================================================

}


/**
 * @brief Department::destroy
 */
void Department::destroy()
{
    ViewChangableEntity::destroy();

    delete positions;
    delete positions_label;

    positions       = NULL;
    positions_label = NULL;
}

/**
 * @brief Department::initAddDepartment
 * @return
 */
addDialog *Department::getAddDialog()
{
    add_department = add_department ? add_department : new addDepartment(getModel());
    return add_department;
}

/**
 * @brief updateViewModel
 */
void Department::updateViewModel()
{
    viewModel->setQuery("SELECT d.id, d.name, CONCAT(e.firstname, ' ', e.lastname), d.schedule_id "\
                        "FROM department as d "\
                        "JOIN employer as e ON e.id = d.manager_id");

    viewModel->setHeaderData(0,  Qt::Horizontal, "ID");
    viewModel->setHeaderData(1,  Qt::Horizontal, "Անվանում");
    viewModel->setHeaderData(2,  Qt::Horizontal, "Անուն Ազգանուն");
    viewModel->setHeaderData(3,  Qt::Horizontal, "Գրաֆիկի ID");
}

