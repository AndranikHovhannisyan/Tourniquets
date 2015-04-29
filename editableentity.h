#ifndef EDITABLEENTITY_H
#define EDITABLEENTITY_H

#include <QSqlRelationalTableModel>
#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QMainWindow>
#include <QSqlDatabase>
#include "entity.h"
#include "addDialog.h"


class EditableEntity : public Entity
{
protected:
    EditableEntity(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    EditableEntity(const EditableEntity &);
    EditableEntity& operator=(const EditableEntity&);

    QSqlRelationalTableModel *model;
    QSqlDatabase db;

    QMainWindow *parent;
    QTableView  *tableView;
    QGridLayout *mainLayout;
    QString      tableName;

    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *removeButton;

public:

    //This function is used to return coressponding model
    virtual QSqlRelationalTableModel* getModel();

    virtual addDialog* getAddDialog() = 0;
public slots:
    //This function will draw all neccessary fields on the passed QMainWindow
    virtual void select(QMainWindow *mainWindow = NULL);
    virtual void destroy();

    virtual void selectRow(const QModelIndex &modelIndex);
    virtual void edit();
    virtual void remove();
};

#endif // EDITABLEENTITY_H
