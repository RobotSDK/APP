#-------------------------------------------------
#
# Project created by QtCreator 2014-10-10T10:48:28
#
#-------------------------------------------------

QT       += core gui xml opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

HEADERS += ./kitti_dataset_viewer.h
SOURCES += ./kitti_dataset_viewer.cpp \
    ./main.cpp
FORMS += ./kitti_dataset_viewer.ui

PROJNAME = KITTI_Dataset_Viewer
INSTALLTYPE = APP

INSTTYPE = APP
include(RobotSDK_Main.pri)