#include "powerwidget.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QGridLayout>

//正则表达式
const char *PowerWidget::REGEXP = "^[0]|((-?[0-9]{1,4})(\\.\\d{0,3}))$";

PowerWidget::PowerWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("电源设定"));

    CreateInit();
    CreateLayout();

}

void PowerWidget::CreateInit()
{
    QRegExp regExp(REGEXP);
    //检查器，可以输入[-9999.999,9999.999]

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

    setOkButton = new QPushButton(tr("参数设定"));
    connect(setOkButton, SIGNAL(clicked(bool)),
            this, SLOT(HandlePowerData()));

    TittleLabel = new QLabel(tr("电源设定:"));
}

void PowerWidget::CreateLayout()
{
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(TittleLabel, 0, 0);
    mainLayout->addWidget(PulseWidthLable,1,0);
    mainLayout->addWidget(PulseWidthEidt, 1, 1);
    mainLayout->addWidget(PowerLabel, 1, 3);
    mainLayout->addWidget(PowerEdit, 1, 4);
    mainLayout->addWidget(PulseRateLabel, 2, 0);
    mainLayout->addWidget(PulseRateEdit, 2, 1);
    mainLayout->addWidget(PowerCheckLabel, 2, 3);
    mainLayout->addWidget(PowerCheckEdit, 2, 4);
    mainLayout->addWidget(setOkButton, 2, 6);
    mainLayout->setHorizontalSpacing(10);
    mainLayout->setVerticalSpacing(10);
    this->setLayout(mainLayout);
}

void PowerWidget::HandlePowerData()
{
    PowerData.PulseWidethString = PulseWidthEidt->text();
    PowerData.PulseRateString = PulseRateEdit->text();
    PowerData.PowerString = PowerEdit->text();
    emit SendPowerData();
}



