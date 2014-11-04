#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    rospub=new ROSPub<geometry_msgs::Twist>("turtle1/cmd_vel",1000,"Control1");
    connect(ui->pub,SIGNAL(clicked()),this,SLOT(sendMessageSlot()));

    rossub=new ROSSub<turtlesim::Pose>("turtle1/pose",1000,10,"Control1");
    connect(ui->sub,SIGNAL(clicked()),this,SLOT(triggerSubSlot()));
    connect(this,SIGNAL(startSubSignal()),rossub,SLOT(startReceiveSlot()));
    connect(this,SIGNAL(stopSubSignal()),rossub,SLOT(stopReceiveSlot()));
    connect(rossub,SIGNAL(receiveMessageSignal()),this,SLOT(receiveMessageSlot()));
}

MainWindow::~MainWindow()
{
    delete rospub;
    delete rossub;
    delete ui;
}

void MainWindow::sendMessageSlot()
{
    geometry_msgs::Twist msg;
    msg.linear.x=ui->linear->text().toDouble();
    msg.angular.z=ui->angular->text().toDouble();
    rospub->sendMessage(msg);
}

void MainWindow::triggerSubSlot()
{
    if(ui->sub->text()=="Start")
    {
        emit startSubSignal();
        ui->sub->setText("Stop");
    }
    else
    {
        emit stopSubSignal();
        ui->sub->setText("Start");
    }
}

void MainWindow::receiveMessageSlot()
{
    ROSSub<turtlesim::Pose>::ROSSubMsgPtr msgptr=rossub->getMessagePtr();
    if(msgptr!=NULL)
    {
        QString msg=QString("%1, %2, %3\n").arg(msgptr->x).arg(msgptr->y).arg(msgptr->theta);
        ui->pose->insertPlainText(msg);
        ui->pose->moveCursor(QTextCursor::End);
    }
}
