#ifndef ADDRESS_H
#define ADDRESS_H

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
    void setTableViewModel();

public slots:
};

#endif // ADDRESS_H
