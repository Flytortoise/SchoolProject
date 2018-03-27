#include "mainwindow.h"
#include <QSplitter>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle(tr("纳秒脉冲电化学监控系统"));

    CreateInit();
    CreateLayout();
    this->setFixedSize(MainWidgetWidth, MainWidgetHight);   //窗口大小固定为1050*393
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

    powerwidget->setFixedWidth(MidWidth);
    runwidget->setFixedWidth(MidWidth);
    voltagewidget->setFixedWidth(MidWidth);

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

    QSplitter *MidSplitter = new QSplitter(Qt::Vertical);
    MidSplitter->addWidget(powerwidget);
    MidSplitter->addWidget(runwidget);
    MidSplitter->addWidget(voltagewidget);

    QSplitter *mainSplitter = new QSplitter(Qt::Horizontal);
    mainSplitter->addWidget(leftWidget);
    mainSplitter->addWidget(MidSplitter);
    mainSplitter->addWidget(comportwidget);

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






