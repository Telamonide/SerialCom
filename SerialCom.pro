#-------------------------------------------------
#
# Project created by QtCreator 2013-08-24T02:26:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialCom
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

include(C:\Qt\qextserialport-1.2rc\src\qextserialport.pri)
