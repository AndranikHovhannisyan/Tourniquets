#ifndef ADDEMPLOYER_H
#define ADDEMPLOYER_H

#include "addDialog.h"
#include <QComboBox>
#include <QMap>

namespace Ui {
class addEmployer;
}

class addEmployer : public addDialog
{
    Q_OBJECT

public:
    explicit addEmployer(QSqlRelationalTableModel *tableModel, QWidget *parent = 0);
    ~addEmployer();

private:
    Ui::addEmployer           *ui;
    QMap<QString, QComboBox*>  addInComboMap;
    QComboBox                 *relationComboBox;
    QSqlQueryModel            *departmentPositions;

    int livingAddress;
    int registerAddress;

    virtual void init(QSqlRecord &record);
    virtual void clear();
    virtual void populateData(QSqlRecord &record);


private slots:
    void selectCreated(int rowNumber);
    void rejectAddition();
    void initAddition();

    void populateDepartmentPositions(int departmentRow);
    void employerDepartmentPositionSave(int);
};

#endif // ADDEMPLOYER_H
