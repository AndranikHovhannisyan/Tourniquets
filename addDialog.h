#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QSqlDatabase>

class addDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addDialog(QSqlDatabase db, QWidget *parent = 0);
    ~addDialog();
protected:
    QSqlDatabase db;
    int id;

    virtual void init() = 0;

public slots:
    void editShow(int id);

signals:
    void ready();
};

#endif // ADDDIALOG_H
