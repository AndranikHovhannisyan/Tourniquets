#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QCheckBox>
#include <QGridLayout>
#include "addtransaction.h"

#include "viewchangableentity.h"


class Transaction : public ViewChangableEntity
{
private:
    Transaction(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    Transaction(const Transaction &);
    Transaction& operator=(const Transaction&);

    static Transaction* transaction;

    addTransaction *add_transaction;
    QPushButton *importButton;

    QCheckBox   *showOriginal;

public:
    static Transaction* create(QSqlDatabase dbConnection, QMainWindow *mainWindow = NULL);


    void createWidgets();
    void setWidgetsInLayout();
    void setSignalSlotConnections();

    void updateViewModel();

    addDialog* getAddDialog();

public slots:

    void importData();
    void destroy();

    void changeModel(int);
};

#endif // TRANSACTION_H
