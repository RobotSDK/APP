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

void MainWindow::on_setinputnum_clicked()
{
    ui->inputs->clear();
    int i,inputnum=ui->inputnum->value();
    ui->inputs->setColumnCount(1);
    ui->inputs->setRowCount(inputnum);
    for(i=0;i<inputnum;i++)
    {
        ui->inputs->setItem(i,1,new QTableWidgetItem);
    }
}

void MainWindow::on_open_clicked()
{
    QString library="COI_ROS";
    QString config="config.xml";

    QString nodeclass=ui->nodeclass->text();

    integration=new ProcessorMulti(library,nodeclass,"integration",config);
    integration->setOutputNodesName(QStringList()<<"viewer");

    viewer=new VisualizationMono(library,nodeclass,"viewer",config);
    viewer->setInputNodesName(QStringList()<<"integration");
    viewer->connectExternalTrigger(0,DRAINSLOT);

    QList<QWidget *> widgets=viewer->getVisualizationWidgets();
    ui->tabWidget->insertTab(0,widgets[0],nodeclass);
    ui->tabWidget->setCurrentIndex(0);

    edge.addNode(integration,1,1);
    edge.addNode(viewer,0,0);

    int i,inputnum=ui->inputs->rowCount();
    QVector<QString> inputnodes(inputnum);
    sensors.resize(inputnum);
    viewers.resize(inputnum);
    QStringList sensorlist;
    for(i=0;i<inputnum;i++)
    {
        inputnodes[i]=ui->inputs->item(i,0)->text();

        sensors[i]=new SensorInternalEvent(library,inputnodes[i],QString("sensor_%1").arg(i),config);
        sensors[i]->setOutputNodesName(QStringList()<<QString("sensor_viewer_%1;integration").arg(i));

        sensorlist=sensorlist<<QString("sensor_%1").arg(i);
        integration->connectExternalTrigger(i,PROCESSORSLOT);

        viewers[i]=new VisualizationMono(library,inputnodes[i],QString("sensor_viewer_%1").arg(i),config);
        viewers[i]->setInputNodesName(QStringList()<<QString("sensor_%1").arg(i));
        viewers[i]->connectExternalTrigger(0,DRAINSLOT);

        edge.addNode(sensors[i],1,1);
        edge.addNode(viewers[i],0,0);

        widgets=viewers[i]->getVisualizationWidgets();
        ui->inputtab->addTab(widgets[0],inputnodes[i]);
    }
    integration->setInputNodesName(sensorlist);

    edge.connectAll();
    edge.openAllNodesSlot();

    ui->open->setEnabled(0);
    ui->close->setEnabled(1);
}

void MainWindow::on_close_clicked()
{
    ui->tabWidget->removeTab(0);
    ui->inputtab->clear();

    edge.clear();

    ui->open->setEnabled(1);
    ui->close->setEnabled(0);
}
