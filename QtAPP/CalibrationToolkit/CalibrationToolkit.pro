SOURCES += main.cpp\
        mainwindow.cpp
HEADERS  += mainwindow.h
FORMS    += mainwindow.ui

unix{
    INCLUDEPATH += /opt/ros/indigo/include
    INCLUDEPATH += $$(HOME)/SDK/ROSInterface/include
    INCLUDEPATH += $$(HOME)/SDK/CalibrationToolkit/include

    CONFIG(debug, debug|release){
        LIBS += -L$$(HOME)/SDK/CalibrationToolkit/lib -lCalibrationToolkit_Debug
        LIBS += -L$$(HOME)/SDK/ROSInterface/lib/ -lROSInterface_Debug

    }else{
        LIBS += -L$$(HOME)/SDK/CalibrationToolkit/lib -lCalibrationToolkit_Release
        LIBS += -L$$(HOME)/SDK/ROSInterface/lib/ -lROSInterface_Release

    }

    LIBS += -L/usr/lib/x86_64-linux-gnu -lopencv_core
    LIBS += -L/usr/lib/x86_64-linux-gnu -lopencv_highgui
    LIBS += -L/usr/lib/x86_64-linux-gnu -lopencv_features2d
    LIBS += -L/usr/lib/x86_64-linux-gnu -lopencv_objdetect
    LIBS += -L/usr/lib/x86_64-linux-gnu -lopencv_contrib
    LIBS += -L/usr/lib/x86_64-linux-gnu -lopencv_calib3d
    LIBS += -L/usr/lib/x86_64-linux-gnu -lopencv_imgproc

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

PROJNAME = CalibrationToolkit
INSTTYPE = APP
include(RobotSDK_Main.pri)
