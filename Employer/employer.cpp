#include "Employer/employer.h"
#include <QException>
#include <QSqlRelation>
#include <QObject>
#include <QDataWidgetMapper>
#include <QSqlRelationalDelegate>
#include "Address/address.h"
#include "Phone/phone.h"
#include <QScrollBar>

#include <QModelIndexList>
#include <QMessageBox>


Employer* Employer::employer = NULL;

/**
 * Create singleton object of Employer
 *
 * @brief Employer::create
 * @param dbConnection
 * @param mainWindow
 * @return
 */
Employer* Employer::create(QSqlDatabase dbConnection, QMainWindow *mainWindow)
{
    if (!employer) {
        employer = new Employer(dbConnection, mainWindow);
    }

    return employer;
}

/**
 * @brief Employer::Employer
 */
Employer::Employer(QSqlDatabase dbConnection, QMainWindow *mainWindow):
    ViewChangableEntity(dbConnection, mainWindow)
{
    tableName    = "employer";
    add_employer = NULL;

    setNullRegisterAddressFields();
    setNullLivingAddressFields();

    phone_numbers              = NULL;
    phone_number_label         = NULL;

    department_positions       = NULL;
    department_positions_label = NULL;

    employer_ids               = NULL;
    employer_ids_label         = NULL;
}

/**
 * @brief Employer::setTableViewModel
 */
void Employer::setTableViewModel()
{
    ViewChangableEntity::setTableViewModel();
    tableView->resizeColumnsToContents();

    getModel()->setHeaderData(1,  Qt::Horizontal, "Անուն");
    getModel()->setHeaderData(2,  Qt::Horizontal, "Ազգանուն");
    getModel()->setHeaderData(3,  Qt::Horizontal, "Հայրանուն");
    getModel()->setHeaderData(4,  Qt::Horizontal, "Ծննդյան ամսաթիվ");
    getModel()->setHeaderData(5,  Qt::Horizontal, "Անձնագրի սերիա");
    getModel()->setHeaderData(6,  Qt::Horizontal, "Անձնագրի համար");
    getModel()->setHeaderData(7,  Qt::Horizontal, "Տրման ամսաթիվ");
    getModel()->setHeaderData(8,  Qt::Horizontal, "Ում կողմից");
    getModel()->setHeaderData(9,  Qt::Horizontal, "Սեռը");
    getModel()->setHeaderData(10, Qt::Horizontal, "Զինապարտություն");
    getModel()->setHeaderData(11, Qt::Horizontal, "Ընտանեկան վիճակ");
    getModel()->setHeaderData(12, Qt::Horizontal, "Երեխաների քանակ");
    getModel()->setHeaderData(13, Qt::Horizontal, "Անչափահաս երեխաների քանակ");
    getModel()->setHeaderData(16, Qt::Horizontal, "Գրաֆիկ");
    getModel()->setHeaderData(17, Qt::Horizontal, "Բաժին");

    tableView->hideColumn(0);  //Hide Id
    tableView->hideColumn(14); //Hide register address id
    tableView->hideColumn(15); //Hide living address id
}


/**
 * @brief Employer::selectRow
 * @param modelIndex
 */
