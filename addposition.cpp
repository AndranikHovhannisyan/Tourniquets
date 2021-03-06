#include "addposition.h"
#include "ui_addposition.h"
#include <QSqlTableModel>
#include <QDebug>

addPosition::addPosition(QSqlDatabase db, QWidget *parent) :
    addDialog(db, parent),
    ui(new Ui::addPosition)
{
    ui->setupUi(this);
    this->setWindowTitle("Ավելացնել պաշտոն");
    tableName = "position";


    QSqlTableModel *scheduleModel = new QSqlTableModel(this, db);
    scheduleModel->setTable("schedule");
    scheduleModel->select();

    for (int i = 0; i < scheduleModel->rowCount(); i++) {
        comboIndexScheduleId[i] = scheduleModel->record(i).value("id").toInt();
        ui->schedule->addItem(scheduleModel->record(i).value("standart_in_time").toString());
    }

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(create()));
}

addPosition::~addPosition()
{
    delete ui;
}

void addPosition::init(QSqlRecord &record) {
    ui->schedule->setCurrentIndex(comboIndexScheduleId.key(record.value("schedule_id").toInt()));
    ui->name->setText(record.value("name").toString());
}

void addPosition::claer() {
    ui->name->setText("");
    ui->schedule->setCurrentIndex(0);
}

void addPosition::populateData(QSqlRecord &record)
{
    record.setValue(record.indexOf("name"), QVariant(ui->name->text()));

    if (comboIndexScheduleId[ui->schedule->currentIndex()] != 0) {
        record.setValue(record.indexOf("schedule_id"), QVariant(comboIndexScheduleId[ui->schedule->currentIndex()]));
    }
}
