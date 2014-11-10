#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CalibrateROSCameraChessboard * calibration=new CalibrateROSCameraChessboard("/usb_cam/image_raw",cv::Size2f(0.035,0.035),cv::Size2i(8,6));
    ui->tabWidget->addTab(calibration,"Calibration");

    connect(ui->grab,SIGNAL(clicked()),calibration,SLOT(grabCalibDataSlot()));
    connect(ui->calibrate,SIGNAL(clicked()),calibration,SLOT(calibrateSensorSlot()));
    connect(ui->load,SIGNAL(clicked()),calibration,SLOT(loadCalibResultSlot()));
    connect(ui->save,SIGNAL(clicked()),calibration,SLOT(saveCalibResultSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