void Employer::selectRow(const QModelIndex &modelIndex)
{
    ViewChangableEntity::selectRow(modelIndex);


    QSqlRelationalTableModel* addressModel = Address::create(model->database())->getModel();
    int addressCount = addressModel->rowCount();

    //============================================================
    //====================== Register Address ====================
    //============================================================

    int registerAddressId = getModel()->record(modelIndex.row()).value("register_address_id").toInt();
    if (registerAddressId == 0) {
        if (registerAddressFrame) {
            delete registerAddressFrame;
        }
        setNullRegisterAddressFields();
    }
    else {

        registerAddressFrame  = registerAddressFrame  ? registerAddressFrame  : new QFrame;
        registerAddressLayout = registerAddressLayout ? registerAddressLayout : new QGridLayout;
        reg_title_label       = reg_title_label       ? reg_title_label       : new QLabel;

        label_reg_country     = label_reg_country     ? label_reg_country     : new QLabel("Country");
        label_reg_city        = label_reg_city        ? label_reg_city        : new QLabel("City");
        label_reg_street      = label_reg_street      ? label_reg_street      : new QLabel("Street");
        label_reg_hNumber     = label_reg_hNumber     ? label_reg_hNumber     : new QLabel("H_Number");

        reg_country           = reg_country           ? reg_country           : new QLineEdit;
        reg_city              = reg_city              ? reg_city              : new QLineEdit;
        reg_street            = reg_street            ? reg_street            : new QLineEdit;
        reg_hNumber           = reg_hNumber           ? reg_hNumber           : new QLineEdit;


        reg_title_label->setText("<b>Գրանցման հասցե</b>");
        reg_title_label->setAlignment(Qt::AlignCenter);
        registerAddressLayout->addWidget(reg_title_label, 0, 0, 1, 2);
        registerAddressLayout->addWidget(label_reg_country, 1, 0);
        registerAddressLayout->addWidget(label_reg_city, 2, 0);
        registerAddressLayout->addWidget(label_reg_street, 3, 0);
        registerAddressLayout->addWidget(label_reg_hNumber, 4, 0);

        registerAddressLayout->addWidget(reg_country, 1, 1);
        registerAddressLayout->addWidget(reg_city, 2, 1);
        registerAddressLayout->addWidget(reg_street, 3, 1);
        registerAddressLayout->addWidget(reg_hNumber, 4, 1);

        registerAddressFrame->setLayout(registerAddressLayout);

        registerAddressFrame->setObjectName("register_address_frame");
        registerAddressFrame->setStyleSheet("#register_address_frame { border: 1px solid black; border-radius: 4px; padding: 2px; }");
        registerAddressFrame->setFixedHeight(170);

        mainLayout->addWidget(registerAddressFrame, 1, 16, 5, 5);

        QDataWidgetMapper *register_mapper = new QDataWidgetMapper();
        register_mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
        register_mapper->setModel(Address::create(model->database())->getModel());
        register_mapper->setItemDelegate(new QSqlRelationalDelegate());
        register_mapper->addMapping(reg_country, 1);
        register_mapper->addMapping(reg_city,    2);
        register_mapper->addMapping(reg_street,  3);
        register_mapper->addMapping(reg_hNumber, 4);


        for(int i = 0; i < addressCount; i++) {
            if (addressModel->record(i).value("id").toInt() == registerAddressId) {
                 register_mapper->setCurrentIndex(i);
                 break;
            }
        }
    }

    //============================================================
    //==================== End Register Address ==================
    //============================================================


    //============================================================
    //======================= Living Address =====================
    //============================================================

    int livingAddressId = getModel()->record(modelIndex.row()).value("living_address_id").toInt();
    if (livingAddressId == 0) {
        if (livingAddressFrame) {
            delete livingAddressFrame;
        }
        setNullLivingAddressFields();
    }
    else {

        livingAddressFrame     = livingAddressFrame   ? livingAddressFrame   : new QFrame;
        livingAddressLayout    = livingAddressLayout  ? livingAddressLayout  : new QGridLayout;
        living_title_label     = living_title_label   ? living_title_label   : new QLabel;

        label_living_country   = label_living_country ? label_living_country : new QLabel("Country");
        label_living_city      = label_living_city    ? label_living_city    : new QLabel("City");
        label_living_street    = label_living_street  ? label_living_street  : new QLabel("Street");
        label_living_hNumber   = label_living_hNumber ? label_living_hNumber : new QLabel("H_Number");

        living_country         = living_country       ? living_country       : new QLineEdit;
        living_city            = living_city          ? living_city          : new QLineEdit;
        living_street          = living_street        ? living_street        : new QLineEdit;
        living_hNumber         = living_hNumber       ? living_hNumber       : new QLineEdit;


        living_title_label->setText("<b>Բնակության հասցե</b>");
        living_title_label->setAlignment(Qt::AlignCenter);
        livingAddressLayout->addWidget(living_title_label, 0, 0, 1, 2);
        livingAddressLayout->addWidget(label_living_country, 1, 0);
        livingAddressLayout->addWidget(label_living_city, 2, 0);
        livingAddressLayout->addWidget(label_living_street, 3, 0);
        livingAddressLayout->addWidget(label_living_hNumber, 4, 0);

        livingAddressLayout->addWidget(living_country, 1, 1);
        livingAddressLayout->addWidget(living_city, 2, 1);
        livingAddressLayout->addWidget(living_street, 3, 1);
        livingAddressLayout->addWidget(living_hNumber, 4, 1);

        livingAddressFrame->setLayout(livingAddressLayout);

        livingAddressFrame->setObjectName("living_address_frame");
        livingAddressFrame->setStyleSheet("#living_address_frame { border: 1px solid black; border-radius: 4px; padding: 2px; }");
        livingAddressFrame->setFixedHeight(170);

        mainLayout->addWidget(livingAddressFrame, 6, 16, 5, 5);

        QDataWidgetMapper *living_mapper = new QDataWidgetMapper();
        living_mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
        living_mapper->setModel(Address::create(model->database())->getModel());
        living_mapper->setItemDelegate(new QSqlRelationalDelegate());
        living_mapper->addMapping(living_country, 1);
        living_mapper->addMapping(living_city,    2);
        living_mapper->addMapping(living_street,  3);
        living_mapper->addMapping(living_hNumber, 4);

        for(int i = 0; i < addressCount; i++) {
            if (addressModel->record(i).value("id").toInt() == livingAddressId) {
                 living_mapper->setCurrentIndex(i);
                 break;
            }
        }
    }

    //============================================================
    //===================== End Living Address ===================
    //============================================================


    int employer_id = getModel()->record(modelIndex.row()).value("id").toInt();

    //============================================================
    //======================== Phone Number ======================
    //============================================================

    QSqlRelationalTableModel* phoneModel = Phone::create(model->database())->getModel();
    phoneModel->setFilter("employer_id = " + QString::number(employer_id));
    phoneModel->select();

    if (phoneModel->rowCount())
    {
        phone_numbers = phone_numbers ? phone_numbers : new QTableView;
        phone_numbers->setModel(phoneModel);
        phone_numbers->hideColumn(0);
        phone_numbers->setColumnWidth(1, 70);
        phone_numbers->setColumnWidth(2, 70);
        phone_numbers->setColumnWidth(3, 140);
        phone_numbers->setFixedHeight(120);

        phone_numbers->verticalScrollBar()->setStyleSheet(
            "QScrollBar:vertical { width: 1px; }");

        phone_number_label = phone_number_label ? phone_number_label : new QLabel("<b>Հեռախոսահամարներ</b>");
        phone_number_label->setAlignment(Qt::AlignCenter);
        phone_number_label->setFixedWidth(305);

        mainLayout->addWidget(phone_number_label, 17, 0, 1, 4);
        mainLayout->addWidget(phone_numbers, 18, 0, 2, 4);
    }
    else {
        delete phone_numbers;
        delete phone_number_label;
        phone_numbers      = NULL;
        phone_number_label = NULL;
    }

    //============================================================
    //===================== End Phone Number =====================
    //============================================================


    //============================================================
    //==================== Department Position ===================
    //============================================================

    QSqlQueryModel* employerDepartmentPosition = new QSqlQueryModel;
    employerDepartmentPosition->setQuery("SELECT d.name, p.name, edp.from, edp.to "\
                                         "FROM employer_dep_positions as edp "\
                                         "JOIN dep_positions as dp ON edp.dep_positions_id = dp.id "\
                                         "JOIN department as d ON dp.department_id = d.id "\
                                         "JOIN position as p ON dp.position_id = p.id "\
                                         "WHERE edp.employer_id = " + QString::number(employer_id) + " "\
                                         "ORDER BY edp.id");

    if (employerDepartmentPosition->rowCount())
    {
        employerDepartmentPosition->setHeaderData(0,  Qt::Horizontal, "Բաժին");
        employerDepartmentPosition->setHeaderData(1,  Qt::Horizontal, "Պաշտոն");

        department_positions = department_positions ? department_positions : new QTableView;
        department_positions->setModel(employerDepartmentPosition);
        department_positions->setFixedHeight(120);

        department_positions->verticalScrollBar()->setStyleSheet(
            "QScrollBar:vertical { width: 1px; }");

        department_positions_label = department_positions_label ? department_positions_label : new QLabel("<b>Պաշտոններ</b>");
        department_positions_label->setAlignment(Qt::AlignCenter);

        mainLayout->addWidget(department_positions_label, 17, 5, 1, 7);
        mainLayout->addWidget(department_positions, 18, 5, 2, 7);
    }
    else {
        delete department_positions;
        delete department_positions_label;
        department_positions       = NULL;
        department_positions_label = NULL;
    }

    //============================================================
    //================= End Department Position ==================
    //============================================================


    //============================================================
    //======================== Employer ID =======================
    //============================================================

    QSqlQueryModel* employerEmployerId = new QSqlQueryModel;
    employerEmployerId->setQuery("SELECT ei.emp_number, ei.id_type, eei.from, eei.to "\
                                 "FROM employer_employer_ids as eei "\
                                 "JOIN employer_ids as ei ON eei.emp_number = ei.emp_number "\
                                 "WHERE eei.employer_id = " + QString::number(employer_id) + " "\
                                 "ORDER BY eei.id");

    if (employerEmployerId->rowCount())
    {
        employerEmployerId->setHeaderData(0,  Qt::Horizontal, "ԻԴ համար");
        employerEmployerId->setHeaderData(1,  Qt::Horizontal, "ԻԴ֊ի տեսակը");

        employer_ids = employer_ids ? employer_ids : new QTableView;
        employer_ids->setModel(employerEmployerId);
        employer_ids->setFixedHeight(120);
        employer_ids->verticalScrollBar()->setStyleSheet(
            "QScrollBar:vertical { width: 1px; }");

        employer_ids_label = employer_ids_label ? employer_ids_label : new QLabel("<b>Իդենտիֆիկացիոն համարներ</b>");
        employer_ids_label->setAlignment(Qt::AlignCenter);

        mainLayout->addWidget(employer_ids_label, 17, 13, 1, 7);
        mainLayout->addWidget(employer_ids, 18, 13, 2, 7);
    }
    else {
        delete employer_ids;
        delete employer_ids_label;
        employer_ids       = NULL;
        employer_ids_label = NULL;
    }

    //============================================================
    //====================== End Employer ID =====================
    //============================================================
}


