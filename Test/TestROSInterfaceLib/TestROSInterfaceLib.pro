#-------------------------------------------------
#
# Project created by QtCreator 2014-11-02T15:36:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestROSInterfaceLib
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


INCLUDEPATH += $$(HOME)/SDK/ROSInterface/include

CONFIG(debug, debug|release){
    LIBS += -L$$(HOME)/SDK/ROSInterface/lib/ -lROSInterface_Debug
}
else {
    LIBS += -L$$(HOME)/SDK/ROSInterface/lib/ -lROSInterface_Release
}

unix {
    INCLUDEPATH += /opt/ros/indigo/include

    LIBS += -L/opt/ros/indigo/lib -lroscpp
    LIBS += -L/opt/ros/indigo/lib -lrosconsole
    LIBS += -L/opt/ros/indigo/lib -lroscpp_serialization
    LIBS += -L/opt/ros/indigo/lib -lrostime
    LIBS += -L/opt/ros/indigo/lib -lxmlrpcpp
    LIBS += -L/opt/ros/indigo/lib -lcpp_common
    LIBS += -L/opt/ros/indigo/lib -lrosconsole_log4cxx
    LIBS += -L/opt/ros/indigo/lib -lrosconsole_backend_interface
    LIBS += -L/usr/lib/x86_64-linux-gnu -lboost_system
}

PROJNAME = TestROSInterfaceLib
INSTTYPE = APP
include(RobotSDK_Main.pri)