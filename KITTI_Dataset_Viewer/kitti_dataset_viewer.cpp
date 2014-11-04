#include "kitti_dataset_viewer.h"

#pragma comment(lib, "Kernel.lib")

#define MONITOR 0

KITTI_Dataset_Viewer::KITTI_Dataset_Viewer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QString config="config.xml";
	
	Simulator * camerasim=new Simulator("KITTI","Sensor_Camera","camerasim",config,QTime(),1.0);
	camerasim->setOutputNodesName(QStringList()<<"cameraviewer;integrationvelodynecamera;detection1cameradpm;detection2cameradpm");

	VisualizationMono * cameraviewer=new VisualizationMono("KITTI","Sensor_Camera","cameraviewer",config);
	cameraviewer->setInputNodesName(QStringList()<<"camerasim");
	cameraviewer->connectExternalTrigger(0,DRAINSLOT);

	Simulator * velodynesim=new Simulator("KITTI","Sensor_Velodyne","velodynesim",config,QTime(),1.0);
	velodynesim->setOutputNodesName(QStringList()<<"velodyneviewer;integrationvelodynecamera");

	VisualizationMono * velodyneviewer=new VisualizationMono("KITTI","Sensor_Velodyne","velodyneviewer",config);
	velodyneviewer->setInputNodesName(QStringList()<<"velodynesim");
	velodyneviewer->connectExternalTrigger(0,DRAINSLOT);
	
	Simulator * gpsimusim=new Simulator("KITTI","Sensor_GPSIMU","gpsimusim",config,QTime(),1.0);
	gpsimusim->setOutputNodesName(QStringList()<<"gpsimuviewer;integrationvelodynecameragpsimu");	

	VisualizationMono * gpsimuviewer=new VisualizationMono("KITTI","Sensor_GPSIMU","gpsimuviewer",config);
	gpsimuviewer->setInputNodesName(QStringList()<<"gpsimusim");
	gpsimuviewer->connectExternalTrigger(0,DRAINSLOT);

	Simulator * slamsim=new Simulator("KITTI","Algorithm_SLAM_Velodyne_ScanMatching","slamsim",config,QTime(),1.0);
	slamsim->setOutputNodesName(QStringList()<<"slamviewer;integrationvelodynecameraslam");	

	VisualizationMono * slamviewer=new VisualizationMono("KITTI","Algorithm_SLAM_Velodyne_ScanMatching","slamviewer",config);
	slamviewer->setInputNodesName(QStringList()<<"slamsim");
	slamviewer->connectExternalTrigger(0,DRAINSLOT);

	ProcessorMulti * integrationvelodynecamera=new ProcessorMulti("KITTI","Algorithm_Integration_VelodyneCamera","integrationvelodynecamera",config);
	integrationvelodynecamera->setInputNodesName(QStringList()<<"velodynesim"<<"camerasim");
	integrationvelodynecamera->setOutputNodesName(QStringList()<<"integrationvelodynecameraviewer;integrationvelodynecamerastorage;integrationvelodynecameragpsimu;integrationvelodynecameraslam");
	integrationvelodynecamera->connectExternalTrigger(0,PROCESSORSLOT);
	integrationvelodynecamera->connectExternalTrigger(1,PROCESSORSLOT);

	VisualizationMono * integrationvelodynecameraviewer=new VisualizationMono("KITTI","Algorithm_Integration_VelodyneCamera","integrationvelodynecameraviewer",config);
	integrationvelodynecameraviewer->setInputNodesName(QStringList()<<"integrationvelodynecamera");
	integrationvelodynecameraviewer->connectExternalTrigger(0,DRAINSLOT);
	integrationvelodynecameraviewer->connectExternalTrigger(1,DRAINSLOT);
	integrationvelodynecameraviewer->connectExternalTrigger(2,DRAINSLOT);

	StorageMono * integrationvelodynecamerastorage=new StorageMono("KITTI","Algorithm_Integration_VelodyneCamera","integrationvelodynecamerastorage",config);
	integrationvelodynecamerastorage->setInputNodesName(QStringList()<<"integrationvelodynecamera");
	integrationvelodynecamerastorage->connectExternalTrigger(0,DRAINSLOT);

	ProcessorMulti * integrationvelodynecameragpsimu=new ProcessorMulti("KITTI","Algorithm_Integration_VelodyneCameraGPSIMU","integrationvelodynecameragpsimu",config);
	integrationvelodynecameragpsimu->setInputNodesName(QStringList()<<"integrationvelodynecamera"<<"gpsimusim");
	integrationvelodynecameragpsimu->setOutputNodesName(QStringList()<<"integrationvelodynecameragpsimuviewer;integrationvelodynecameragpsimustorage");
	integrationvelodynecameragpsimu->connectExternalTrigger(0,PROCESSORSLOT);

	VisualizationMono * integrationvelodynecameragpsimuviewer=new VisualizationMono("KITTI","Algorithm_Integration_VelodyneCameraGPSIMU","integrationvelodynecameragpsimuviewer",config);
	integrationvelodynecameragpsimuviewer->setInputNodesName(QStringList()<<"integrationvelodynecameragpsimu");
	integrationvelodynecameragpsimuviewer->connectExternalTrigger(0,DRAINSLOT);

	StorageMono * integrationvelodynecameragpsimustorage=new StorageMono("KITTI","Algorithm_Integration_VelodyneCameraGPSIMU","integrationvelodynecameragpsimustorage",config);
	integrationvelodynecameragpsimustorage->setInputNodesName(QStringList()<<"integrationvelodynecameragpsimu");
	integrationvelodynecameragpsimustorage->connectExternalTrigger(0,DRAINSLOT);

	ProcessorMulti * integrationvelodynecameraslam=new ProcessorMulti("KITTI","Algorithm_Integration_VelodyneCameraSLAM","integrationvelodynecameraslam",config);
	integrationvelodynecameraslam->setInputNodesName(QStringList()<<"integrationvelodynecamera"<<"slamsim");
	integrationvelodynecameraslam->setOutputNodesName(QStringList()<<"integrationvelodynecameraslamviewer;integrationvelodynecameraslamstorage");
	integrationvelodynecameraslam->connectExternalTrigger(0,PROCESSORSLOT);

	VisualizationMono * integrationvelodynecameraslamviewer=new VisualizationMono("KITTI","Algorithm_Integration_VelodyneCameraSLAM","integrationvelodynecameraslamviewer",config);
	integrationvelodynecameraslamviewer->setInputNodesName(QStringList()<<"integrationvelodynecameraslam");
	integrationvelodynecameraslamviewer->connectExternalTrigger(0,DRAINSLOT);

	StorageMono * integrationvelodynecameraslamstorage=new StorageMono("KITTI","Algorithm_Integration_VelodyneCameraSLAM","integrationvelodynecameraslamstorage",config);
	integrationvelodynecameraslamstorage->setInputNodesName(QStringList()<<"integrationvelodynecameraslam");
	integrationvelodynecameraslamstorage->connectExternalTrigger(0,DRAINSLOT);

	ProcessorMono * detection1cameradpm=new ProcessorMono("KITTI","Algorithm_Detection_Camera_DPM","detection1cameradpm",config);
	detection1cameradpm->setInputNodesName(QStringList()<<"camerasim");
	detection1cameradpm->setOutputNodesName(QStringList()<<"detection1cameradpmviewer");
	detection1cameradpm->connectExternalTrigger(0,PROCESSORSLOT);

	VisualizationMono * detection1cameradpmviewer=new VisualizationMono("KITTI","Algorithm_Detection_Camera_DPM","detection1cameradpmviewer",config);
	detection1cameradpmviewer->setInputNodesName(QStringList()<<"detection1cameradpm");
	detection1cameradpmviewer->connectExternalTrigger(0,DRAINSLOT);

	ProcessorMono * detection2cameradpm=new ProcessorMono("KITTI","Algorithm_Detection_Camera_DPM","detection2cameradpm",config);
	detection2cameradpm->setInputNodesName(QStringList()<<"camerasim");
	detection2cameradpm->setOutputNodesName(QStringList()<<"detection2cameradpmviewer");
	detection2cameradpm->connectExternalTrigger(0,PROCESSORSLOT);

	VisualizationMono * detection2cameradpmviewer=new VisualizationMono("KITTI","Algorithm_Detection_Camera_DPM","detection2cameradpmviewer",config);
	detection2cameradpmviewer->setInputNodesName(QStringList()<<"detection2cameradpm");
	detection2cameradpmviewer->connectExternalTrigger(0,DRAINSLOT);

	edge.addNode(camerasim,1,MONITOR|1);
	edge.addNode(cameraviewer,0,0);
	edge.addNode(velodynesim,1,MONITOR|1);
	edge.addNode(velodyneviewer,0,0);
	edge.addNode(gpsimusim,1,MONITOR);
	edge.addNode(gpsimuviewer,0,0);
	edge.addNode(slamsim,1,MONITOR);
	edge.addNode(slamviewer,0,0);
	edge.addNode(integrationvelodynecamera,1,MONITOR);
	edge.addNode(integrationvelodynecameraviewer,0,0);
	edge.addNode(integrationvelodynecamerastorage,1,MONITOR);
	edge.addNode(integrationvelodynecameragpsimu,1,MONITOR);
	edge.addNode(integrationvelodynecameragpsimuviewer,0,0);
	edge.addNode(integrationvelodynecameragpsimustorage,1,MONITOR);
	edge.addNode(integrationvelodynecameraslam,1,MONITOR);
	edge.addNode(integrationvelodynecameraslamviewer,0,0);
	edge.addNode(integrationvelodynecameraslamstorage,1,MONITOR);
	edge.addNode(detection1cameradpm,1,MONITOR|1);
	edge.addNode(detection1cameradpmviewer,0,0);
	edge.addNode(detection2cameradpm,1,MONITOR|1);
	edge.addNode(detection2cameradpmviewer,0,0);
	edge.connectAll();

	connect(ui.open,SIGNAL(clicked()),this,SLOT(openSlot()));
	connect(this,SIGNAL(openSignal()),&edge,SLOT(openAllNodesSlot()));
	connect(this,SIGNAL(closeSignal()),&edge,SLOT(closeAllNodesSlot()));

	connect(ui.set,SIGNAL(clicked()),this,SLOT(setSlot()));
	connect(ui.start,SIGNAL(clicked()),this,SLOT(startSlot()));
	
	connect(this,SIGNAL(setStartTimeSignal(QTime)),velodynesim,SLOT(setStartTimeSlot(QTime)));
	connect(this,SIGNAL(setSimulateRateSignal(double)),velodynesim,SLOT(setSimulateRateSlot(double)),Qt::BlockingQueuedConnection);
	connect(this,SIGNAL(startSignal()),velodynesim,SLOT(startSimulatorSlot()));
	connect(this,SIGNAL(stopSignal()),velodynesim,SLOT(stopSimulatorSlot()));
	connect(ui.reset,SIGNAL(clicked()),velodynesim,SLOT(resetTimeTrackSlot()),Qt::BlockingQueuedConnection);	

	connect(this,SIGNAL(setStartTimeSignal(QTime)),camerasim,SLOT(setStartTimeSlot(QTime)));
	connect(this,SIGNAL(setSimulateRateSignal(double)),camerasim,SLOT(setSimulateRateSlot(double)),Qt::BlockingQueuedConnection);
	connect(this,SIGNAL(startSignal()),camerasim,SLOT(startSimulatorSlot()));
	connect(this,SIGNAL(stopSignal()),camerasim,SLOT(stopSimulatorSlot()));
	connect(ui.reset,SIGNAL(clicked()),camerasim,SLOT(resetTimeTrackSlot()),Qt::BlockingQueuedConnection);	

	connect(this,SIGNAL(setStartTimeSignal(QTime)),gpsimusim,SLOT(setStartTimeSlot(QTime)));
	connect(this,SIGNAL(setSimulateRateSignal(double)),gpsimusim,SLOT(setSimulateRateSlot(double)),Qt::BlockingQueuedConnection);
	connect(this,SIGNAL(startSignal()),gpsimusim,SLOT(startSimulatorSlot()));
	connect(this,SIGNAL(stopSignal()),gpsimusim,SLOT(stopSimulatorSlot()));
	connect(ui.reset,SIGNAL(clicked()),gpsimusim,SLOT(resetTimeTrackSlot()),Qt::BlockingQueuedConnection);	

	connect(this,SIGNAL(setStartTimeSignal(QTime)),slamsim,SLOT(setStartTimeSlot(QTime)));
	connect(this,SIGNAL(setSimulateRateSignal(double)),slamsim,SLOT(setSimulateRateSlot(double)),Qt::BlockingQueuedConnection);
	connect(this,SIGNAL(startSignal()),slamsim,SLOT(startSimulatorSlot()));
	connect(this,SIGNAL(stopSignal()),slamsim,SLOT(stopSimulatorSlot()));
	connect(ui.reset,SIGNAL(clicked()),slamsim,SLOT(resetTimeTrackSlot()),Qt::BlockingQueuedConnection);	

	connect(ui.reset,SIGNAL(clicked()),velodyneviewer,SLOT(resetVisualizationSlot()));
	connect(ui.reset,SIGNAL(clicked()),cameraviewer,SLOT(resetVisualizationSlot()));
	connect(ui.reset,SIGNAL(clicked()),gpsimuviewer,SLOT(resetVisualizationSlot()));
	connect(ui.reset,SIGNAL(clicked()),slamviewer,SLOT(resetVisualizationSlot()));
	connect(ui.reset,SIGNAL(clicked()),integrationvelodynecameraviewer,SLOT(resetVisualizationSlot()));
	connect(ui.reset,SIGNAL(clicked()),integrationvelodynecameragpsimuviewer,SLOT(resetVisualizationSlot()));
	connect(ui.reset,SIGNAL(clicked()),integrationvelodynecameraslamviewer,SLOT(resetVisualizationSlot()));
	connect(ui.reset,SIGNAL(clicked()),detection1cameradpmviewer,SLOT(resetVisualizationSlot()));
	connect(ui.reset,SIGNAL(clicked()),detection2cameradpmviewer,SLOT(resetVisualizationSlot()));

	QList<QWidget *> widgets;

	widgets=cameraviewer->getVisualizationWidgets();
	ui.camera->setWidget(widgets.front());

	widgets=velodyneviewer->getVisualizationWidgets();
	ui.velodyne->setWidget(widgets.front());

	widgets=gpsimuviewer->getVisualizationWidgets();
	ui.gpsimu->setWidget(widgets.front());

	widgets=slamviewer->getVisualizationWidgets();
	ui.slam->setWidget(widgets.front());

	widgets=integrationvelodynecameraviewer->getVisualizationWidgets();
	ui.camera_velodyne->setWidget(widgets[0]);
	ui.velodyne_camera->setWidget(widgets[1]);

	widgets=integrationvelodynecameragpsimuviewer->getVisualizationWidgets();
	ui.velodynecameragpsimu->setWidget(widgets.front());

	widgets=integrationvelodynecameraslamviewer->getVisualizationWidgets();
	ui.velodynecameraslam->setWidget(widgets.front());

	widgets=detection1cameradpmviewer->getVisualizationWidgets();
	ui.object1->setWidget(widgets.front());

	widgets=detection2cameradpmviewer->getVisualizationWidgets();
	ui.object2->setWidget(widgets.front());

	ui.tabWidget->addTab(&edge,"Monitor");

	ui.open->setEnabled(1);
	ui.set->setEnabled(0);
	ui.start->setEnabled(0);
	ui.reset->setEnabled(0);
}

