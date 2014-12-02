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
    camera->setOutputNodesName(QStringList()<<"velodynecamera;image");

    VisualizationMono * image=new VisualizationMono(library,"Sensor_Camera","image",config);
    image->setInputNodesName(QStringList()<<"camera");
    image->connectExternalTrigger(0,DRAINSLOT);

    ProcessorMulti * velodynecamera=new ProcessorMulti(library,"Algorithm_Integration_VelodyneCamera","velodynecamera",config);
    velodynecamera->setInputNodesName(QStringList()<<"velodyne"<<"camera");
    velodynecamera->setOutputNodesName(QStringList()<<"velodynecamerandt3d");
    velodynecamera->connectExternalTrigger(0,PROCESSORSLOT);
    velodynecamera->connectExternalTrigger(1,PROCESSORSLOT);

    SensorInternalEvent * ndt3d=new SensorInternalEvent(library,"Algorithm_Localization_NDT3D","ndt3d",config);
    ndt3d->setOutputNodesName(QStringList()<<"velodynecamerandt3d");

    ProcessorMulti * velodynecamerandt3d=new ProcessorMulti(library,"Algorithm_Integration_VelodyneCameraNDT3D","velodynecamerandt3d",config);
    velodynecamerandt3d->setInputNodesName(QStringList()<<"velodynecamera"<<"ndt3d");
    velodynecamerandt3d->setOutputNodesName(QStringList()<<"viewer");
    velodynecamerandt3d->connectExternalTrigger(0,PROCESSORSLOT);
    velodynecamerandt3d->connectExternalTrigger(1,PROCESSORSLOT);

    VisualizationMono * viewer=new VisualizationMono(library,"Algorithm_Integration_VelodyneCameraNDT3D","viewer",config);
    viewer->setInputNodesName(QStringList()<<"velodynecamerandt3d");
    viewer->connectExternalTrigger(0,DRAINSLOT);

    edge.addNode(velodyne,1,1);
    edge.addNode(camera,1,1);
    edge.addNode(image,0,0);
    edge.addNode(velodynecamera,1,1);
    edge.addNode(ndt3d,1,1);
    edge.addNode(velodynecamerandt3d,1,1);
    edge.addNode(viewer,0,0);

    edge.connectAll();

    QList<QWidget *> widgets=viewer->getVisualizationWidgets();
    ui->tabWidget->addTab(widgets[0],"Viewer");

    widgets=image->getVisualizationWidgets();
    ui->tabWidget->addTab(widgets[0],"image");

    ui->tabWidget->addTab(&edge,"Monitor");

    edge.openAllNodesSlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
