#include "comportwidget.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include "datahandle.h"
#include <QDebug>
#include <QMessageBox>
#include <QTextFormat>

static bool isSendDataOk = false;     //是否发送成功
static bool isOpenStatus = false;       //打开按钮状态

ComPortWidget::ComPortWidget(QWidget *parent) : QWidget(parent),
    m_SendData(32,0), m_RecvData(32,0), m_ResponseData(32,0)
{
    this->setWindowTitle(tr("串口调试"));
    CreateInit();
    CreateLayout();
    MyOpenCom();    //默认先打开一次
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

/*    SendDataButton = new QPushButton(tr("发送数据"));
    SendDataButton->setEnabled(false);
    connect(SendDataButton, SIGNAL(clicked(bool)),
            this, SLOT(MySendData()));
*/
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
    SelectComComboBox->setCurrentIndex(2);  //默认是COM2

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

    SingualrTimer = new QTimer(this);
    connect(SingualrTimer, &QTimer::timeout,
            [this](){     
        MyCloseCom();   //关闭串口
        promptmessage->close();
        SingualrTimer->stop();
        SendTimer->stop();
        ShowButton(false);
        QMessageBox::critical(this, tr("发送失败"),tr("发送超时!!"),QMessageBox::NoButton,QMessageBox::NoButton);

    });

    myCom = new Win_QextSerialPort(SelectComComboBox->currentText(),
                                   QextSerialBase::EventDriven);

   SendTimer = new QTimer(this);
   connect(SendTimer, &QTimer::timeout,
           [this](){

        MyCloseCom();   //关闭串口
        promptmessage->close();
        SingualrTimer->stop();
        SendTimer->stop();
        ShowButton(false);
        QMessageBox::critical(this, tr("错误"), tr("发送失败！！！"),
                             QMessageBox::NoButton,QMessageBox::NoButton);

   });

   promptmessage = new PromptMessage;
   PromptTimer = new QTimer(this);
   connect(PromptTimer,&QTimer::timeout,
           [this](){
       PromptTimer->stop();
       if(!isSendDataOk)
           promptmessage->show();
   });

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

//    mainLayout->addWidget(SendDataButton, 5, 1);
    mainLayout->addWidget(OpenComButton, 5, 2);
    mainLayout->addWidget(CloseComButton, 5, 3);


    this->setLayout(mainLayout);
}

void ComPortWidget::MyOpenCom()
{  
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
//        if(isSendDataOk)
//           SendDataButton->setEnabled(true);
        connect(myCom, SIGNAL(readyRead()),
                this, SLOT(MyRecvData()));
        //当缓存中存在数据时，调用接受函数

    }
    else
    {
        QMessageBox::critical(NULL,tr("严重错误"),tr("<font size='+2'>串口打开失败! 请检查端口和波特率，重新打开!!"),
                              QMessageBox::Ok, QMessageBox::Ok);
    }

}

void ComPortWidget::MyCloseCom()
{
    //isSendDataOk = false;
    myCom->close(); //串口关闭

    OpenComButton->setEnabled(true);
    CloseComButton->setEnabled(false);
//    SendDataButton->setEnabled(false);
}

void ComPortWidget::MyClearRecvText()
{
    RecvDataTextEdit->clear();
    ClearRecvTextButton->setEnabled(false);
}

void ComPortWidget::MyClearSendText()
{
   // isSendDataOk = false;
//    SendDataButton->setEnabled(false);   //发送信息按钮关闭
    SendDataTextEdit->clear();
    ClearSendTextButton->setEnabled(false);
}

void ComPortWidget::MySendData(int DataFlag)
{

    if(DataFlag == SENDDATA)
    {
        isSendDataOk = false;
        SingualrTimer->stop();
        SingualrTimer->start(2000);     //2s检查一次
        myCom->write(m_SendData);       //发送数据信息
    }
    else
        myCom->write(m_ResponseData);   //发送标志信息

}

