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
#include "editableentity.h"

class Address : public EditableEntity
{
private:
    Address(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    Address(const Address &);
    Address& operator=(const Address&);

    static Address* address;

    addAddress *add_address;

public:

    static Address* create(QSqlDatabase dbConnection, QMainWindow *mainWindow = NULL);
    addDialog* getAddDialog();

public slots:
};

#endif // ADDRESS_H
