#ifndef ADDEMPLOYER_H
#define ADDEMPLOYER_H

#include "addDialog.h"
#include <QMap>

namespace Ui {
class addEmployer;
}

class addEmployer : public addDialog
{
    Q_OBJECT

public:
    explicit addEmployer(QSqlDatabase db, QWidget *parent = 0);
    ~addEmployer();

    virtual void subConnections();

private:
    Ui::addEmployer *ui;
    QMap<int, int> comboIndexAddressId;
    QMap<int, int> comboIndexDepartmentId;
    QMap<int, int> comboIndexPositionId;
    QMap<int, int> comboIndexScheduleId;

    virtual void init(QSqlRecord &record);
    virtual void clear();
    virtual void populateData(QSqlRecord &record);

private slots:
    void populateLivingAddresses(int livingAddressId = 0);
    void populateRegisterAddresses(int registesrAddressId = 0);
    void populateDepartments(int departmentId = 0);
    void populatePositions(int positionId = 0);
    void populateSchedules(int scheduleId = 0);
};

#endif // ADDEMPLOYER_H
