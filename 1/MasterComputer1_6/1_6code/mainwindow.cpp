#include "mainwindow.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMetaType>

#define COMWIDGETWIDTH 450  //串口调试窗口，大小为450 360
#define COMWIDGETHIGHT 360

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle(tr("纳秒脉冲电化学监控系统"));

    CreateInit();
    CreateLayout();
    this->setFixedSize(MainWidgetWidth, MainWidgetHight);   //窗口大小固定为600*393
}

MainWindow::~MainWindow()
{

}

void MainWindow::CreateInit()
{
    powerwidget = new PowerWidget;
    runwidget = new RunWidget;
    voltagewidget = new VoltageWidget;
    controlwidget = new ControlWidget;
    comportwidget = new ComPortWidget;
    comportwidget->setFixedSize(COMWIDGETWIDTH, COMWIDGETHIGHT);      //串口调试窗口，大小为450 360
    comportwidget->hide();  //隐藏

    powerwidget->setFixedWidth(MidWidth);
    runwidget->setFixedWidth(MidWidth);
    voltagewidget->setFixedWidth(MidWidth);
//    controlwidget->setFixedWidth(80);

    ComAction = new QAction(tr("串口调试"));
    connect(ComAction, &QAction::triggered,
            [this](){
        if(comportwidget->isHidden())   //如果隐藏界面
            comportwidget->show();
    });
    menuBar()->addAction(ComAction);

    connect(powerwidget, SIGNAL(SendPowerData()),
            this, SLOT(GetPowerData()));
    connect(runwidget, SIGNAL(SendRunData()),
            this, SLOT(GetRunData()));
    connect(comportwidget, SIGNAL(EmitRecvData()),
            this, SLOT(GetComRecvData()));
    connect(controlwidget,SIGNAL(SendConData()),
            this, SLOT(GetConData()));
    m_handleThread = nullptr;
/*
    connect(m_handleThread, SIGNAL(SendReadyData(HandleToComData)),
            comportwidget, SLOT(GetSendData(HandleToComData)));
    connect(m_handleThread, SIGNAL(ComToRun(ComToRunData)),
            runwidget,SLOT(GetRecvData(ComToRunData)));
*/
    // exitButton = new QPushButton(tr("退出"));
   // connect(exitButton, SIGNAL(clicked(bool)),
   //         this, SLOT(close()));
    //m_handleThread->start();
}

void MainWindow::CreateLayout()
{
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(controlwidget);
    //leftLayout->addWidget(exitButton);
    leftLayout->addStretch(1);
    QWidget *leftWidget = new QWidget;
    leftWidget->setLayout(leftLayout);
    leftWidget->setFixedWidth(LeftWidth);

    QSplitter *MidSplitter = new QSplitter(Qt::Vertical);
    MidSplitter->addWidget(powerwidget);
    MidSplitter->addWidget(runwidget);
    MidSplitter->addWidget(voltagewidget);

    QSplitter *mainSplitter = new QSplitter(Qt::Horizontal);
    mainSplitter->addWidget(leftWidget);
    mainSplitter->addWidget(MidSplitter);
   // mainSplitter->addWidget(comportwidget);

    setCentralWidget(mainSplitter);
}

void MainWindow::GetPowerData()
{
    m_handleThread = new DataHandleThread(DATA::POWER);

    connect(m_handleThread, SIGNAL(SendReadyData(HandleToComData)), //将线程的准备信号，
            comportwidget, SLOT(GetSendData(HandleToComData)));     //与串口的发送函数连接
    m_handleThread->start();
}

void MainWindow::GetRunData()
{
    m_handleThread = new DataHandleThread(DATA::RUN);
    connect(m_handleThread, SIGNAL(SendReadyData(HandleToComData)),
            comportwidget, SLOT(GetSendData(HandleToComData)));
    m_handleThread->start();
}

void MainWindow::GetConData()
{
    m_handleThread = new DataHandleThread(DATA::CON);
    connect(m_handleThread, SIGNAL(SendReadyData(HandleToComData)),
            comportwidget, SLOT(GetSendData(HandleToComData)));
    m_handleThread->start();
}

void MainWindow::GetComRecvData()
{
    m_handleThread = new DataHandleThread(DATA::COMTORUN);

    connect(m_handleThread, SIGNAL(ComToRun(ComToRunData)),
            runwidget,SLOT(GetRecvData(ComToRunData)));
    m_handleThread->start();
}

void MainWindow::closeEvent(QCloseEvent *)
{    
    comportwidget->close();     //主窗口关闭时，串口窗口也关闭
    if(m_handleThread != nullptr)
    {
        m_handleThread->terminate();     //关闭最后一个线程
        m_handleThread->wait();     //等待该线程资源释放，其实不写也没事，因为进程关闭了，线程肯定都回收
    }

}




