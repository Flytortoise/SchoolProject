#include "promptmessage.h"
#include <QFont>
#include <QHBoxLayout>

PromptMessage::PromptMessage(QWidget *parent)
    : QDialog(parent)
{
    this->setWindowTitle(tr("提示"));
    CreateInit();
    CreateLayout();
    this->setFixedSize(263,121);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
}

void PromptMessage::CreateInit()
{
    MessageLabel = new QLabel;
    MessageLabel->setText(tr("信息发送中，请稍后..."));
    QFont ft;
    ft.setPointSize(12);
    MessageLabel->setFont(ft);
}

void PromptMessage::CreateLayout()
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addStretch(1);
    mainLayout->addWidget(MessageLabel);
    mainLayout->addStretch(1);

}
