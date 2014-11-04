#-------------------------------------------------
#
# Project created by QtCreator 2014-10-10T10:48:28
#
#-------------------------------------------------

QT       += core gui xml opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ModelExtraction
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

PROJNAME = ModelExtraction
INSTALLTYPE = APP

INSTTYPE = APP
include(RobotSDK_Main.pri)