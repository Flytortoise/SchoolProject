#include "controlwidget.h"
#include <QVBoxLayout>

ControlWidget::ControlWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("点动控制"));
    CreateInit();
    CreateLayout();
}

void ControlWidget::CreateInit()
{
    //ConData = new QByteArray(3, 0);   //长度位3,初始值都为0
    ConData[0] = 0x20;
    ConData[2] = 0x10;        //固定格式，每次按下按钮才会改变ConData[1]的值

    xPlus = new QPushButton(tr("+X"));
    xSub = new QPushButton(tr("-X"));
    yPlus = new QPushButton(tr("+Y"));
    ySub = new QPushButton(tr("-Y"));
    zPlus = new QPushButton(tr("+Z"));
    zSub = new QPushButton(tr("-Z"));
    pztPlus = new QPushButton(tr("+PZT"));
    pztSub = new QPushButton(tr("-PZT"));

    TittleLable = new QLabel(tr("点动控制:"));

    connect(xPlus, SIGNAL(clicked(bool)),
            this, SLOT(HandleXPlusData()));
    connect(xSub, SIGNAL(clicked(bool)),
            this, SLOT(HandleXSubData()));
    connect(yPlus, SIGNAL(clicked(bool)),
            this, SLOT(HandleYPlusData()));
    connect(ySub, SIGNAL(clicked(bool)),
            this, SLOT(HandleYSubData()));
    connect(zPlus, SIGNAL(clicked(bool)),
            this, SLOT(HandleZPlusData()));
    connect(zSub, SIGNAL(clicked(bool)),
            this, SLOT(HandleZSubData()));
    connect(pztPlus, SIGNAL(clicked(bool)),
            this, SLOT(HandlePZTPlusData()));
    connect(pztSub, SIGNAL(clicked(bool)),
            this, SLOT(HandlePZTSubData()));

}

void ControlWidget::CreateLayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(TittleLable);
    mainLayout->addWidget(xPlus);
    mainLayout->addWidget(xSub);
    mainLayout->addWidget(yPlus);
    mainLayout->addWidget(ySub);
    mainLayout->addWidget(zPlus);
    mainLayout->addWidget(zSub);
    mainLayout->addWidget(pztPlus);
    mainLayout->addWidget(pztSub);

    this->setLayout(mainLayout);
}

void ControlWidget::HandleXPlusData()
{
    ConData[1] = 0x20;

    emit SendConData();
}

void ControlWidget::HandleXSubData()
{
    ConData[1] = 0x21;

    emit SendConData();
}

void ControlWidget::HandleYPlusData()
{
    ConData[1] = 0x22;

    emit SendConData();
}

void ControlWidget::HandleYSubData()
{
    ConData[1] = 0x23;

    emit SendConData();
}

void ControlWidget::HandleZPlusData()
{
    ConData[1] = 0x24;

    emit SendConData();
}

void ControlWidget::HandleZSubData()
{
    ConData[1] = 0x25;

    emit SendConData();
}

void ControlWidget::HandlePZTPlusData()
{
    ConData[1] = 0x26;

    emit SendConData();
}

void ControlWidget::HandlePZTSubData()
{
    ConData[1] = 0x27;

    emit SendConData();
}




