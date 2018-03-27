#ifndef SOCKETWIDGET_H
#define SOCKETWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QRegExp>
#include <QTcpSocket>

class SocketWidget : public QWidget
{
    Q_OBJECT

public:
    SocketWidget(QWidget *parent = 0);
    ~SocketWidget();

private slots:
    void ConnectServer();   //连接服务器
    void SendData();        //向服务器发送数据
    void RecvData();        //接受从服务器发回的数据
    void ShowError(QAbstractSocket::SocketError socketError);       //展示错误信息
    void CloseConnectServer();    //关闭连接

private:
    void CreateInit();
    void CreateLayout();

private:
    static const char *IPREGEXP;
    static const char *PORTREGEXP;
    QLabel *ServerIPLabel;
    QLineEdit *ServerIPLineEdit;
    QLabel *ServerPortLabel;
    QLineEdit *ServerPortLineEdit;
    QLabel *RecvLabel;
    QLabel *SendLabel;
    QTextEdit *RecvTextEdit;
    QTextEdit *SendTextEidt;
    QPushButton *RecvClearBtn;
    QPushButton *SendClearBtn;
    QPushButton *SendBtn;
    QPushButton *ConnectBtn;

   // int ConBtnFlag;

    QTcpSocket *tcpSocket;
    quint16 m_recvsize;
};

#endif // SOCKETWIDGET_H
