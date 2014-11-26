#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<RobotSDK_Global.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_open_clicked();

    void on_close_clicked();

private:
    Ui::MainWindow *ui;

protected:
    Edge edge;
    SensorInternalEvent * sensor;
    VisualizationMono * sensor_viewer;
};

#endif // MAINWINDOW_H