/**
 * @brief Employer::destroy
 */
void Employer::destroy()
{
    ViewChangableEntity::destroy();

    delete phone_numbers;
    delete phone_number_label;
    phone_numbers      = NULL;
    phone_number_label = NULL;

    delete department_positions;
    delete department_positions_label;
    department_positions       = NULL;
    department_positions_label = NULL;

    delete employer_ids;
    delete employer_ids_label;
    employer_ids       = NULL;
    employer_ids_label = NULL;

    delete registerAddressFrame;
    delete livingAddressFrame;

    setNullRegisterAddressFields();
    setNullLivingAddressFields();
}

/**
 * @brief Employer::setNullRegisterAddressFields
 */
void Employer::setNullRegisterAddressFields()
{
    registerAddressFrame  = NULL;
    registerAddressLayout = NULL;
    reg_title_label       = NULL;

    label_reg_country     = NULL;
    label_reg_city        = NULL;
    label_reg_street      = NULL;
    label_reg_hNumber     = NULL;

    reg_country           = NULL;
    reg_city              = NULL;
    reg_street            = NULL;
    reg_hNumber           = NULL;
}


/**
 * @brief Employer::setNullLivingAddressFields
 */
void Employer::setNullLivingAddressFields()
{
    livingAddressFrame    = NULL;
    livingAddressLayout   = NULL;
    living_title_label    = NULL;

    label_living_country  = NULL;
    label_living_city     = NULL;
    label_living_street   = NULL;
    label_living_hNumber  = NULL;

    living_country        = NULL;
    living_city           = NULL;
    living_street         = NULL;
    living_hNumber        = NULL;
}

/**
 * @brief Employer::updateViewModel
 */
void Employer::updateViewModel()
{
    ViewChangableEntity::updateViewModel();

    viewModel->setQuery("SELECT * "\
                        "FROM employer as e");
}

/**
 * @brief getAddDialog
 * @return
 */
addDialog* Employer::getAddDialog()
{
    add_employer = add_employer ? add_employer : new addEmployer(getModel());
    return add_employer ;
}
