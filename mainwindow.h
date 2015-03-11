#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtSql/QSqlDatabase>
#include <QMainWindow>

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

public slots:
    void infoWindow();
    void addItem();

};

#endif // MAINWINDOW_H
