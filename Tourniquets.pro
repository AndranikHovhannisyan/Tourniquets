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
    adddepartment.cpp \
    addposition.cpp

HEADERS  += mainwindow.h \
    adddepartment.h \
    addposition.h

FORMS    += mainwindow.ui \
    adddepartment.ui \
    addposition.ui
