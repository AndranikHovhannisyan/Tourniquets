#-------------------------------------------------
#
# Project created by QtCreator 2015-03-11T00:13:16
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tourniquets
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addDialog.cpp \
    Department/adddepartment.cpp \
    Employer/addemployer.cpp \
    EmployerId/addemployerid.cpp \
    Phone/addphone.cpp \
    Position/addposition.cpp \
    Schedule/addschedule.cpp \
    ScheduleType/addscheduletype.cpp \
    Tourniquet/addtourniquet.cpp \
    Address/addaddress.cpp \
    Address/address.cpp \
    Department/department.cpp \
    Employer/employer.cpp \
    EmployerId/employerid.cpp \
    Phone/phone.cpp \
    Position/position.cpp \
    Schedule/schedule.cpp \
    ScheduleType/scheduletype.cpp \
    Tourniquet/tourniquet.cpp \
    Department_Position/department_position.cpp \
    Employer_DepPosition/employer_depposition.cpp

HEADERS  += mainwindow.h \
    constants.h \
    addDialog.h \
    Department/adddepartment.h \
    Employer/addemployer.h \
    EmployerId/addemployerid.h \
    Phone/addphone.h \
    Position/addposition.h \
    Schedule/addschedule.h \
    ScheduleType/addscheduletype.h \
    Tourniquet/addtourniquet.h \
    Address/addaddress.h \
    Address/address.h \
    Department/department.h \
    Employer/employer.h \
    EmployerId/employerid.h \
    Phone/phone.h \
    Position/position.h \
    Schedule/schedule.h \
    ScheduleType/scheduletype.h \
    Tourniquet/tourniquet.h \
    entity.h \
    Department_Position/department_position.h \
    Employer_DepPosition/employer_depposition.h

FORMS    += mainwindow.ui \
    Department/adddepartment.ui \
    Employer/addemployer.ui \
    EmployerId/addemployerid.ui \
    Phone/addphone.ui \
    Position/addposition.ui \
    Schedule/addschedule.ui \
    ScheduleType/addscheduletype.ui \
    Tourniquet/addtourniquet.ui \
    Address/addaddress.ui
