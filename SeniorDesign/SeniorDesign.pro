#-------------------------------------------------
#
# Project created by QtCreator 2014-03-08T14:59:19
#
#-------------------------------------------------

QT       += core gui
QT += concurrent widgets
QMAKE_LFLAGS += /INCREMENTAL:NO

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SeniorDesign
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    exampleprogram.cpp \
    runningdialog.cpp

HEADERS  += mainwindow.h \
    runningdialog.h

FORMS    += mainwindow.ui

#enable console
CONFIG += console
