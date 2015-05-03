#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QGridLayout>

#include "editableentity.h"


class Transaction : public EditableEntity
{
private:
    Transaction(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    Transaction(const Transaction &);
    Transaction& operator=(const Transaction&);

    static Transaction* transaction;

public:
    static Transaction* create(QSqlDatabase dbConnection, QMainWindow *mainWindow = NULL);

    virtual void createWidgets();
    virtual void setWidgetsInLayout();
    virtual void setTableViewModel();
    virtual void setSignalSlotConnections();

    virtual addDialog* getAddDialog() {}

public slots:

};

#endif // TRANSACTION_H
