#ifndef PHONE_H
#define PHONE_H

#include <QSqlRelationalTableModel>
#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QMainWindow>
#include <QSqlDatabase>
#include "addphone.h"

class Phone
{
private:
    Phone(QSqlDatabase *dbConnection, QMainWindow *mainWindow);
    Phone(const Phone &);
    Phone& operator=(const Phone&);

    static Phone* phone;

    addPhone *add_phone;
    QSqlRelationalTableModel *model;
    QSqlDatabase* db;

    QMainWindow *parent;
    QTableView  *tableView;
    QPushButton *addButton;
    QGridLayout *mainLayout;
    QString      tableName;

public:

    static Phone* create(QSqlDatabase *dbConnection, QMainWindow *mainWindow);

    //This function is used to return coressponding model
    QSqlRelationalTableModel* getModel();

public slots:
    //This function will draw all neccessary fields on the passed QMainWindow
    void select();
};

#endif // PHONE_H
