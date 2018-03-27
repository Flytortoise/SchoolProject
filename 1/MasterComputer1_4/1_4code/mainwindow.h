#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "powerwidget.h"
#include "runwidget.h"
#include "voltagewidget.h"
#include "controlwidget.h"
#include "comportwidget.h"
#include "transmitdata.h"
#include "datahandle.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    enum{
        MainWidgetWidth = 1100,
        MainWidgetHight = 393,
        MidWidth = 480
    };

signals:
    void SendReadyData(HandleToComData);    //向串口界面发送封装好的数据
    void ComToRun(ComToRunData);     //串口传回的数据，发给运动设定

public slots:
    void GetPowerData(PowerToHandleData powerdata); //从电源设定界面接受到的数据
    void GetRunData(RunToHandleData rundata);       //从运动设定界面接受到的数据
    void GetComRecvData(QByteArray comdata);        //串口接收到的数据
    void GetConData(QByteArray condata);      //获取点位控制传来的数据

private:
    PowerWidget *powerwidget;   //电压设定
    RunWidget *runwidget;       //运动设定
    VoltageWidget *voltagewidget;   //极间电压
    ControlWidget *controlwidget;   //点动控制
    ComPortWidget *comportwidget;   //串口调试
    DataHandle m_handle;            //数据处理对象
   // QPushButton *exitButton;
    HandleToComData m_data;         //传给串口的数据

    void CreateInit();
    void CreateLayout();
};

#endif // MAINWINDOW_H
