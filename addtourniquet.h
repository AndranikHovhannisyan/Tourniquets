#ifndef ADDTOURNIQUET_H
#define ADDTOURNIQUET_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class addTourniquet;
}

class addTourniquet : public QDialog
{
    Q_OBJECT

public:
    explicit addTourniquet(QSqlDatabase db, QWidget *parent = 0);
    ~addTourniquet();

private:
    Ui::addTourniquet *ui;
    QSqlDatabase db;
};

#endif // ADDTOURNIQUET_H
