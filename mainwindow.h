#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtSql/QSqlDatabase>
#include <QMainWindow>
#include <QMap>

#include "adddepartment.h"
#include "addposition.h"
#include "addscheduletype.h"
#include "addschedule.h"
#include "addtourniquet.h"
#include "addemployerid.h"
#include "addemployer.h"
#include "addaddress.h"
#include "addphone.h"

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
    QString lastTable;

public slots:
    void infoWindow();
    void addItem();
    void refresh();
};

#endif // MAINWINDOW_H
