#include "mainwindow.h"
#include "ui_mainwindow.h"

#define MONITOR 1

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString library="COI";
    QString config="config.xml";

    Simulator * velodyne=new Simulator(library,"Sensor_Velodyne","velodyne",config,QTime(),1.0);
    velodyne->setOutputNodesName(QStringList()<<"velodyneviewer;groundobjects;rangeimage");

    VisualizationMono * velodyneviewer=new VisualizationMono(library,"Sensor_Velodyne","velodyneviewer",config);
    velodyneviewer->setInputNodesName(QStringList()<<"velodyne");
    velodyneviewer->connectExternalTrigger(0,DRAINSLOT);

    ProcessorMono * groundobjects=new ProcessorMono(library,"Algorithm_Segmentation_Velodyne_GroundObjects","groundobjects",config);
    groundobjects->setInputNodesName(QStringList()<<"velodyne");
    groundobjects->setOutputNodesName(QStringList()<<"groundobjectsviewer;groundobjectsdbmviewer");
    groundobjects->connectExternalTrigger(0,PROCESSORSLOT);

    VisualizationMono * groundobjectsviewer=new VisualizationMono(library,"Algorithm_Segmentation_Velodyne_GroundObjects","groundobjectsviewer",config);
    groundobjectsviewer->setInputNodesName(QStringList()<<"groundobjects");
    groundobjectsviewer->connectExternalTrigger(0,DRAINSLOT);


    Simulator * camera=new Simulator(library,"Sensor_Camera","camera",config,QTime(),1.0);
    camera->setOutputNodesName(QStringList()<<"cameraviewer;dbm");

    VisualizationMono * cameraviewer=new VisualizationMono(library,"Sensor_Camera","cameraviewer",config);
    cameraviewer->setInputNodesName(QStringList()<<"camera");
    cameraviewer->connectExternalTrigger(0,DRAINSLOT);

    ProcessorMono * dbm=new ProcessorMono(library,"Algorithm_Detection_Camera_DBM","dbm",config);
    dbm->setInputNodesName(QStringList()<<"camera");
    dbm->setOutputNodesName(QStringList()<<"dbmviewer;groundobjectsdbmviewer");
    dbm->connectExternalTrigger(0,PROCESSORSLOT);

    VisualizationMono * dbmviewer=new VisualizationMono(library,"Algorithm_Detection_Camera_DBM","dbmviewer",config);
    dbmviewer->setInputNodesName(QStringList()<<"dbm");
    dbmviewer->connectExternalTrigger(0,DRAINSLOT);

    VisualizationMulti * groundobjectsdbmviewer=new VisualizationMulti(library,"Visualization_Integration_GroundObjectsDBM","groundobjectsdbmviewer",config);
    groundobjectsdbmviewer->setInputNodesName(QStringList()<<"groundobjects"<<"dbm");
    groundobjectsdbmviewer->connectExternalTrigger(0,DRAINSLOT);


    ProcessorMono * rangeimage=new ProcessorMono(library,"Algorithm_Conversion_Velodyne_RangeImage","rangeimage",config);
    rangeimage->setInputNodesName(QStringList()<<"velodyne");
    rangeimage->setOutputNodesName(QStringList()<<"rangeimageviewer");
    rangeimage->connectExternalTrigger(0,PROCESSORSLOT);

    VisualizationMono * rangeimageviewer=new VisualizationMono(library,"Algorithm_Conversion_Velodyne_RangeImage","rangeimageviewer",config);
    rangeimageviewer->setInputNodesName(QStringList()<<"rangeimage");
    rangeimageviewer->connectExternalTrigger(0,DRAINSLOT);

    edge.addNode(velodyne,1,MONITOR);
    edge.addNode(velodyneviewer,0,0);
    edge.addNode(groundobjects,1,MONITOR);
    edge.addNode(groundobjectsviewer,0,0);
    edge.addNode(camera,1,MONITOR);
    edge.addNode(cameraviewer,0,0);
    edge.addNode(dbm,1,MONITOR);
    edge.addNode(dbmviewer,0,0);
    edge.addNode(groundobjectsdbmviewer,0,0);
 //   edge.addNode(rangeimage,1,MONITOR);
 //   edge.addNode(rangeimageviewer,0,0);

    edge.connectAll();

    connect(this,SIGNAL(openSignal()),&edge,SLOT(openAllNodesSlot()));
    connect(this,SIGNAL(closeSingal()),&edge,SLOT(closeAllNodesSlot()));

    connect(this,SIGNAL(startSignal()),velodyne,SLOT(startSimulatorSlot()));
    connect(this,SIGNAL(stopSignal()),velodyne,SLOT(stopSimulatorSlot()));
    connect(this,SIGNAL(setStartTimeSignal(QTime)),velodyne,SLOT(setStartTimeSlot(QTime)));
    connect(this,SIGNAL(setSimulateRateSignal(double)),velodyne,SLOT(setSimulateRateSlot(double)));
    connect(this,SIGNAL(resetSignal()),velodyne,SLOT(resetTimeTrackSlot()));

    connect(this,SIGNAL(startSignal()),camera,SLOT(startSimulatorSlot()));
    connect(this,SIGNAL(stopSignal()),camera,SLOT(stopSimulatorSlot()));
    connect(this,SIGNAL(setStartTimeSignal(QTime)),camera,SLOT(setStartTimeSlot(QTime)));
    connect(this,SIGNAL(setSimulateRateSignal(double)),camera,SLOT(setSimulateRateSlot(double)));
    connect(this,SIGNAL(resetSignal()),camera,SLOT(resetTimeTrackSlot()));

    connect(this,SIGNAL(resetSignal()),velodyneviewer,SLOT(resetVisualizationSlot()));
    connect(this,SIGNAL(resetSignal()),groundobjectsviewer,SLOT(resetVisualizationSlot()));
    connect(this,SIGNAL(resetSignal()),cameraviewer,SLOT(resetVisualizationSlot()));
    connect(this,SIGNAL(resetSignal()),dbmviewer,SLOT(resetVisualizationSlot()));
    connect(this,SIGNAL(resetSignal()),rangeimageviewer,SLOT(resetVisualizationSlot()));

    QList<QWidget *> widgets;


    QSplitter * splitter=new QSplitter(Qt::Vertical);
    ui->tabWidget->addTab(splitter,"Viewer");

    QTabWidget * tab=new QTabWidget;
    splitter->addWidget(tab);

    widgets=cameraviewer->getVisualizationWidgets();
    tab->addTab(widgets[0],"Camera");

    widgets=dbmviewer->getVisualizationWidgets();
    tab->addTab(widgets[0],"DBM");

    widgets=groundobjectsdbmviewer->getVisualizationWidgets();
    tab->addTab(widgets[0],"Ground_Object_DBM");

    QSplitter * hsplitter=new QSplitter(Qt::Horizontal);
    splitter->addWidget(hsplitter);

    widgets=velodyneviewer->getVisualizationWidgets();
    hsplitter->addWidget(widgets[0]);

    widgets=groundobjectsviewer->getVisualizationWidgets();
    hsplitter->addWidget(widgets[0]);
    hsplitter->addWidget(widgets[1]);

    widgets=rangeimageviewer->getVisualizationWidgets();
    tab->addTab(widgets[0],"Range Image");
    tab->addTab(widgets[1],"Range Points");

    ui->tabWidget->addTab(&edge,"Monitor");

    ui->set->setEnabled(0);
    ui->start->setEnabled(0);
    ui->reset->setEnabled(0);
}

