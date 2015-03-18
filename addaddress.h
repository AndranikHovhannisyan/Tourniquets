#ifndef ADDADDRESS_H
#define ADDADDRESS_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class addAddress;
}

class addAddress : public QDialog
{
    Q_OBJECT

public:
    explicit addAddress(QSqlDatabase db, QWidget *parent = 0);
    ~addAddress();

private:
    Ui::addAddress *ui;
    QSqlDatabase db;

private slots:
    void createAddress();

signals:
    void ready();
};

#endif // ADDADDRESS_H
