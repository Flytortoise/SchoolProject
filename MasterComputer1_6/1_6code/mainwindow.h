#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QAction>
#include <QVector>
#include "powerwidget.h"
#include "runwidget.h"
#include "voltagewidget.h"
#include "controlwidget.h"
#include "comportwidget.h"
#include "transmitdata.h"
#include "datahandlethread.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    enum{
        MainWidgetWidth = 650,      //界面宽度
        MainWidgetHight = 393,      //界面高度
        MidWidth = 480,             //中间部分的宽度
        LeftWidth = 140             //左边的宽度
    };
    void closeEvent(QCloseEvent *); //重载该事件，让串口窗口关闭，让所有线程结束


signals:
    void SendReadyData(HandleToComData);    //向串口界面发送封装好的数据
    void ComToRun(ComToRunData);     //串口传回的数据，发给运动设定

public slots:
    void GetPowerData(); //从电源设定界面接受到的数据
    void GetRunData();       //从运动设定界面接受到的数据
    void GetComRecvData();        //串口接收到的数据
    void GetConData();      //获取点位控制传来的数据

private:
    PowerWidget *powerwidget;   //电压设定
    RunWidget *runwidget;       //运动设定
    VoltageWidget *voltagewidget;   //极间电压
    ControlWidget *controlwidget;   //点动控制
    ComPortWidget *comportwidget;   //串口调试
  //  DataHandle m_handle;            //数据处理对象
   // QPushButton *exitButton;
  //  HandleToComData m_data;         //传给串口的数据
    DataHandleThread *m_handleThread;

    QAction *ComAction;

    void CreateInit();
    void CreateLayout();
};

#endif // MAINWINDOW_H
