#include "comportwidget.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include "datahandle.h"
#include <QDebug>
#include <QMessageBox>
#include <QTextFormat>

static bool isSendDataOk = false;     //发送信息框是否有内容

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

    RecvDataTextEdit = new QTextEdit;
    RecvDataTextEdit->setFixedHeight(80);
    RecvDataTextEdit->setReadOnly(true);
    SendDataTextEdit = new QTextEdit;
    SendDataTextEdit->setFixedHeight(80);
    SendDataTextEdit->setReadOnly(true);

    myCom = nullptr;


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
    mainLayout->addWidget(ClearRecvTextButton, 1, 3);

    mainLayout->addWidget(RecvDataTextEdit, 2, 0, 1, 4);

    mainLayout->addWidget(SendDataLabel, 3, 0);
    mainLayout->addWidget(ClearSendTextButton, 3, 3);

    mainLayout->addWidget(SendDataTextEdit, 4, 0, 1, 4);

    mainLayout->addWidget(SendDataButton, 5, 1);
    mainLayout->addWidget(OpenComButton, 5, 2);
    mainLayout->addWidget(CloseComButton, 5, 3);


    this->setLayout(mainLayout);
}

void ComPortWidget::MyOpenCom()
{  
    if(myCom)
        delete myCom;
    myCom = new Win_QextSerialPort(SelectComComboBox->currentText(),
                                   QextSerialBase::EventDriven);
    //定义
    if(myCom->open(QIODevice::ReadWrite))  //读写方式打开且成功
    {
        QString BPSData = SelectBPSComboBox->currentText();  //已选择的波特率
        if(BPSData == tr("4800"))
            myCom->setBaudRate(BAUD4800);
        else if(BPSData == tr("9600"))
            myCom->setBaudRate(BAUD9600);
        else if(BPSData == tr("14400"))
            myCom->setBaudRate(BAUD14400);
        else if(BPSData == tr("56000"))
            myCom->setBaudRate(BAUD56000);
        else if(BPSData == tr("115200"))
            myCom->setBaudRate(BAUD115200);

        myCom->setDataBits(DATA_8); //设置数据位为8
        myCom->setParity(PAR_NONE); //无奇偶校验
        myCom->setStopBits(STOP_1); //停止位为1
        myCom->setFlowControl(FLOW_OFF);    //数据流监控关闭
        myCom->setTimeout(500);     //设置500ms延迟

        OpenComButton->setEnabled(false);   //打开串口按钮关闭
        CloseComButton->setEnabled(true);   //关闭串口按钮打开
        if(isSendDataOk)
            SendDataButton->setEnabled(true);
        connect(myCom, SIGNAL(readyRead()),
                this, SLOT(MyRecvData()));
        //当缓存中存在数据时，调用接受函数

    }
    else
    {
        QMessageBox::critical(NULL,tr("严重错误"),tr("<font size='+2'>串口打开失败，请检查错误，重新打开!!"),
                              QMessageBox::Ok, QMessageBox::Ok);
    }

}

void ComPortWidget::MyCloseCom()
{
    isSendDataOk = false;
    myCom->close(); //串口关闭
    delete myCom;
    myCom = nullptr;

    OpenComButton->setEnabled(true);
    CloseComButton->setEnabled(false);
    SendDataButton->setEnabled(false);
}

void ComPortWidget::MyClearRecvText()
{
    RecvDataTextEdit->clear();
    ClearRecvTextButton->setEnabled(false);
}

void ComPortWidget::MyClearSendText()
{
    isSendDataOk = false;
    SendDataButton->setEnabled(false);   //发送信息按钮关闭
    SendDataTextEdit->clear();
    ClearSendTextButton->setEnabled(false);
}

void ComPortWidget::MySendData()
{
    myCom->write(m_SendData);       //发送信息
}

void ComPortWidget::MyRecvData()
{
    m_RecvData = myCom->readAll();  //读取所有的信息
    RecvDataTextEdit->append(tr("接收到的信息:"));
    RecvDataTextEdit->append(QString(m_RecvData.toHex().data()));
    ClearRecvTextButton->setEnabled(true);  //接收到信息时，设置可清空

    emit EmitRecvData(m_RecvData);
}

void ComPortWidget::GetSendData(HandleToComData data)
{
    isSendDataOk = true;
    if(!OpenComButton->isEnabled())         //当打开串口关闭时，发送按钮才能打开
        SendDataButton->setEnabled(true);   //发送信息按钮打开
    ClearSendTextButton->setEnabled(true);      //清空消息按钮打开
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
   // qDebug() << data.data.toHex().data();
    SendDataTextEdit->append(QString(data.data.toHex().data()));
    m_SendData = data.data;
   // qDebug() << m_SendData.toHex();
}





