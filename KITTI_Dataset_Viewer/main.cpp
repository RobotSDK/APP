#include "kitti_dataset_viewer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	KITTI_Dataset_Viewer w;
	w.show();
	return a.exec();
}
