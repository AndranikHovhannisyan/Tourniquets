#ifndef REPORT_H
#define REPORT_H

#include "entity.h"
#include <QSqlDatabase>
#include <QTableView>
#include <QGridLayout>
#include <QSqlQueryModel>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>


class Report : public Entity
{
private:
    Report(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    Report(const Report &);
    Report& operator=(const Report&);

    static Report* report;

    QSqlQueryModel *model;
    QSqlDatabase db;

    QMainWindow *parent;
    QTableView  *tableView;
    QGridLayout *mainLayout;

    QComboBox   *departments;
    QComboBox   *employers;
    QDateEdit   *dateFrom;
    QDateEdit   *dateTo;

    QPushButton *filterButton;
    QPushButton *cancelFilterButton;


public:

    static Report* create(QSqlDatabase dbConnection, QMainWindow *mainWindow = NULL);
    QSqlQueryModel* getModel();

public slots:

    void select(QMainWindow *mainWindow = NULL);
    void destroy();
    void selectRow(const QModelIndex &modelIndex);
    void filter();
    void cancelFilter();
};


#endif // REPORT_H
