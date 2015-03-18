#include "addaddress.h"
#include "ui_addaddress.h"
#include <QSqlQuery>
#include <QTimer>


addAddress::addAddress(QSqlDatabase db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addAddress)
{
    ui->setupUi(this);
    this->db = db;

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(createAddress()));
}

addAddress::~addAddress()
{
    delete ui;
}

void addAddress::createAddress()
{
    int k = 90;
    QSqlQuery query;
    query.prepare("INSERT INTO address (country, city, street, h_number) VALUES(?, ?, ?, ?)");
    query.bindValue(0, ui->country->text());
    query.bindValue(1, ui->city->text());
    query.bindValue(2, ui->street->text());
    query.bindValue(3, ui->hNumber->text());
    query.exec();

    emit ready();
}
