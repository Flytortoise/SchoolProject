#include "voltagewidget.h"
#include <QVBoxLayout>

VoltageWidget::VoltageWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("极间电压"));
    CreateInit();
    CreateLayout();
}

void VoltageWidget::CreateInit()
{
    voltageInput = new QLineEdit;
    voltageOutput = new QLineEdit;
    voltageOutput->setEnabled(false);

    TittleLabel = new QLabel(tr("极间电压:"));
}

void VoltageWidget::CreateLayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(TittleLabel);
    mainLayout->addWidget(voltageInput);
    mainLayout->addWidget(voltageOutput);
    this->setLayout(mainLayout);
}
