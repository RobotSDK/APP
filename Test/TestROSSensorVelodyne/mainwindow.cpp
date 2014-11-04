#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString library="COI";
    QString config="config.xml";

    SensorInternalEvent * rosvelodyne=new SensorInternalEvent(library,"ROS_Sensor_Velodyne","rosvelodyne",config);
    rosvelodyne->setOutputNodesName(QStringList()<<"velodyneviewer");

    VisualizationMono * velodyneviewer=new VisualizationMono(library,"Sensor_Velodyne","velodyneviewer",config);
    velodyneviewer->setInputNodesName(QStringList()<<"rosvelodyne");
    velodyneviewer->connectExternalTrigger(0,DRAINSLOT);

    SensorInternalEvent * roscamera=new SensorInternalEvent(library,"ROS_Sensor_Camera","roscamera",config);
    roscamera->setOutputNodesName(QStringList()<<"cameraviewer");

    VisualizationMono * cameraviewer=new VisualizationMono(library,"Sensor_Camera","cameraviewer",config);
    cameraviewer->setInputNodesName(QStringList()<<"roscamera");
    cameraviewer->connectExternalTrigger(0,DRAINSLOT);

    edge.addNode(rosvelodyne,1,1);
    edge.addNode(velodyneviewer,0,0);
    edge.addNode(roscamera,1,1);
    edge.addNode(cameraviewer,0,0);

    edge.connectAll();

    connect(this,SIGNAL(openSignal()),&edge,SLOT(openAllNodesSlot()));
    connect(this,SIGNAL(closeSignal()),&edge,SLOT(closeAllNodesSlot()));

    QList<QWidget *> widgets;

    widgets=velodyneviewer->getVisualizationWidgets();
    ui->velodyne->setWidget(widgets[0]);

    widgets=cameraviewer->getVisualizationWidgets();
    ui->camera->setWidget(widgets[0]);

    ui->monitor->setWidget(&edge);
}

MainWindow::~MainWindow()
{
    edge.clear();
    delete ui;
}

void MainWindow::on_open_clicked()
{
    if(ui->open->text()=="Open")
    {
        ui->open->setText("Close");
        emit openSignal();
    }
    else
    {
        ui->open->setText("Open");
        emit closeSignal();
    }
}

void MainWindow::on_actionControl_triggered(bool checked)
{
    if(checked)
    {
        ui->control->show();
    }
    else
    {
        ui->control->hide();
    }
}

void MainWindow::on_actionMonitor_triggered(bool checked)
{
    if(checked)
    {
        ui->monitor->show();
    }
    else
    {
        ui->monitor->hide();
    }
}

void MainWindow::on_actionVelodyne_triggered(bool checked)
{
    if(checked)
    {
        ui->velodyne->show();
    }
    else
    {
        ui->velodyne->hide();
    }
}

void MainWindow::on_actionCamera_triggered(bool checked)
{
    if(checked)
    {
        ui->camera->show();
    }
    else
    {
        ui->camera->hide();
    }
}
