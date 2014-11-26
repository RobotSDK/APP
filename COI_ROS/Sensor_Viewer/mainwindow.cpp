#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->addTab(&edge,"Monitor");

    ui->close->setEnabled(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_clicked()
{
    QString library="COI_ROS";
    QString nodeclass=ui->nodeclass->text();
    QString config="config.xml";

    sensor=new SensorInternalEvent(library,nodeclass,"sensor",config);
    sensor->setOutputNodesName(QStringList()<<"sensor_viewer");

    sensor_viewer=new VisualizationMono(library,nodeclass,"sensor_viewer",config);
    sensor_viewer->connectExternalTrigger(0,DRAINSLOT);
    sensor_viewer->setInputNodesName(QStringList()<<"sensor");

    edge.addNode(sensor,1,1);
    edge.addNode(sensor_viewer,0,0);
    edge.connectAll();
    edge.openAllNodesSlot();

    QList<QWidget *> widgets=sensor_viewer->getVisualizationWidgets();
    ui->tabWidget->insertTab(0,widgets[0],nodeclass);
    ui->tabWidget->setCurrentIndex(0);

    ui->open->setEnabled(0);
    ui->close->setEnabled(1);
}


void MainWindow::on_close_clicked()
{
    ui->tabWidget->removeTab(0);
    edge.clear();

    ui->open->setEnabled(1);
    ui->close->setEnabled(0);
}
