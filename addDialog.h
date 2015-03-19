#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlRecord>

class addDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addDialog(QSqlDatabase db, QWidget *parent = 0);
    ~addDialog();
protected:
    QSqlDatabase db;
    int id;
    QString tableName;
    QString IdField;

    virtual void init(QSqlRecord &) = 0;
    virtual void claer() = 0;
    virtual void populateData(QSqlRecord &) = 0;
    virtual void initialize();

public slots:
    void editShow(int id);

private slots:
    void create();

signals:
    void ready();
};

#endif // ADDDIALOG_H
