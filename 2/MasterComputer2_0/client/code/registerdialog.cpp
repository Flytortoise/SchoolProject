#include "registerdialog.h"
#include <QGridLayout>

RegisterDialog::RegisterDialog(QWidget *parent):QDialog(parent)
{
    this->setWindowTitle(tr("注册"));
    CreateInit();
    CreateLayout();
    setFixedSize(QWidget::sizeHint());
}

void RegisterDialog::CreateInit()
{
    UserNameLabel = new QLabel(tr("用户名:"));
    UserNameLineEdit = new QLineEdit;
    PassWdLabel1 = new QLabel(tr("密码:"));
    PassWdLineEdit1 = new QLineEdit;
    PassWdLabel2 = new QLabel(tr("确认密码:"));
    PassWdLineEdit2 = new QLineEdit;

    OkBtn = new QPushButton(tr("确定"));
}

void RegisterDialog::CreateLayout()
{
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setHorizontalSpacing(10);
    mainLayout->setVerticalSpacing(10);

    mainLayout->addWidget(UserNameLabel, 0, 0);
    mainLayout->addWidget(UserNameLineEdit, 0, 1, 1, 2);
    mainLayout->addWidget(PassWdLabel1, 1, 0);
    mainLayout->addWidget(PassWdLineEdit1, 1, 1, 1, 2);
    mainLayout->addWidget(PassWdLabel2, 2, 0);
    mainLayout->addWidget(PassWdLineEdit2, 2, 1, 1, 2);
    mainLayout->addWidget(OkBtn, 3, 2);
    this->setLayout(mainLayout);
}















