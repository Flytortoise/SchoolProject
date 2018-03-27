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
#include "transmitdata.h"


class ComPortWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ComPortWidget(QWidget *parent = 0);

signals:

public slots:
    void GetSendData(HandleToComData);  //从主界面获取需要发送的数据
    void MySendData();

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

    QCheckBox *RecvHexShowCheckBox;
    QCheckBox *SendHexShowCheckBox;

    QTextEdit *RecvDataTextEdit;
    QTextEdit *SendDataTextEdit;

    void CreateInit();
    void CreateLayout();

};

#endif // COMPORTWIDGET_H
