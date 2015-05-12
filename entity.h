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

    virtual void updateView(int,QSqlRecord&){}
    virtual void updateView(QModelIndex,QModelIndex){}
    virtual void updateViewModel(){}

    virtual void reselect(QModelIndex, QModelIndex){}

    virtual void importData(){}
    virtual void changeModel(int){}

    virtual void setQuery(){}

signals:
    //After QSqlTableModel data changes need to run selectRow
    //But because parameter count don't match then we use intermediate signal/slot
    void reselect(QModelIndex);
};

#endif // ENTITY_H
