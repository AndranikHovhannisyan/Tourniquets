#ifndef EMPLOYER_H
#define EMPLOYER_H

#include <QSqlRelationalTableModel>
#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QMainWindow>
#include <QSqlDatabase>

#include <QLineEdit>
#include <QLabel>
#include <QFrame>

#include "addemployer.h"
#include "entity.h"

class Employer : public Entity
{
private:
    Employer(QSqlDatabase dbConnection, QMainWindow *mainWindow);
    Employer(const Employer &);
    Employer& operator=(const Employer&);

    static Employer* employer;

    addEmployer *add_employer;
    QSqlRelationalTableModel *model;
    QSqlDatabase db;

    QMainWindow *parent;
    QTableView  *tableView;

    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *removeButton;

    QGridLayout *mainLayout;
    QString      tableName;

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


public:

    void setNullRegisterAddressFields();
    void setNullLivingAddressFields();

    static Employer* create(QSqlDatabase dbConnection, QMainWindow *mainWindow = NULL);

    //This function is used to return coressponding model
    QSqlRelationalTableModel* getModel();

public slots:
    //This function will draw all neccessary fields on the passed QMainWindow
    void select(QMainWindow *mainWindow = NULL);
    void destroy();

    void selectRow(const QModelIndex &modelIndex);
    void edit();
    void remove();
};

#endif // EMPLOYER_H
