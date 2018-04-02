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
    m_condata = new QByteArray(3, 0);   //长度位3,初始值都为0
    (*m_condata)[0] = 0x20;
    (*m_condata)[2] = 0x10;        //固定格式，每次按下按钮才会改变m_condata[1]的值

    AllButton.append(new QPushButton(tr("+X")));
    AllButton.append(new QPushButton(tr("-X")));
    AllButton.append(new QPushButton(tr("+Y")));
    AllButton.append(new QPushButton(tr("-Y")));
    AllButton.append(new QPushButton(tr("+Z")));
    AllButton.append(new QPushButton(tr("-Z")));
    AllButton.append(new QPushButton(tr("+PZT")));
    AllButton.append(new QPushButton(tr("-PZT")));

   /* xPlus = new QPushButton(tr("+X"));
    xSub = new QPushButton(tr("-X"));
    yPlus = new QPushButton(tr("+Y"));
    ySub = new QPushButton(tr("-Y"));
    zPlus = new QPushButton(tr("+Z"));
    zSub = new QPushButton(tr("-Z"));
    pztPlus = new QPushButton(tr("+PZT"));
    pztSub = new QPushButton(tr("-PZT"));
*/
    TittleLable = new QLabel(tr("点动控制:"));

    connect(AllButton.at(0), SIGNAL(clicked(bool)),
            this, SLOT(HandleXPlusData()));
    connect(AllButton.at(1), SIGNAL(clicked(bool)),
            this, SLOT(HandleXSubData()));
    connect(AllButton.at(2), SIGNAL(clicked(bool)),
            this, SLOT(HandleYPlusData()));
    connect(AllButton.at(3), SIGNAL(clicked(bool)),
            this, SLOT(HandleYSubData()));
    connect(AllButton.at(4), SIGNAL(clicked(bool)),
            this, SLOT(HandleZPlusData()));
    connect(AllButton.at(5), SIGNAL(clicked(bool)),
            this, SLOT(HandleZSubData()));
    connect(AllButton.at(6), SIGNAL(clicked(bool)),
            this, SLOT(HandlePZTPlusData()));
    connect(AllButton.at(7), SIGNAL(clicked(bool)),
            this, SLOT(HandlePZTSubData()));

}

void ControlWidget::CreateLayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(TittleLable);
    mainLayout->addWidget(AllButton.at(0));
    mainLayout->addWidget(AllButton.at(1));
    mainLayout->addWidget(AllButton.at(2));
    mainLayout->addWidget(AllButton.at(3));
    mainLayout->addWidget(AllButton.at(4));
    mainLayout->addWidget(AllButton.at(5));
    mainLayout->addWidget(AllButton.at(6));
    mainLayout->addWidget(AllButton.at(7));

    this->setLayout(mainLayout);
}

void ControlWidget::HandleXPlusData()
{
    (*m_condata)[1] = 0x20;

    emit ConToCom(*m_condata);
}

void ControlWidget::HandleXSubData()
{
    (*m_condata)[1] = 0x21;

    emit ConToCom(*m_condata);
}

void ControlWidget::HandleYPlusData()
{
    (*m_condata)[1] = 0x22;

    emit ConToCom(*m_condata);
}

void ControlWidget::HandleYSubData()
{
    (*m_condata)[1] = 0x23;

    emit ConToCom(*m_condata);
}

void ControlWidget::HandleZPlusData()
{
    (*m_condata)[1] = 0x24;

    emit ConToCom(*m_condata);
}

void ControlWidget::HandleZSubData()
{
    (*m_condata)[1] = 0x25;

    emit ConToCom(*m_condata);
}

void ControlWidget::HandlePZTPlusData()
{
    (*m_condata)[1] = 0x26;

    emit ConToCom(*m_condata);
}

void ControlWidget::HandlePZTSubData()
{
    (*m_condata)[1] = 0x27;

    emit ConToCom(*m_condata);
}

void ControlWidget::HideButton()
{
    for(auto &button : AllButton){
        button->setEnabled(false);
    }
}

void ControlWidget::ShowButton()
{
    for(auto &button : AllButton){
        button->setEnabled(true);
    }
}



