#include "mainwindow.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QMenuBar>

#define COMWIDGETWIDTH 450  //串口调试窗口，大小为450 360
#define COMWIDGETHIGHT 360

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle(tr("纳秒脉冲电化学监控系统"));

    CreateInit();
    CreateLayout();
    this->setFixedSize(MainWidgetWidth, MainWidgetHight);   //窗口大小固定为650*310
}

MainWindow::~MainWindow()
{

}

void MainWindow::CreateInit()
{
    powerwidget = new PowerWidget;
    runwidget = new RunWidget;
    //voltagewidget = new VoltageWidget;
    controlwidget = new ControlWidget;
    comportwidget = new ComPortWidget;
    comportwidget->setFixedSize(COMWIDGETWIDTH, COMWIDGETHIGHT);      //串口调试窗口，大小为450 360
    comportwidget->hide();  //隐藏

    //powerwidget->setFixedWidth(MidWidth);
    //runwidget->setFixedWidth(MidWidth);
    powerwidget->setContentsMargins(0, 10, 20, 0);
    runwidget->setContentsMargins(0, 0, 20, 10);
    //voltagewidget->setFixedWidth(MidWidth);
//    controlwidget->setFixedWidth(80);

    ComAction = new QAction(tr("串口调试"));
    connect(ComAction, &QAction::triggered,
            [this](){
        if(comportwidget->isHidden())   //如果隐藏界面
            comportwidget->show();
    });
    menuBar()->addAction(ComAction);

    connect(powerwidget, SIGNAL(SendPowerData(PowerToHandleData)),
            this, SLOT(GetPowerData(PowerToHandleData)));
    connect(runwidget, SIGNAL(SendRunData(RunToHandleData)),
            this, SLOT(GetRunData(RunToHandleData)));
    connect(comportwidget, SIGNAL(EmitRecvData(QByteArray)),
            this, SLOT(GetComRecvData(QByteArray)));
    connect(controlwidget,SIGNAL(ConToCom(QByteArray)),
            this, SLOT(GetConData(QByteArray)));

    connect(this, SIGNAL(SendReadyData(HandleToComData)),
            comportwidget, SLOT(GetSendData(HandleToComData)));
    connect(this, SIGNAL(ComToRun(ComToRunData)),
            runwidget,SLOT(GetRecvData(ComToRunData)));

    connect(comportwidget, SIGNAL(HideAllButton()),
            this, SLOT(HideAllButton()));
    connect(comportwidget, SIGNAL(ShowAllButton()),
            this, SLOT(ShowAllButton()));

    // exitButton = new QPushButton(tr("退出"));
   // connect(exitButton, SIGNAL(clicked(bool)),
   //         this, SLOT(close()));

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
    //MidSplitter->addWidget(voltagewidget);

    QSplitter *mainSplitter = new QSplitter(Qt::Horizontal);
    mainSplitter->addWidget(leftWidget);
    mainSplitter->addWidget(MidSplitter);
   // mainSplitter->addWidget(comportwidget);

    setCentralWidget(mainSplitter);
}

void MainWindow::GetPowerData(PowerToHandleData powerdata)
{
    m_data = m_handle.PowerDataHandle(powerdata);

    emit SendReadyData(m_data);

}

void MainWindow::GetRunData(RunToHandleData rundata)
{
    m_data = m_handle.RunDataHandle(rundata);

    emit SendReadyData(m_data);

}

void MainWindow::GetComRecvData(QByteArray comdata)
{
    ComToRunData rundata = m_handle.AnalysisComData(comdata);
    emit ComToRun(rundata);
}

void MainWindow::GetConData(QByteArray condata)
{
    m_data = m_handle.ConDataHandle(condata);
    emit SendReadyData(m_data);

}

void MainWindow::closeEvent(QCloseEvent *)
{
    comportwidget->close();     //主窗口关闭时，串口窗口也关闭
}

void MainWindow::HideAllButton()
{
    powerwidget->HideButton();
    runwidget->HideButton();
    controlwidget->HideButton();
}

void MainWindow::ShowAllButton()
{
    powerwidget->ShowButton();
    runwidget->ShowButton();
    controlwidget->ShowButton();
}


