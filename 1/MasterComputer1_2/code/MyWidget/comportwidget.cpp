#include "comportwidget.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include "datahandle.h"

ComPortWidget::ComPortWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("串口调试"));
    CreateInit();
    CreateLayout();
}

void ComPortWidget::CreateInit()
{
//    TittleLabel = new QLabel(tr("串口调试:"));
    RecvDataLable = new QLabel(tr("串口接受数据:"));
    SendDataLabel = new QLabel(tr("串口发送数据:"));
    SelectComLabel = new QLabel(tr("端口:"));
    SelectBPSLabel = new QLabel(tr("波特率:"));

    OpenComButton = new QPushButton(tr("打开串口"));
    OpenComButton->setEnabled(true);
    connect(OpenComButton,SIGNAL(clicked(bool)),
            this, SLOT(MyOpenCom()));

    CloseComButton = new QPushButton(tr("关闭串口"));
    CloseComButton->setEnabled(false);
    connect(CloseComButton, SIGNAL(clicked(bool)),
            this, SLOT(MyCloseCom()));

    SendDataButton = new QPushButton(tr("发送数据"));
    SendDataButton->setEnabled(false);
    connect(SendDataButton, SIGNAL(clicked(bool)),
            this, SLOT(MySendData()));

    ClearRecvTextButton = new QPushButton(tr("清空接受显示"));
    ClearRecvTextButton->setEnabled(false);
    connect(ClearRecvTextButton, SIGNAL(clicked(bool)),
            this, SLOT(MyClearRecvText()));

    ClearSendTextButton = new QPushButton(tr("清空发送显示"));
    ClearSendTextButton->setEnabled(false);
    connect(ClearSendTextButton, SIGNAL(clicked(bool)),
            this, SLOT(MyClearSendText()));

    SelectComComboBox = new QComboBox;
    SelectComComboBox->addItem(tr("COM1"));
    SelectComComboBox->addItem(tr("COM2"));
    SelectComComboBox->addItem(tr("COM3"));
    SelectComComboBox->addItem(tr("COM4"));
    SelectComComboBox->addItem(tr("COM5"));
    SelectComComboBox->setCurrentIndex(0);  //默认是COM1

    SelectBPSComboBox = new QComboBox;
    SelectBPSComboBox->addItem(tr("4800"));
    SelectBPSComboBox->addItem(tr("9600"));
    SelectBPSComboBox->addItem(tr("14400"));
    SelectBPSComboBox->addItem(tr("56000"));
    SelectBPSComboBox->addItem(tr("115200"));
    SelectBPSComboBox->setCurrentIndex(4);  //默认是115200

    RecvHexShowCheckBox = new QCheckBox(tr("十六进制显示"));
    SendHexShowCheckBox = new QCheckBox(tr("十六进制发送"));

    RecvDataTextEdit = new QTextEdit;
    RecvDataTextEdit->setFixedHeight(80);
    RecvDataTextEdit->setReadOnly(true);
    SendDataTextEdit = new QTextEdit;
    SendDataTextEdit->setFixedHeight(80);
    SendDataTextEdit->setReadOnly(true);

}

void ComPortWidget::CreateLayout()
{
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setHorizontalSpacing(10);
    mainLayout->setVerticalSpacing(10);
    //mainLayout->addWidget(TittleLabel, 0, 0);
    mainLayout->addWidget(SelectComLabel, 0, 0, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(SelectComComboBox, 0, 1);
    mainLayout->addWidget(SelectBPSLabel, 0, 2, 1, 1, Qt::AlignRight);
    mainLayout->addWidget(SelectBPSComboBox, 0, 3);

    mainLayout->addWidget(RecvDataLable, 1, 0);
    mainLayout->addWidget(RecvHexShowCheckBox, 1, 1);
    mainLayout->addWidget(ClearRecvTextButton, 1, 3);

    mainLayout->addWidget(RecvDataTextEdit, 2, 0, 1, 4);

    mainLayout->addWidget(SendDataLabel, 3, 0);
    mainLayout->addWidget(SendHexShowCheckBox, 3, 1);
    mainLayout->addWidget(ClearSendTextButton, 3, 3);

    mainLayout->addWidget(SendDataTextEdit, 4, 0, 1, 4);

    mainLayout->addWidget(SendDataButton, 5, 1);
    mainLayout->addWidget(OpenComButton, 5, 2);
    mainLayout->addWidget(CloseComButton, 5, 3);


    this->setLayout(mainLayout);
}

void ComPortWidget::MyOpenCom()
{
    OpenComButton->setEnabled(false);
    CloseComButton->setEnabled(true);
    SendDataButton->setEnabled(true);
}

void ComPortWidget::MyCloseCom()
{
    OpenComButton->setEnabled(true);
    CloseComButton->setEnabled(false);
    SendDataButton->setEnabled(false);
}

void ComPortWidget::MyClearRecvText()
{
    RecvDataTextEdit->clear();
  //  ClearTextButton->setEnabled(false);
}

void ComPortWidget::MyClearSendText()
{
    SendDataTextEdit->clear();
    ClearSendTextButton->setEnabled(false);
}

void ComPortWidget::MySendData()
{}

void ComPortWidget::GetSendData(HandleToComData data)
{
    ClearSendTextButton->setEnabled(true);
    switch (data.flag) {
    case HandleToComData::POWERDATA:
        SendDataTextEdit->append(tr("电源设定数据:"));
        break;
    case HandleToComData::RUNDATA:
        SendDataTextEdit->append(tr("运动设定数据:"));
        break;
    default:
        break;
    }

    SendDataTextEdit->append(data.data);
}





