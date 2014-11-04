#ifndef KITTI_DATASET_VIEWER_H
#define KITTI_DATASET_VIEWER_H

#include <QtWidgets/QMainWindow>
#include "ui_kitti_dataset_viewer.h"

#include<RobotSDK_Global.h>

#include<qsplitter.h>

class KITTI_Dataset_Viewer : public QMainWindow
{
	Q_OBJECT

public:
	KITTI_Dataset_Viewer(QWidget *parent = 0);
	~KITTI_Dataset_Viewer();

private:
	Ui::KITTI_Dataset_ViewerClass ui;

protected:
	Edge edge;
public slots:
	void openSlot();
	void setSlot();
	void startSlot();
signals:
	void openSignal();
	void closeSignal();
	void startSignal();
	void stopSignal();
	void setStartTimeSignal(QTime startTime);
	void setSimulateRateSignal(double simulateRate);
};

#endif // KITTI_DATASET_VIEWER_H
