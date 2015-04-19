#include "addposition.h"
#include "ui_addposition.h"
#include "Schedule/schedule.h"
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDebug>

/**
 * @brief addPosition::addPosition
 * @param tableModel
 * @param parent
 */
addPosition::addPosition(QSqlRelationalTableModel *tableModel, QWidget *parent) :
    addDialog(tableModel, parent),
    ui(new Ui::addPosition)
{
    ui->setupUi(this);
    this->setWindowTitle("Ավելացնել պաշտոն");

    ui->schedule->setModel(Schedule::create(model->database())->getModel());

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}

/**
 * @brief addPosition::~addPosition
 */
addPosition::~addPosition()
{
    delete ui;
}

/**
 * @brief addPosition::init
 * @param record
 */
void addPosition::init(QSqlRecord &record) {

    ui->name->setText(record.value("name").toString());

    QSqlRelationalTableModel* scheduleModel = Schedule::create(model->database())->getModel();
    int scheduleCount = scheduleModel->rowCount();
    for(int i = 0; i < scheduleCount; i++) {
        if (scheduleModel->record(i).value("id").toInt() == record.value("schedule_id").toInt()) {
            ui->schedule->setCurrentIndex(i);
            break;
        }
    }
}

/**
 * @brief addPosition::clear
 */
void addPosition::clear() {
    ui->name->setText("");
    ui->schedule->setCurrentIndex(0);
}

/**
 * @brief addPosition::populateData
 * @param record
 */
void addPosition::populateData(QSqlRecord &record)
{
    record.setValue(record.indexOf("name"), QVariant(ui->name->text()));

    int scheduleId = Schedule::create(model->database())
                                        ->getModel()
                                        ->record(ui->schedule->currentIndex())
                                        .value("id").toInt();
    record.setValue(record.indexOf("schedule_id"), QVariant(scheduleId));
}
