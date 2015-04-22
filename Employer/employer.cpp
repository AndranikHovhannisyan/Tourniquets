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


    registerAddressFrame  = NULL;
    registerAddressLayout = NULL;
    reg_title_label       = NULL;

    label_reg_country   = NULL;
    label_reg_city      = NULL;
    label_reg_street    = NULL;
    label_reg_hNumber   = NULL;

    reg_country = NULL;
    reg_city    = NULL;
    reg_street  = NULL;
    reg_hNumber = NULL;
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
    getModel()->setHeaderData(14, Qt::Horizontal, "Գրանցման հասցե");
    getModel()->setHeaderData(15, Qt::Horizontal, "Բնակության հասցե");
    getModel()->setHeaderData(16, Qt::Horizontal, "Գրաֆիկ");
    getModel()->setHeaderData(17, Qt::Horizontal, "Բաժին");



    tableView->hideColumn(0);



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

/**
 * @brief Employer::selectRow
 * @param modelIndex
 */
void Employer::selectRow(const QModelIndex &modelIndex) {
    tableView->selectRow(modelIndex.row());


    //============================================================
    //====================== Register Address ====================
    //============================================================

    registerAddressFrame  = registerAddressFrame  ? registerAddressFrame  : new QFrame;
    registerAddressLayout = registerAddressLayout ? registerAddressLayout : new QGridLayout;
    reg_title_label       = reg_title_label       ? reg_title_label         : new QLabel;

    label_reg_country   = label_reg_country ? label_reg_country : new QLabel("Country");
    label_reg_city      = label_reg_city    ? label_reg_city    : new QLabel("City");
    label_reg_street    = label_reg_street  ? label_reg_street  : new QLabel("Street");
    label_reg_hNumber   = label_reg_hNumber ? label_reg_hNumber : new QLabel("H_Number");

    reg_country = reg_country ? reg_country : new QLineEdit;
    reg_city    = reg_city    ? reg_city    : new QLineEdit;
    reg_street  = reg_street  ? reg_street  : new QLineEdit;
    reg_hNumber = reg_hNumber ? reg_hNumber : new QLineEdit;


    reg_title_label->setText("<b>Register Address</b>");
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

    mainLayout->addWidget(registerAddressFrame, 1, 16, 4, 4);

    QDataWidgetMapper *mapper = new QDataWidgetMapper();
    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    mapper->setModel(Address::create(model->database())->getModel());
    mapper->setItemDelegate(new QSqlRelationalDelegate());
    mapper->addMapping(reg_country, 1);
    mapper->addMapping(reg_city,    2);
    mapper->addMapping(reg_street,  3);
    mapper->addMapping(reg_hNumber, 4);

    int registerAddressId = getModel()->record(modelIndex.row()).value("register_address_id").toInt();

    QSqlRelationalTableModel* addressModel = Address::create(model->database())->getModel();
    int addressCount = addressModel->rowCount();
    for(int i = 0; i < addressCount; i++) {
        if (addressModel->record(i).value("id").toInt() == registerAddressId) {
             mapper->setCurrentIndex(i);
             break;
        }
    }

    //============================================================
    //==================== End Register Address ==================
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
