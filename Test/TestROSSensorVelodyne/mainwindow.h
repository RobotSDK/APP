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

signals:
    void openSignal();
    void closeSignal();
private slots:
    void on_open_clicked();
    void on_actionControl_triggered(bool checked);

    void on_actionMonitor_triggered(bool checked);

    void on_actionVelodyne_triggered(bool checked);

    void on_actionCamera_triggered(bool checked);

private:
    Ui::MainWindow *ui;
    Edge edge;
};

#endif // MAINWINDOW_H
