#ifndef ADDRESS_H
#define ADDRESS_H

#include <QSqlRelationalTableModel>
#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QMainWindow>
#include <QSqlDatabase>
#include "addaddress.h"

class Address
{
private:
    Address(QSqlDatabase *dbConnection);
    Address(const Address &);
    Address& operator=(const Address&);

    static Address* address;

    addAddress *add_address;
    QSqlRelationalTableModel *model;
    QSqlDatabase* db;

    QMainWindow *parent;
    QTableView  *tableView;
    QPushButton *addButton;
    QGridLayout *mainLayout;
    QString tableName;

public:

    static Address* create(QSqlDatabase *dbConnection);

    //This function is used to return coressponding model
    QSqlRelationalTableModel* getModel();

    //This function will draw all neccessary fields on the passed QMainWindow
    void select(QMainWindow *mainWindow);

private slots:
    void removeWidgets();
};

#endif // ADDRESS_H
