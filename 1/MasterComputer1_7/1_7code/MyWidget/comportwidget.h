/*
 *串口调试窗口
 */

#ifndef COMPORTWIDGET_H
#define COMPORTWIDGET_H


#include <QWidget>
#include <QLabel>
#include <QTextEdit>    //文编编辑框
#include <QPushButton>  //按钮
#include <QComboBox>    //下拉框
#include <QCheckBox>    //复选框
#include <QMessageBox>  //串口错误提示框
#include "transmitdata.h"   //传输数据
#include "win_qextserialport.h"     //串口头文件
#include <QTimer>
#include "promptmessage.h"

class ComPortWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ComPortWidget(QWidget *parent = 0);


signals:
    void EmitRecvData(QByteArray);      //将接收到的数据发送给主界面
    void HideAllButton();
    void ShowAllButton();

public slots:
    void GetSendData(HandleToComData);  //从主界面获取需要发送的数据
    void MySendData(int DataFlat = SENDDATA);      //用来发送信息的槽函数
    void MyRecvData();      //接受信息的槽函数

private slots:
    void MyOpenCom();       //打开串口
    void MyCloseCom();      //关闭串口
    void MyClearRecvText(); //清除接受显示窗口
    void MyClearSendText(); //清空发送显示窗口

private:
    int HandleRecvData();   //处理接受的数据
    void HandleResponseData(bool flag);  //处理标志信息
    void HideButton();
    void ShowButton(bool flag);

private:
    enum{
        SENDDATA,       //发送数据信息
        RESPONSEDATA    //发送应答信息
    };
   // QLabel *TittleLabel;
    QLabel *RecvDataLable;
    QLabel *SendDataLabel;
    QLabel *SelectComLabel;
    QLabel *SelectBPSLabel;

    QPushButton *OpenComButton;
    QPushButton *CloseComButton;
   // QPushButton *SendDataButton;
    QPushButton *ClearRecvTextButton;
    QPushButton *ClearSendTextButton;

    QComboBox *SelectComComboBox;
    QComboBox *SelectBPSComboBox;

    QTextEdit *RecvDataTextEdit;
    QTextEdit *SendDataTextEdit;

    Win_QextSerialPort *myCom;  //串口

    void CreateInit();
    void CreateLayout();

    QByteArray m_SendData;
    QByteArray m_RecvData;
    QByteArray m_ResponseData;

    QTimer *SingualrTimer;
    QTimer *AllTimer;

    PromptMessage *promptmessage;   //提示信息
    QTimer *SendTimer;              //控制整体发送时间
};

#endif // COMPORTWIDGET_H
