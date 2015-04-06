#ifndef TOURNIQUET_H
#define TOURNIQUET_H

#include <QSqlRelationalTableModel>
#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QMainWindow>
#include <QSqlDatabase>
#include "addtourniquet.h"

class Tourniquet
{
private:
    Tourniquet(QSqlDatabase *dbConnection, QMainWindow *mainWindow);
    Tourniquet(const Tourniquet &);
    Tourniquet& operator=(const Tourniquet&);

    static Tourniquet* tourniquet;

    addTourniquet *add_tourniquet;
    QSqlRelationalTableModel *model;
    QSqlDatabase* db;

    QMainWindow *parent;
    QTableView  *tableView;
    QPushButton *addButton;
    QGridLayout *mainLayout;
    QString      tableName;

public:

    static Tourniquet* create(QSqlDatabase *dbConnection, QMainWindow *mainWindow = NULL);

    //This function is used to return coressponding model
    QSqlRelationalTableModel* getModel();

public slots:
    //This function will draw all neccessary fields on the passed QMainWindow
    void select(QMainWindow *mainWindow = NULL);
};

#endif // TOURNIQUET_H
