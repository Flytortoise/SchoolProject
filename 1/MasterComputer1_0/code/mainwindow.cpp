#include "mainwindow.h"
#include <QSplitter>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle(tr("纳秒脉冲电化学监控系统"));

    CreateInit();
    CreateLayout();
    this->setFixedSize(sizeHint()); //固定合适大小
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

    exitButton = new QPushButton(tr("退出"));
    connect(exitButton, SIGNAL(clicked(bool)),
            this, SLOT(close()));
}

void MainWindow::CreateLayout()
{
    QSplitter *leftSplitter = new QSplitter(Qt::Vertical);
    leftSplitter->addWidget(powerwidget);
    leftSplitter->addWidget(runwidget);
    leftSplitter->addWidget(voltagewidget);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(controlwidget);
    rightLayout->addWidget(exitButton);
    rightLayout->addStretch(1);
    QWidget *rightWidget = new QWidget;
    rightWidget->setLayout(rightLayout);

    QSplitter *mainSplitter = new QSplitter(Qt::Horizontal);
    mainSplitter->addWidget(leftSplitter);
    mainSplitter->addWidget(rightWidget);

    setCentralWidget(mainSplitter);
}










