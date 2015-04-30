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
#include "viewchangableentity.h"

class Phone : public ViewChangableEntity
{
private:
    Phone(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    Phone(const Phone &);
    Phone& operator=(const Phone&);

    static Phone* phone;
    addPhone *add_phone;

public:

    static Phone* create(QSqlDatabase dbConnection, QMainWindow *mainWindow = NULL);

    addDialog * getAddDialog();

public slots:
    void updateViewModel();
};

#endif // PHONE_H
