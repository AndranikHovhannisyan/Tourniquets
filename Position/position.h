#ifndef POSITION_H
#define POSITION_H


#include <QSqlRelationalTableModel>
#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QMainWindow>
#include <QSqlDatabase>
#include "addposition.h"
#include "entity.h"

class Position : public Entity
{
private:
    Position(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    Position(const Position &);
    Position& operator=(const Position&);

    static Position* position;

    addPosition *add_position;
    QSqlRelationalTableModel *model;
    QSqlDatabase db;

    QMainWindow *parent;
    QTableView  *tableView;
    QPushButton *addButton;
    QGridLayout *mainLayout;
    QString      tableName;

public:

    static Position* create(QSqlDatabase dbConnection, QMainWindow *mainWindow = NULL);

    //This function is used to return coressponding model
    QSqlRelationalTableModel* getModel();

    addPosition* getAddPosition();
public slots:
    //This function will draw all neccessary fields on the passed QMainWindow
    void select(QMainWindow *mainWindow = NULL);
    void destroy();
};

#endif // POSITION_H
