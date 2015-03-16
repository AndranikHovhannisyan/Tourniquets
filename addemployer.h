#ifndef ADDEMPLOYER_H
#define ADDEMPLOYER_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class addEmployer;
}

class addEmployer : public QDialog
{
    Q_OBJECT

public:
    explicit addEmployer(QSqlDatabase db, QWidget *parent = 0);
    ~addEmployer();

private:
    Ui::addEmployer *ui;
};

#endif // ADDEMPLOYER_H
