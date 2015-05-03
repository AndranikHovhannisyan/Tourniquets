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
#include "viewchangableentity.h"

class Tourniquet : public ViewChangableEntity
{
private:
    Tourniquet(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    Tourniquet(const Tourniquet &);
    Tourniquet& operator=(const Tourniquet&);

    static Tourniquet* tourniquet;

    addTourniquet *add_tourniquet;

public:

    static Tourniquet* create(QSqlDatabase dbConnection, QMainWindow *mainWindow = NULL);

    addDialog* getAddDialog();
    void updateViewModel();

public slots:
};

#endif // TOURNIQUET_H
