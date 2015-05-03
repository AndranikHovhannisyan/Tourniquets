#include "Transaction/addtransaction.h"
#include "ui_addtransaction.h"
#include "EmployerId/employerid.h"
#include "Tourniquet/tourniquet.h"

/**
 * @brief addTransaction::addTransaction
 * @param tableModel
 * @param parent
 */
addTransaction::addTransaction(QSqlRelationalTableModel *tableModel, QWidget *parent) :
    addDialog(tableModel, parent),
    ui(new Ui::addTransaction)
{
    ui->setupUi(this);
    this->setWindowTitle("Ավելացնել տրանզակցիյա");

    ui->employerID->setModel(EmployerId::create(model->database())->getModel());
    ui->tourniquet->setModel(Tourniquet::create(model->database())->getModel());


    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}

/**
 * @brief addTransaction::~addTransaction
 */
addTransaction::~addTransaction()
{
    delete ui;
}

#include <QDebug>

/**
 * @brief addTransaction::init
 * @param record
 */
void addTransaction::init(QSqlRecord &record)
{
    qDebug() << record.value("date_time").toDateTime();
    ui->date_time->setDateTime(record.value("date_time").toDateTime());

    QSqlRelationalTableModel* employerIdModel = EmployerId::create(model->database())->getModel();
    int employerIdCount = employerIdModel->rowCount();
    for(int i = 0; i < employerIdCount; i++) {
        if (employerIdModel->record(i).value("emp_number").toString() == record.value("emp_number").toString()) {
            ui->employerID->setCurrentIndex(i);
            break;
        }
    }

    QSqlRelationalTableModel* tourniquetModel = Tourniquet::create(model->database())->getModel();
    int tourniquetCount = tourniquetModel->rowCount();
    for(int i = 0; i < tourniquetCount; i++) {
        if (tourniquetModel->record(i).value("number").toInt() == record.value("tourniquet_number").toInt()) {
            ui->tourniquet->setCurrentIndex(i);
            break;
        }
    }
}

/**
 * @brief addTourniquet::clear
 */
void addTransaction::clear() {
    ui->employerID->setCurrentIndex(-1);
    ui->tourniquet->setCurrentIndex(-1);
}

/**
 * @brief addTourniquet::populateData
 * @param record
 */
void addTransaction::populateData(QSqlRecord &record)
{
    record.setValue(record.indexOf("date_time"), QVariant(ui->date_time->dateTime()));


    QString employerNumber = EmployerId::create(model->database())
                                        ->getModel()
                                        ->record(ui->employerID->currentIndex())
                                        .value("emp_number").toString();
    record.setValue(record.indexOf("emp_number"), QVariant(employerNumber));


    int tourniquetNumber = Tourniquet::create(model->database())
                                        ->getModel()
                                        ->record(ui->tourniquet->currentIndex())
                                        .value("number").toInt();
    record.setValue(record.indexOf("tourniquet_number"), QVariant(tourniquetNumber));

}
