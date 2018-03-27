/*
 * 电源设定界面
*/

#ifndef POWERWIDGET_H
#define POWERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "transmitdata.h"

class PowerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PowerWidget(QWidget *parent = 0);
signals:
    void SendPowerData(PowerToHandleData);  //向主界面发送数据

public slots:

private:
    static const char *REGEXP;
    //正则表达式，限定

    QLabel *PulseWidthLable;    //脉冲宽度
    QLabel *PulseRateLabel;     //脉冲频率
    QLabel *PowerLabel;         //幅值电压
    QLabel *PowerCheckLabel;    //幅值检测
    QLineEdit *PulseWidthEidt;
    QLineEdit *PulseRateEdit;
    QLineEdit *PowerEdit;
    QLineEdit *PowerCheckEdit;
    QPushButton *setOkButton;         //参数设定按钮

    QLabel *TittleLabel;        //标题

    PowerToHandleData m_data;

    void CreateInit();
    void CreateLayout();

private slots:
    void HandlePowerData();     //处理电源设定数据

};

#endif // POWERWIDGET_H
