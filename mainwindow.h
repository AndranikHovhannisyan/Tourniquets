#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtSql/QSqlDatabase>
#include <QMainWindow>
#include <QMap>

#include "adddepartment.h"
#include "addposition.h"
#include "addscheduletype.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QMap<QString, QDialog*> addItemDialog;
//    addItem["department"] =
//    addDepartment *addDepDialog;
//    addPosition *addPosDialog;

public slots:
    void infoWindow();
    void addItem();
};

#endif // MAINWINDOW_H
