#include "Employer/employer.h"
#include <QException>
#include <QSqlRelation>
#include <QObject>


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
Employer::Employer(QSqlDatabase dbConnection, QMainWindow *mainWindow) {
    model       = NULL;
    db          = dbConnection;
    parent      = mainWindow;
    tableName   = "employer";


    setNullRegisterAddressFields();
    setNullLivingAddressFields();

    phone_numbers = NULL;
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
 * @brief Employer::select
 * @param mainWindow
 */
void Employer::select(QMainWindow *mainWindow)
{
    if (mainWindow) {
        parent = mainWindow;
    }
    if (!parent) {
        throw new QException();
    }

    //Create widgets
    tableView    = new QTableView(mainWindow);
    addButton    = new QPushButton("Ավելացնել");
    editButton   = new QPushButton("Խմբագրել");
    removeButton = new QPushButton("Հեռացնել");
    mainLayout   = new QGridLayout;

    //Arrange widgets on window
    mainLayout->addWidget(addButton, 0, 0, 1, 2);
    mainLayout->addWidget(editButton, 0, 2, 1, 2);
    mainLayout->addWidget(removeButton, 0, 4, 1, 2);
    mainLayout->addWidget(tableView, 1, 0, 15, 15);
    parent->centralWidget()->setLayout(mainLayout);

    //Set tableView content
    tableView->setModel(getModel());
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


    //Create addEmployer instance
    add_employer = new addEmployer(getModel());

    //Connect add new and edit SIGNAL / SLOTS
    QObject::connect(addButton,    SIGNAL(clicked()), add_employer, SLOT(initialize()));
    QObject::connect(editButton,   SIGNAL(clicked()), this, SLOT(edit()));
    QObject::connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));

    QObject::connect(tableView, SIGNAL(pressed(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(selectRow(QModelIndex)));
    QObject::connect(tableView, SIGNAL(doubleClicked(QModelIndex)), add_employer, SLOT(initialize(QModelIndex)));

    //Connect mainWindow destroy with removeWidgets to remove dynamic objects
    QObject::connect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}


#include <QDataWidgetMapper>
#include <QSqlRelationalDelegate>
#include "Address/address.h"
#include "Phone/phone.h"

/**
 * @brief Employer::selectRow
 * @param modelIndex
 */
void Employer::selectRow(const QModelIndex &modelIndex) {
    tableView->selectRow(modelIndex.row());


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

        mainLayout->addWidget(livingAddressFrame, 7, 16, 5, 5);

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


    //============================================================
    //======================== Phone Number ======================
    //============================================================

    QSqlRelationalTableModel* phoneModel = Phone::create(model->database())->getModel();
    int employer_id = getModel()->record(modelIndex.row()).value("id").toInt();
    phoneModel->setFilter("employer_id = " + QString::number(employer_id));
    phoneModel->select();


    phone_numbers = phone_numbers ? phone_numbers : new QTableView;
    phone_numbers->setModel(phoneModel);
    phone_numbers->hideColumn(0);
    phone_numbers->setColumnWidth(1, 70);
    phone_numbers->setColumnWidth(2, 70);
    phone_numbers->setColumnWidth(3, 140);
    phone_numbers->setFixedSize(QSize(299, 87));
    mainLayout->addWidget(phone_numbers, 17, 0, 2, 6);



    //============================================================
    //===================== End Phone Number =====================
    //============================================================
}

/**
 * @brief Employer::edit
 */
void Employer::edit()
{
    QModelIndexList selectedRows = tableView->selectionModel()->selectedRows();
    if (selectedRows.count() == 0) {
        QMessageBox::warning(NULL, "Error", "Ոչ մի տող նշված չէ");
        return;
    }

    if (selectedRows.count() > 1) {
        QMessageBox::warning(NULL, "Error", "Խմբագրման համար անհրաժեշտ է նշել ճիշտ մեկ տող");
        return;
    }

    add_employer->initByRowNumber(selectedRows.at(0).row());
}

/**
 * @brief Employer::remove
 */
void Employer::remove()
{
    QModelIndexList selectedRows = tableView->selectionModel()->selectedRows();
    for( int i = 0; i < selectedRows.count(); i++) {
        getModel()->removeRow(selectedRows.at(i).row());
    }

    getModel()->select();
}

/**
 * @brief Employer::getModel
 * @return
 */
QSqlRelationalTableModel* Employer::getModel()
{
    //Check if model isn't created create it
    if (!model) {
        model = new QSqlRelationalTableModel(parent, db);
        model->setTable(tableName);
        model->setFilter("");
        model->select();
    }

    return model;
}

/**
 * @brief Employer::destroy
 */
void Employer::destroy()
{
    delete tableView;
    delete addButton;
    delete mainLayout;
    delete editButton;
    delete removeButton;

    tableView    = NULL;
    addButton    = NULL;
    mainLayout   = NULL;
    editButton   = NULL;
    removeButton = NULL;

    QObject::disconnect(parent, SIGNAL(destroyed()), this,  SLOT(destroy()));
}
