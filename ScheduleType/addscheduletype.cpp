#include "addscheduletype.h"
#include "ui_addscheduletype.h"
#include <QDebug>

addScheduleType::addScheduleType(QSqlRelationalTableModel *tableModel, QWidget *parent) :
    addDialog(tableModel, parent),
    ui(new Ui::addScheduleType)
{
    ui->setupUi(this);
    this->setWindowTitle("Ավելացնել գրաֆիկի տեսակ");

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}

addScheduleType::~addScheduleType()
{
    delete ui;
}

void addScheduleType::init(QSqlRecord &record) {
    ui->name->setText(record.value("name").toString());
    ui->allowLag->setTime(record.value("allow_lag").toTime());
    ui->ignoreTime->setTime(record.value("ignore_time").toTime());
}

void addScheduleType::clear() {
    ui->name->setText("");
    ui->allowLag->clear();
    ui->ignoreTime->clear();
}

void addScheduleType::populateData(QSqlRecord &record) {
    record.setValue(record.indexOf("name"), QVariant(ui->name->text()));
    record.setValue(record.indexOf("allow_lag"), QVariant(ui->allowLag->time()));
    record.setValue(record.indexOf("ignore_time"), QVariant(ui->ignoreTime->time()));
}