KITTI_Dataset_Viewer::~KITTI_Dataset_Viewer()
{
	edge.clear();
}

void KITTI_Dataset_Viewer::openSlot()
{
	if(ui.open->text()=="Open")
	{
		emit openSignal();
		ui.set->setEnabled(1);
		ui.start->setEnabled(1);
		ui.reset->setEnabled(1);
		ui.open->setText("Close");
	}
	else
	{
		emit closeSignal();
		ui.set->setEnabled(0);
		ui.start->setEnabled(0);
		ui.reset->setEnabled(0);
		ui.open->setText("Open");
	}	
}

void KITTI_Dataset_Viewer::setSlot()
{
	QTime starttime;
	int tmpindex=ui.starttime->text().indexOf(" ");
	QStringList tmpqls=ui.starttime->text().mid(tmpindex+1).split(":");
	if(tmpqls.size()<3)
	{
		starttime=QTime();
	}
	else
	{
		int h=tmpqls.at(0).toInt();
		int m=tmpqls.at(1).toInt();
		int tmpi=int(tmpqls.at(2).toDouble()*1000+0.5);
		int s=tmpi/1000;
		int ms=tmpi%1000;
		starttime=QTime(h,m,s,ms);
	}
	double simrate=ui.simrate->text().toDouble();
	emit setStartTimeSignal(starttime);
	emit setSimulateRateSignal(simrate);
}

void KITTI_Dataset_Viewer::startSlot()
{
	if(ui.start->text()=="Start")
	{
		emit startSignal();
		ui.open->setEnabled(0);
		ui.set->setEnabled(0);
		ui.reset->setEnabled(0);
		ui.start->setText("Stop");
	}
	else
	{
		emit stopSignal();
		ui.open->setEnabled(1);
		ui.set->setEnabled(1);
		ui.reset->setEnabled(1);
		ui.start->setText("Start");
	}	
}