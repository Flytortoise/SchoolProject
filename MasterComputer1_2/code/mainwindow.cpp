#include "mainwindow.h"
#include <QSplitter>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle(tr("纳秒脉冲电化学监控系统"));

    CreateInit();
    CreateLayout();
    this->setFixedSize(980, 393);   //窗口大小固定为980*393
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

    connect(powerwidget, SIGNAL(SendPowerData(PowerToHandleData)),
            this, SLOT(GetPowerData(PowerToHandleData)));
    connect(runwidget, SIGNAL(SendRunData(RunToHandleData)),
            this, SLOT(GetRunData(RunToHandleData)));
    connect(this, SIGNAL(SendPowerData(HandleToComData)),
            comportwidget, SLOT(GetSendData(HandleToComData)));
    connect(this, SIGNAL(SendRunData(HandleToComData)),
            comportwidget, SLOT(GetSendData(HandleToComData)));

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
    emit SendPowerData(m_data);
}

void MainWindow::GetRunData(RunToHandleData rundata)
{
    m_data = m_handle.RunDataHandle(rundata);
    emit SendRunData(m_data);
}







