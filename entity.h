#ifndef ENTITY_H
#define ENTITY_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QModelIndex>
#include <QSqlRecord>

class Entity : public QWidget
{
    Q_OBJECT

protected:
    QLabel *errorLabel;

public slots:
    //This function will draw all neccessary fields on the passed QMainWindow
    virtual void select(QMainWindow *mainWindow = NULL) = 0;
    virtual void destroy() = 0;
    virtual void selectRow(const QModelIndex &modelIndex){}
    virtual void edit(){}
    virtual void remove(){}
};

#endif // ENTITY_H
