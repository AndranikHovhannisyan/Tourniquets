#include "addphone.h"
#include "ui_addphone.h"
#include <QDate>
#include "Employer/employer.h"

#include <QDebug>

/**
 * @brief addPhone::addPhone
 * @param tableModel
 * @param parent
 */
addPhone::addPhone(QSqlRelationalTableModel *tableModel, QWidget *parent) :
    addDialog(tableModel, parent),
    ui(new Ui::addPhone)
{
    ui->setupUi(this);
    this->setWindowTitle("Ավելացնել հեռախոսահամար");

    ui->employer->setModel(Employer::create(model->database())->getModel());

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}

/**
 * @brief addPhone::~addPhone
 */
addPhone::~addPhone()
{
    delete ui;
}

/**
 * @brief addPhone::init
 * @param record
 */
void addPhone::init(QSqlRecord &record)
{
    //TODO: this is bad solution but can't find good solution yet
    QSqlRelationalTableModel* employerModel = Employer::create(model->database())->getModel();
    int employerCount = employerModel->rowCount();
    for(int i = 0; i < employerCount; i++) {
        if (employerModel->record(i).value("id").toInt() == record.value("employer_id").toInt()) {
            ui->employer->setCurrentIndex(i);
            break;
        }
    }

    ui->number->setText(record.value("phone_number").toString());
    ui->from_date->setDate(record.value("from").toDate());
    ui->to_date->setDate(record.value("to").toDate());
}

/**
 * @brief addPhone::clear
 */
void addPhone::clear() {
    ui->number->setText("");
    ui->employer->setCurrentIndex(0);
    ui->from_date->clear();
    ui->to_date->clear();
}

/**
 * @brief addPhone::populateData
 * @param record
 */
void addPhone::populateData(QSqlRecord &record) {
    record.setValue(record.indexOf("phone_number"), QVariant(ui->number->text()));
    record.setValue(record.indexOf("from"),   QVariant(ui->from_date->date()));
    record.setValue(record.indexOf("to"),     QVariant(ui->to_date->date()));

    int employerId = Employer::create(model->database())
                                        ->getModel()
                                        ->record(ui->employer->currentIndex())
                                        .value("id").toInt();
    record.setValue(record.indexOf("employer_id"), QVariant(employerId));
}
