#include "addtourniquet.h"
#include "ui_addtourniquet.h"
#include <QDebug>

/**
 * @brief addTourniquet::addTourniquet
 * @param tableModel
 * @param parent
 */
addTourniquet::addTourniquet(QSqlRelationalTableModel *tableModel, QWidget *parent) :
    addDialog(tableModel, parent),
    ui(new Ui::addTourniquet)
{
    ui->setupUi(this);
    this->setWindowTitle("Ավելացնել տուրնիկետ");

    ui->type->insertItem(0, "Մուտք");
    ui->type->insertItem(1, "Ելք");

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(save()));
}

/**
 * @brief addTourniquet::~addTourniquet
 */
addTourniquet::~addTourniquet()
{
    delete ui;
}

/**
 * @brief addTourniquet::init
 * @param record
 */
void addTourniquet::init(QSqlRecord &record) {
    ui->type->setCurrentIndex(record.value("type").toInt());
    ui->number->setText(record.value("number").toString());
}

/**
 * @brief addTourniquet::clear
 */
void addTourniquet::clear() {
    ui->type->setCurrentIndex(0);
    ui->number->setText("");
}

/**
 * @brief addTourniquet::populateData
 * @param record
 */
void addTourniquet::populateData(QSqlRecord &record) {
    record.setValue(record.indexOf("type"), QVariant(ui->type->currentIndex()));
    record.setValue(record.indexOf("number"), QVariant(ui->number->text()));
}
