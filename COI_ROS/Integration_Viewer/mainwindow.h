#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <RobotSDK_Global.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected:
    Edge edge;
    QVector<SensorInternalEvent *> sensors;
    QVector<VisualizationMono *> viewers;
    ProcessorMulti * integration;
    VisualizationMono * viewer;
private slots:
    void on_setinputnum_clicked();
    void on_open_clicked();
    void on_close_clicked();
};

#endif // MAINWINDOW_H
