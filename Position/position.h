#ifndef POSITION_H
#define POSITION_H

#include "addposition.h"
#include "editableentity.h"

class Position : public EditableEntity
{
private:
    Position(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    Position(const Position &);
    Position& operator=(const Position&);

    static Position* position;
    addPosition *add_position;

public:

    static Position* create(QSqlDatabase dbConnection, QMainWindow *mainWindow = NULL);
    addDialog* getAddDialog();
    void setTableViewModel();

public slots:
};

#endif // POSITION_H
