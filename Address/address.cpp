#include "address.h"

//Initialize static members
QSqlRelationalTableModel* Address::model      = NULL;
QTableView*               Address::tableView  = NULL;
QPushButton*              Address::addButton  = NULL;
QGridLayout*              Address::mainLayout = NULL;
QString                   Address::tableName  = "address";


void Address::select(QMainWindow *mainWindow)
{
    tableView   = new QTableView;
    addButton   = new QPushButton("Ավելացնել Հասցե");
    mainLayout  = new QGridLayout;

    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
    mainWindow->centralWidget()->setLayout(mainLayout);


    tableView->setModel(Address::getModel());
}


QSqlRelationalTableModel* Address::getModel()
{
    if (!model) {
        model = new QSqlRelationalTableModel;
        model->setTable(tableName);
        model->select();
    }

    return model;
}


void Address::removeWidgets() {

}
