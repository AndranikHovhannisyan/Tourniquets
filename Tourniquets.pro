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
    Address/addaddress.cpp \
    Department/adddepartment.cpp \
    Employer/addemployer.cpp \
    EmployerId/addemployerid.cpp \
    Phone/addphone.cpp \
    Position/addposition.cpp \
    Schedule/addschedule.cpp \
    ScheduleType/addscheduletype.cpp \
    Tourniquet/addtourniquet.cpp

HEADERS  += mainwindow.h \
    constants.h \
    addDialog.h \
    Address/addaddress.h \
    Department/adddepartment.h \
    Employer/addemployer.h \
    EmployerId/addemployerid.h \
    Phone/addphone.h \
    Position/addposition.h \
    Schedule/addschedule.h \
    ScheduleType/addscheduletype.h \
    Tourniquet/addtourniquet.h

FORMS    += mainwindow.ui \
    Address/addaddress.ui \
    Department/adddepartment.ui \
    Employer/addemployer.ui \
    EmployerId/addemployerid.ui \
    Phone/addphone.ui \
    Position/addposition.ui \
    Schedule/addschedule.ui \
    ScheduleType/addscheduletype.ui \
    Tourniquet/addtourniquet.ui
