#ifndef VIEWCHANGABLEENTITY_H
#define VIEWCHANGABLEENTITY_H

#include "editableentity.h"
#include "QSqlQueryModel"

class ViewChangableEntity : public EditableEntity
{
protected:
    ViewChangableEntity(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    ViewChangableEntity(const ViewChangableEntity &);
    ViewChangableEntity& operator=(const ViewChangableEntity&);

    QSqlQueryModel           *viewModel;

public:

    virtual QSqlRelationalTableModel* getModel();
    virtual QSqlQueryModel* getViewModel();
    virtual void setTableViewModel();
    virtual void setSignalSlotConnections();

public slots:

    virtual void updateView(int,QSqlRecord&){updateViewModel();}
    virtual void updateView(QModelIndex,QModelIndex){updateViewModel();}
    virtual void updateViewModel() = 0;
};

#endif // VIEWCHANGABLEENTITY_H