MainWindow::~MainWindow()
{
    delete ui;
    edge.clear();
}

void MainWindow::on_open_clicked()
{
    if(ui->open->text()=="Open")
    {
        ui->open->setText("Close");
        ui->set->setEnabled(1);
        ui->start->setEnabled(1);
        ui->reset->setEnabled(1);
        emit openSignal();
    }
    else
    {
        ui->open->setText("Open");
        ui->set->setEnabled(0);
        ui->start->setEnabled(0);
        ui->reset->setEnabled(0);
        emit closeSingal();
    }
}

void MainWindow::on_set_clicked()
{
    emit setStartTimeSignal(QTime::fromString(ui->starttime->text(),"hh:mm:ss.zzz"));
    emit setSimulateRateSignal(ui->simulaterate->text().toDouble());
}

void MainWindow::on_start_clicked()
{
    if(ui->start->text()=="Start")
    {
        ui->start->setText("Stop");
        ui->set->setEnabled(0);
        ui->open->setEnabled(0);
        ui->reset->setEnabled(0);
        emit startSignal();
    }
    else
    {
        ui->start->setText("Start");
        ui->set->setEnabled(1);
        ui->open->setEnabled(1);
        ui->reset->setEnabled(1);
        emit stopSignal();
    }
}

void MainWindow::on_reset_clicked()
{
    emit resetSignal();
}
