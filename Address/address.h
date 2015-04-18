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
#include "entity.h"

class Address : public Entity
{
private:
    Address(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    Address(const Address &);
    Address& operator=(const Address&);

    static Address* address;

    addAddress *add_address;
    QSqlRelationalTableModel *model;
    QSqlDatabase db;

    QMainWindow *parent;
    QTableView  *tableView;
    QPushButton *addButton;
    QGridLayout *mainLayout;
    QString      tableName;

public:

    static Address* create(QSqlDatabase dbConnection, QMainWindow *mainWindow = NULL);

    //This function is used to return coressponding model
    QSqlRelationalTableModel* getModel();

public slots:
    //This function will draw all neccessary fields on the passed QMainWindow
    void select(QMainWindow *mainWindow = NULL);
    void destroy();
};

#endif // ADDRESS_H
