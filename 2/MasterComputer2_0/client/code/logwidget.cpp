#include "logwidget.h"
#include <QGridLayout>

LogWidget::LogWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("登陆"));
    CreateInit();
    CreateLayout();
    this->setFixedSize(QWidget::sizeHint());
}

void LogWidget::CreateInit()
{
    UserNameLabel = new QLabel(tr("用户名:"));
    UserNameLineEdit = new QLineEdit;
    PassWdLabel = new QLabel(tr("密码:"));
    PassWdLineEdit = new QLineEdit;

    OkBtn = new QPushButton(tr("确定"));
    m_RegisterDialog = nullptr;

    RegisterBtn = new QPushButton("注册");
    connect(RegisterBtn, &QPushButton::clicked,
            [this](){
        if(m_RegisterDialog == nullptr)
            m_RegisterDialog = new RegisterDialog;
        m_RegisterDialog->exec();
    });
}

void LogWidget::CreateLayout()
{
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setHorizontalSpacing(10);
    mainLayout->setVerticalSpacing(10);

    mainLayout->addWidget(UserNameLabel, 0, 0);
    mainLayout->addWidget(UserNameLineEdit, 0, 1, 1, 2);
    mainLayout->addWidget(PassWdLabel, 1, 0);
    mainLayout->addWidget(PassWdLineEdit, 1, 1, 1, 2);
    mainLayout->addWidget(RegisterBtn, 2, 1);
    mainLayout->addWidget(OkBtn, 2, 2);
    //mainLayout->addWidget(ExitBtn, 2, 3);
    this->setLayout(mainLayout);
}






















