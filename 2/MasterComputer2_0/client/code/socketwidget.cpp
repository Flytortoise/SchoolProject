#include "socketwidget.h"
#include <QGridLayout>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QByteArray>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

const char *SocketWidget::IPREGEXP = "((25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))\\.){3}(25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))";
const char *SocketWidget::PORTREGEXP = "0|[1-9]\\d{0,3}|[1-5]\\d{4}|6[0-5][0-5][0-3][0-5]";


SocketWidget::SocketWidget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("网络连接"));
    CreateInit();
    CreateLayout();
}

void SocketWidget::CreateInit()
{
    QRegExp IPRegExp(IPREGEXP);     //[0.0.0.0 , 255.255.255.255]
    QRegExp PortRegExp(PORTREGEXP); //[0,65535]

    ServerIPLabel = new QLabel(tr("服务器IP:"));
    ServerIPLineEdit = new QLineEdit;
    ServerIPLineEdit->setValidator(new QRegExpValidator(IPRegExp,this));
    ServerIPLineEdit->setText(tr("192.168.10.133"));
    ServerPortLabel = new QLabel(tr("服务器端口号:"));
    ServerPortLineEdit = new QLineEdit;
    ServerPortLineEdit->setValidator(new QRegExpValidator(PortRegExp, this));
    ServerPortLineEdit->setText(tr("8800"));

    RecvLabel = new QLabel(tr("接受信息:"));
    SendLabel = new QLabel(tr("发送信息:"));
    RecvTextEdit = new QTextEdit;
    RecvTextEdit->setFontPointSize(12);
    SendTextEidt = new QTextEdit;
    SendTextEidt->setFontPointSize(12);
    RecvClearBtn = new QPushButton(tr("清除接受区域"));
    connect(RecvClearBtn, &QPushButton::clicked,
            [this](){
        this->RecvTextEdit->clear();
    });

    SendClearBtn = new QPushButton(tr("清除发送区域"));
    connect(SendClearBtn,&QPushButton::clicked,
            [this](){
        this->SendTextEidt->clear();
    });

    ConnectBtn = new QPushButton(tr("连接服务器"));
    connect(ConnectBtn, SIGNAL(clicked(bool)),
            this, SLOT(ConnectServer()));
    SendBtn = new QPushButton(tr("发送信息"));
    connect(SendBtn, SIGNAL(clicked(bool)),
            this, SLOT(SendData()));
    SendBtn->setEnabled(false);

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()),
            this, SLOT(RecvData()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(ShowError(QAbstractSocket::SocketError)));
    connect(tcpSocket, SIGNAL(disconnected()),
            this, SLOT(CloseConnectServer()));
    connect(tcpSocket, &QTcpSocket::connected,
            [this](){
        this->SendBtn->setEnabled(true);
        ConnectBtn->setText("关闭连接！");

    });
    m_recvsize = 0;
  //  ConBtnFlag = 0;
}

void SocketWidget::CreateLayout()
{
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setHorizontalSpacing(10);
    mainLayout->setVerticalSpacing(10);

    mainLayout->addWidget(ServerIPLabel, 0, 0);
    mainLayout->addWidget(ServerIPLineEdit, 0, 1);
    mainLayout->addWidget(ServerPortLabel, 0, 2);
    mainLayout->addWidget(ServerPortLineEdit, 0, 3);

    mainLayout->addWidget(RecvLabel, 1, 0);
    mainLayout->addWidget(RecvClearBtn, 1, 3);

    mainLayout->addWidget(RecvTextEdit, 2, 0, 1, 4);

    mainLayout->addWidget(SendLabel, 3, 0);
    mainLayout->addWidget(SendClearBtn, 3, 3);

    mainLayout->addWidget(SendTextEidt, 4, 0, 1, 4);

    mainLayout->addWidget(SendBtn, 5, 2);
    mainLayout->addWidget(ConnectBtn, 5, 3);
    setLayout(mainLayout);
}

void SocketWidget::ConnectServer()
{
   // QString tmp = ConnectBtn->text();

    if(!QString::compare(ConnectBtn->text(), tr("连接服务器"),Qt::CaseInsensitive))
    {
        //连接服务器操作
        tcpSocket->abort();
        tcpSocket->connectToHost(ServerIPLineEdit->text(),
                                 ServerPortLineEdit->text().toInt());
        RecvTextEdit->append(tr("连接服务器..."));
    }
    else
    {
        //关闭服务器操作
        tcpSocket->close();
        RecvTextEdit->append(tr("关闭连接..."));
        SendBtn->setEnabled(false);
        ConnectBtn->setText(tr("连接服务器"));
    }
   // ConBtnFlag = ~ConBtnFlag;
}

SocketWidget::~SocketWidget()
{

}

void SocketWidget::SendData()
{
    QByteArray senddata;
    QJsonObject jsondata;
    jsondata.insert("data",SendTextEidt->toPlainText());
    QJsonDocument document;
    document.setObject(jsondata);
    senddata = document.toJson(QJsonDocument::Compact);     //定义一个紧凑格式
    tcpSocket->write(senddata);
    RecvTextEdit->append(tr("发送消息:\n%1").arg(SendTextEidt->toPlainText()));
}

void SocketWidget::RecvData()
{
    QByteArray recvdata;
    recvdata = tcpSocket->readAll();

    QJsonParseError json_error;
    QJsonDocument parse_document = QJsonDocument::fromJson(recvdata, &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_document.isObject())
        {
            QJsonObject obj = parse_document.object();
            if(obj.contains("data"))
            {
                QJsonValue value = obj.take("data");
                if(value.isString())
                {
                    RecvTextEdit->append(tr("接受消息:\n%1").arg(value.toString()));

                }
            }
        }
    }
    else
    {
        QMessageBox::critical(this, tr("接受错误！"), json_error.errorString());
            //qDebug() << json_error.errorString();
    }
}

void SocketWidget::CloseConnectServer()
{
    if(m_recvsize != 0xFFFF)
        RecvTextEdit->append(tr("与服务器连接中断..."));
    tcpSocket->close();
    SendBtn->setEnabled(false);
    ConnectBtn->setText(tr("连接服务器"));

}

void SocketWidget::ShowError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("客户端"), tr("主机不可达！"));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("客户端"),tr("连接被拒绝!"));
        break;
    default:
        QMessageBox::information(this,tr("客户端"), tr("产生如下错误：%1.").arg(tcpSocket->errorString()));
        break;
    }
}




