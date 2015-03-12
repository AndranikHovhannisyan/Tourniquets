#ifndef ADDPOSITION_H
#define ADDPOSITION_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class addPosition;
}

class addPosition : public QDialog
{
    Q_OBJECT

public:
    explicit addPosition(QSqlDatabase db, QWidget *parent = 0);
    ~addPosition();

private:
    Ui::addPosition *ui;
};

#endif // ADDPOSITION_H
