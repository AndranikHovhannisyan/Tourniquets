#ifndef EMPLOYER_H
#define EMPLOYER_H

#include <QLineEdit>
#include <QLabel>
#include <QFrame>

#include "addemployer.h"
#include "viewchangableentity.h"

class Employer : public ViewChangableEntity
{
private:
    Employer(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    Employer(const Employer &);
    Employer& operator=(const Employer&);

    static Employer* employer;
    addEmployer *add_employer;


    //====================== Register Address ====================

    QFrame      *registerAddressFrame;
    QGridLayout *registerAddressLayout;
    QLabel      *reg_title_label;

    QLabel      *label_reg_country;
    QLabel      *label_reg_city;
    QLabel      *label_reg_street;
    QLabel      *label_reg_hNumber;

    QLineEdit   *reg_country;
    QLineEdit   *reg_city;
    QLineEdit   *reg_street;
    QLineEdit   *reg_hNumber;


    //====================== Living Address ======================

    QFrame      *livingAddressFrame;
    QGridLayout *livingAddressLayout;
    QLabel      *living_title_label;

    QLabel      *label_living_country;
    QLabel      *label_living_city;
    QLabel      *label_living_street;
    QLabel      *label_living_hNumber;

    QLineEdit   *living_country;
    QLineEdit   *living_city;
    QLineEdit   *living_street;
    QLineEdit   *living_hNumber;


    //======================== Phone Number ======================

    QTableView  *phone_numbers;
    QLabel      *phone_number_label;


    //=================== Department Position ====================

    QTableView  *department_positions;
    QLabel      *department_positions_label;

    //======================= Employer ID ========================

    QTableView  *employer_ids;
    QLabel      *employer_ids_label;

public:

    void setNullRegisterAddressFields();
    void setNullLivingAddressFields();

    static Employer* create(QSqlDatabase dbConnection, QMainWindow *mainWindow = NULL);
    addDialog* getAddDialog();

public slots:
    void destroy();
    void selectRow(const QModelIndex &modelIndex);
    void updateViewModel();
};

#endif // EMPLOYER_H
