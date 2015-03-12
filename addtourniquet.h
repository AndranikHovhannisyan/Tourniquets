#ifndef ADDTOURNIQUET_H
#define ADDTOURNIQUET_H

#include <QDialog>

namespace Ui {
class addTourniquet;
}

class addTourniquet : public QDialog
{
    Q_OBJECT

public:
    explicit addTourniquet(QWidget *parent = 0);
    ~addTourniquet();

private:
    Ui::addTourniquet *ui;
};

#endif // ADDTOURNIQUET_H
