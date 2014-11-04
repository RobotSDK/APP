#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <RobotSDK_Global.h>
#include <qsplitter.h>

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

public:
    Edge edge;
signals:
    void openSignal();
    void closeSingal();
    void setStartTimeSignal(QTime startTime);
    void setSimulateRateSignal(double simulateRate);
    void startSignal();
    void stopSignal();
    void resetSignal();
private slots:
    void on_open_clicked();
    void on_set_clicked();
    void on_start_clicked();
    void on_reset_clicked();
};

#endif // MAINWINDOW_H
