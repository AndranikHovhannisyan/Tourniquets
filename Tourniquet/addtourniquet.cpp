#include "addtourniquet.h"
#include "ui_addtourniquet.h"
#include <QDebug>

addTourniquet::addTourniquet(QSqlDatabase db, QWidget *parent) :
    addDialog(db, parent),
    ui(new Ui::addTourniquet)
{
    ui->setupUi(this);
    this->setWindowTitle("Ավելացնել տուրնիկետ");
    tableName = "tourniquet";

    ui->type->insertItem(0, "Մուտք");
    ui->type->insertItem(1, "Ելք");

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(create()));
}

addTourniquet::~addTourniquet()
{
    delete ui;
}

void addTourniquet::init(QSqlRecord &record) {
    ui->type->setCurrentIndex(record.value("type").toInt());
    ui->number->setText(record.value("number").toString());
}

void addTourniquet::claer() {
    ui->type->setCurrentIndex(0);
    ui->number->setText("");
}

void addTourniquet::populateData(QSqlRecord &record) {
    qDebug() << ui->type->currentIndex();

    record.setValue(record.indexOf("type"), QVariant(ui->type->currentIndex()));
    record.setValue(record.indexOf("number"), QVariant(ui->number->text()));
}
