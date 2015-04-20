#include "addtourniquet.h"
#include "ui_addtourniquet.h"
#include <QDebug>

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

addTourniquet::~addTourniquet()
{
    delete ui;
}

void addTourniquet::init(QSqlRecord &record) {
    ui->type->setCurrentIndex(record.value("type").toInt());
    ui->number->setText(record.value("number").toString());
}

void addTourniquet::clear() {
    ui->type->setCurrentIndex(0);
    ui->number->setText("");
}

void addTourniquet::populateData(QSqlRecord &record) {
    record.setValue(record.indexOf("type"), QVariant(ui->type->currentIndex()));
    record.setValue(record.indexOf("number"), QVariant(ui->number->text()));
}