void ComPortWidget::MyRecvData()
{
    m_RecvData = myCom->readAll();  //读取所有的信息
    if(m_RecvData.isEmpty())
        return;

    RecvDataTextEdit->append(tr("接收到的信息:"));
    RecvDataTextEdit->append(QString(m_RecvData.toHex().data()));
    ClearRecvTextButton->setEnabled(true);  //接收到信息时，设置可清空
    HandleRecvData();
    //emit EmitRecvData(m_RecvData);

}

void ComPortWidget::GetSendData(HandleToComData data)
{
    if(OpenComButton->isEnabled())          //打开串口可以工作，说明没打开串口
    {
        QMessageBox::critical(NULL,tr("错误"),tr("<font size='+2'>串口未打开，消息发送失败！"),
                              QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    ClearSendTextButton->setEnabled(true);      //清空消息按钮打开
    switch (data.flag) {
    case HandleToComData::POWERDATA:
        SendDataTextEdit->append(tr("电源设定数据:"));
        break;
    case HandleToComData::RUNDATA:
        SendDataTextEdit->append(tr("运动设定数据:"));
        break;
    case HandleToComData::CONDATA:
        SendDataTextEdit->append(tr("点位控制数据:"));
        break;
    case HandleToComData::PROBEGINDATA:
        SendDataTextEdit->append(tr("加工开始数据:"));
        break;
    case HandleToComData::PROENDDATA:
        SendDataTextEdit->append(tr("加工结束:"));
        break;
    default:
        break;
    }

    SendDataTextEdit->append(QString(data.data.toHex().data()));
    m_SendData = data.data;

    SendTimer->stop();
    SendTimer->start(5000);
    PromptTimer->stop();
    PromptTimer->start(800);    //0.8s,延迟0.8s后显示窗口，避免数据传输正确时，闪烁界面
    //promptmessage->show();
    HideButton();
    MySendData(SENDDATA);
}


int ComPortWidget::HandleRecvData()
{
    if(CRCHandle(m_RecvData, 31))  //CRC验证为非0说明数据有错
    {
        if(0x09 == m_RecvData[0])   //数据信息
        {
            //发送错误标志信息
            HandleResponseData(false);   //处理应答信息
            MySendData(RESPONSEDATA);           //发送正确标识信息

        }
        else  if(0x10 == m_RecvData[0]) //应答信息
        {

            MySendData(SENDDATA);       //出错，重新发送数据信息
        }
        return 1;
    }

    //返回信息数据无错
    if(0x09 == m_RecvData[0] )   //数据信息
    {
        HandleResponseData(true);   //处理应答信息
        MySendData(RESPONSEDATA);           //发送正确标识信息
        SingualrTimer->stop();
        emit EmitRecvData(m_RecvData);  //传回给运动控制显示的数据

    }
    else if(0x10 == m_RecvData[0]) //应答信息
    {
        if(0x00 == m_RecvData[1])   //无错，标识位为真
        {
            SingualrTimer->stop();  //单趟定时器关闭
            SendTimer->stop();      //总定时器关闭
            promptmessage->close();
            ShowButton(true);
            isSendDataOk = true;
        }
        else
            MySendData(SENDDATA);       //出错，重新发送
    }

    return 0;
}

void ComPortWidget::HandleResponseData(bool flag)
{
    ByteArrayClear(m_SendData); //清空
    m_ResponseData[0] = 0x10;
    m_ResponseData[1] = flag ? 0x00 : 0x01;
    unsigned short CrcFlag = CRCHandle(m_ResponseData, 29);
    m_ResponseData[29] = CrcFlag >> 8;
    m_ResponseData[30] = CrcFlag & 0xff;
    m_ResponseData[31] = 0x10;
}

void ComPortWidget::HideButton()
{
    isOpenStatus = OpenComButton->isEnabled();  //保存状态
    OpenComButton->setEnabled(false);
    CloseComButton->setEnabled(false);
    emit HideAllButton();
}

void ComPortWidget::ShowButton(bool flag)
{
    if(flag)
    {
        OpenComButton->setEnabled(isOpenStatus);
        CloseComButton->setEnabled(!isOpenStatus);
    }

    emit ShowAllButton();
}




















