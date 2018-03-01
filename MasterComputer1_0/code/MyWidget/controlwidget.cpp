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
    xPlus = new QPushButton(tr("+X"));
    xSub = new QPushButton(tr("-X"));
    yPlus = new QPushButton(tr("+Y"));
    ySub = new QPushButton(tr("-Y"));
    zPlus = new QPushButton(tr("+Z"));
    zSub = new QPushButton(tr("-Z"));
    pztPlus = new QPushButton(tr("+PZT"));
    pztSub = new QPushButton(tr("-PZT"));

    TittleLable = new QLabel(tr("点动控制:"));
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
