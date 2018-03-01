#include "powerwidget.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QGridLayout>

PowerWidget::PowerWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("电源设定"));

    CreateInit();
    CreateLayout();

}

void PowerWidget::CreateInit()
{
    QRegExp regExp("[0-9]{1,2}");   //检查器，可以输入0—99

    PulseWidthLable = new QLabel(tr("脉冲宽度(us):"));
    PulseWidthEidt = new QLineEdit;
    PulseWidthEidt->setText(tr("0"));
    PulseWidthEidt->setValidator(new QRegExpValidator(regExp, this));
    PulseWidthLable->setBuddy(PulseWidthEidt);

    PulseRateLabel = new QLabel(tr("脉冲频率(Hz):"));
    PulseRateEdit = new QLineEdit;
    PulseRateEdit->setText(tr("0"));
    PulseRateEdit->setValidator(new QRegExpValidator(regExp, this));
    PulseRateLabel->setBuddy(PulseRateEdit);

    PowerLabel = new QLabel(tr("幅值电压(V):"));
    PowerEdit = new QLineEdit;
    PowerEdit->setText(tr("0"));
    PowerEdit->setValidator(new QRegExpValidator(regExp, this));
    PowerLabel->setBuddy(PowerEdit);

    PowerCheckLabel = new QLabel(tr("幅值检测(V):"));
    PowerCheckEdit = new QLineEdit;
    PowerCheckEdit->setText(tr("0"));
    PowerCheckEdit->setReadOnly(true);  //只读
    PowerCheckEdit->setEnabled(false);  //显示灰色
    PowerCheckLabel->setBuddy(PowerCheckEdit);

    setOk = new QPushButton(tr("参数设定"));

    TittleLabel = new QLabel(tr("电源设定:"));
}

void PowerWidget::CreateLayout()
{
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(TittleLabel, 0, 0);
    mainLayout->addWidget(PulseWidthLable,1,0);
    mainLayout->addWidget(PulseWidthEidt, 1, 1, 1, 2);
    mainLayout->addWidget(PowerLabel, 1, 3);
    mainLayout->addWidget(PowerEdit, 1, 4, 1, 2);
    mainLayout->addWidget(PulseRateLabel, 2, 0);
    mainLayout->addWidget(PulseRateEdit, 2, 1, 1, 2);
    mainLayout->addWidget(PowerCheckLabel, 2, 3);
    mainLayout->addWidget(PowerCheckEdit, 2, 4, 1, 2);
    mainLayout->addWidget(setOk, 2, 6);
    mainLayout->setHorizontalSpacing(10);
    mainLayout->setVerticalSpacing(10);
    this->setLayout(mainLayout);
}

