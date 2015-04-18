#ifndef ENTITY_H
#define ENTITY_H

#include <QWidget>
#include <QMainWindow>

class Entity : public QWidget
{
    Q_OBJECT
public slots:
    //This function will draw all neccessary fields on the passed QMainWindow
    virtual void select(QMainWindow *mainWindow = NULL) = 0;
    virtual void destroy() = 0;
};

#endif // ENTITY_H