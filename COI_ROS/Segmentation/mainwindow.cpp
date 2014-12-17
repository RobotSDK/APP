#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString library="COI_ROS";
    QString config="config.xml";

    SensorInternalEvent * segment=new SensorInternalEvent(library,"Algorithm_Segmentation_Velodyne","segment",config);
    segment->setOutputNodesName(QStringList()<<"viewer");

    VisualizationMono * viewer=new VisualizationMono(library,"Algorithm_Segmentation_Velodyne","viewer",config);
    viewer->setInputNodesName(QStringList()<<"segment");
    viewer->connectExternalTrigger(0,DRAINSLOT);

    edge.addNode(segment,1,1);
    edge.addNode(viewer,0,0);

    edge.connectAll();

    QList<QWidget *> widgets=viewer->getVisualizationWidgets();
    ui->tabWidget->addTab(widgets[0],"Segment");

    ui->tabWidget->addTab(&edge,"Monitor");

    edge.openAllNodesSlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
