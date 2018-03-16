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


class ComPortWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ComPortWidget(QWidget *parent = 0);

signals:
    void EmitRecvData();      //将接收到的数据发送给主界面

public slots:
    void GetSendData(HandleToComData);  //从数据处理线程获取需要发送的数据
    void MySendData();      //用来发送信息的槽函数
    void MyRecvData();      //接受信息的槽函数

private slots:
    void MyOpenCom();       //打开串口
    void MyCloseCom();      //关闭串口
    void MyClearRecvText(); //清除接受显示窗口
    void MyClearSendText(); //清空发送显示窗口

private:
   // QLabel *TittleLabel;
    QLabel *RecvDataLable;
    QLabel *SendDataLabel;
    QLabel *SelectComLabel;
    QLabel *SelectBPSLabel;

    QPushButton *OpenComButton;
    QPushButton *CloseComButton;
    QPushButton *SendDataButton;
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

};

#endif // COMPORTWIDGET_H
