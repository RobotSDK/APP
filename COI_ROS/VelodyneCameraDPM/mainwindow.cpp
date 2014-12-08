#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString library="COI_ROS";
    QString config="config.xml";

    SensorInternalEvent * velodyne=new SensorInternalEvent(library,"Sensor_Velodyne","velodyne",config);
    velodyne->setOutputNodesName(QStringList()<<"velodynecamera");

    SensorInternalEvent * camera=new SensorInternalEvent(library,"Sensor_Camera","camera",config);
    camera->setOutputNodesName(QStringList()<<"velodynecamera");

    ProcessorMulti * velodynecamera=new ProcessorMulti(library,"Algorithm_Integration_VelodyneCamera","velodynecamera",config);
    velodynecamera->setInputNodesName(QStringList()<<"velodyne"<<"camera");
    velodynecamera->setOutputNodesName(QStringList()<<"viewer");
    velodynecamera->connectExternalTrigger(0,PROCESSORSLOT);
    velodynecamera->connectExternalTrigger(1,PROCESSORSLOT);

    SensorInternalEvent * dpm=new SensorInternalEvent(library,"Algorithm_Detection_DPM","dpm",config);
    dpm->setOutputNodesName(QStringList()<<"viewer");

    VisualizationMulti * viewer=new VisualizationMulti(library,"Algorithm_Integration_VelodyneCameraDPM","viewer",config);
    viewer->setInputNodesName(QStringList()<<"velodynecamera"<<"dpm");
    viewer->connectExternalTrigger(0,DRAINSLOT);
    viewer->connectExternalTrigger(1,DRAINSLOT);

    edge.addNode(velodyne,1,1);
    edge.addNode(camera,1,1);
    edge.addNode(velodynecamera,1,1);
    edge.addNode(dpm,1,1);
    edge.addNode(viewer,0,0);
    edge.connectAll();

    QList<QWidget *> widgets=viewer->getVisualizationWidgets();
    ui->tabWidget->addTab(widgets[0],"DPM");

    ui->tabWidget->addTab(&edge,"Monitor");

    edge.openAllNodesSlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
