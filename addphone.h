#ifndef ADDPHONE_H
#define ADDPHONE_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class addPhone;
}

class addPhone : public QDialog
{
    Q_OBJECT

public:
    explicit addPhone(QSqlDatabase db, QWidget *parent = 0);
    ~addPhone();

private:
    Ui::addPhone *ui;
    QSqlDatabase db;
};

#endif // ADDPHONE_H
