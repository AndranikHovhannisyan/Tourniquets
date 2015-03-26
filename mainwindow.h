#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtSql/QSqlDatabase>
#include <QMainWindow>
#include <QMap>
#include <QSqlRelationalTableModel>

#include "addDialog.h"
#include "adddepartment.h"
#include "addposition.h"
#include "addscheduletype.h"
#include "addschedule.h"
#include "addtourniquet.h"
#include "addemployerid.h"
#include "addemployer.h"
#include "addaddress.h"
#include "addphone.h"

#include <QModelIndex>
#include <QTableView>
#include <QGridLayout>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    QPushButton *addButton;
    QTableView  *tableView;
    QGridLayout *mainLayout;

    Ui::MainWindow *ui;
    QSqlDatabase db;
    QMap<QString, addDialog*> addItemDialog;
    QString table;
    QSqlRelationalTableModel *model;

public slots:
    void infoWindow();
    void addItem();
    void refresh(int = 0);
    void subTables();

    void edit(QModelIndex a);
};

#endif // MAINWINDOW_H
