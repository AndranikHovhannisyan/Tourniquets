#ifndef ADDRESS_H
#define ADDRESS_H

#include <QSqlRelationalTableModel>
#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include "addaddress.h"

class Address
{
private:
    Address();
    static QSqlRelationalTableModel *model;
    static QTableView *tableView;
    static QPushButton *addButton;
    static QGridLayout *mainLayout;
    static QString tableName;

public:

    //This function is used to return coressponding model
    static QSqlRelationalTableModel* getModel();

    //This function will draw all neccessary fields on the passed QMainWindow
    static void select(QMainWindow *mainWindow);

private slots:
    static void removeWidgets();
};

#endif // ADDRESS_H
