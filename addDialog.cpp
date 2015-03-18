#include "addDialog.h"

addDialog::addDialog(QSqlDatabase db, QWidget *parent) :
    QDialog(parent)
{
    this->db = db;
}

addDialog::~addDialog() {
}

void addDialog::editShow(int id) {
    this->id = id;
    this->init();
    this->show();
}
