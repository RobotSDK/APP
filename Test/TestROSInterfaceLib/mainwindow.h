#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<rosinterface.h>
#include<turtlesim/Pose.h>
#include<geometry_msgs/Twist.h>

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
    ROSPub<geometry_msgs::Twist> * rospub;
    ROSSub<turtlesim::Pose> * rossub;
signals:
    void startSubSignal();
    void stopSubSignal();
public slots:
    void sendMessageSlot();
    void triggerSubSlot();
    void receiveMessageSlot();
};

#endif // MAINWINDOW_H
