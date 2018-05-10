#include "processwidget.h"
#include <QHBoxLayout>
#include <QGridLayout>
static bool oldEnable[2];

ProcessWidget::ProcessWidget(QWidget *parent) : QWidget(parent)
{
    CreateInit();
    CreateLayout();

}

void ProcessWidget::CreateInit()
{
    //TittleLabel = new QLabel(tr("加工控制："));
    BeginBtn = new QPushButton(tr("开始加工"));
    BeginBtn->setEnabled(true);
    connect(BeginBtn, &QPushButton::clicked,
            [this](){
        BeginBtn->setEnabled(!BeginBtn->isEnabled());
        EndBtn->setEnabled(!EndBtn->isEnabled());
        emit SendProcessData(true);
    });

    EndBtn = new QPushButton(tr("结束加工"));
    EndBtn->setEnabled(false);
    connect(EndBtn, &QPushButton::clicked,
            [this](){
        BeginBtn->setEnabled(!BeginBtn->isEnabled());
        EndBtn->setEnabled(!EndBtn->isEnabled());
        emit SendProcessData(false);
    });
}

void ProcessWidget::CreateLayout()
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(10);
    //mainLayout->addWidget(TittleLabel);
    mainLayout->addStretch(1);
    mainLayout->addWidget(BeginBtn);
    mainLayout->addWidget(EndBtn);

}

void ProcessWidget::HideButton()
{
    oldEnable[0] = BeginBtn->isEnabled();
    oldEnable[1] = EndBtn->isEnabled();

    BeginBtn->setEnabled(false);
    EndBtn->setEnabled(false);
}

void ProcessWidget::ShowButton()
{
    BeginBtn->setEnabled(oldEnable[0]);
    EndBtn->setEnabled(oldEnable[1]);
}
