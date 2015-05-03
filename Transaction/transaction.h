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

    QPushButton *importButton;

public:
    static Transaction* create(QSqlDatabase dbConnection, QMainWindow *mainWindow = NULL);

    void createWidgets();
    void setWidgetsInLayout();
    void setTableViewModel();
    void setSignalSlotConnections();

    addDialog* getAddDialog() {}

public slots:

    void importData();
};

#endif // TRANSACTION_H
