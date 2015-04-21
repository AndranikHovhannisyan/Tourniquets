#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlRelationalTableModel>

class addDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addDialog(QSqlRelationalTableModel* tableModel, QWidget *parent = 0);
    ~addDialog();

protected:
    QSqlRelationalTableModel* model;
    int rowNumber;

    virtual void init(QSqlRecord &) = 0;
    virtual void clear() = 0;
    virtual void populateData(QSqlRecord &) = 0;

public slots:
    void initialize(QModelIndex modelIndex = QModelIndex());
    void initByRowNumber(int = -1);

private slots:
    void save();

signals:
    void ready();
};

#endif // ADDDIALOG_H
