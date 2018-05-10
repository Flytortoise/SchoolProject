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

signals:
    void SendPowerData(HandleToComData);    //向串口界面发送数据
    void SendRunData(HandleToComData);      //向串口界面发送数据

public slots:
    void GetPowerData(PowerToHandleData powerdata); //从电源设定界面接受到的数据
    void GetRunData(RunToHandleData rundata);       //从运动设定界面接受到的数据

private:
    PowerWidget *powerwidget;   //电压设定
    RunWidget *runwidget;       //运动设定
    VoltageWidget *voltagewidget;   //极间电压
    ControlWidget *controlwidget;   //点动控制
    ComPortWidget *comportwidget;   //串口调试
    DataHandle m_handle;            //数据处理
   // QPushButton *exitButton;
    HandleToComData m_data;         //传给串口的数据

    void CreateInit();
    void CreateLayout();
};

#endif // MAINWINDOW_H