/*
 * 电源设定界面
*/

#ifndef POWERWIDGET_H
#define POWERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class PowerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PowerWidget(QWidget *parent = 0);

signals:

public slots:

private:
    QLabel *PulseWidthLable;    //脉冲宽度
    QLabel *PulseRateLabel;     //脉冲频率
    QLabel *PowerLabel;         //幅值电压
    QLabel *PowerCheckLabel;    //幅值检测
    QLineEdit *PulseWidthEidt;
    QLineEdit *PulseRateEdit;
    QLineEdit *PowerEdit;
    QLineEdit *PowerCheckEdit;
    QPushButton *setOk;         //参数设定按钮

    QLabel *TittleLabel;        //标题

    void CreateInit();
    void CreateLayout();

};

#endif // POWERWIDGET_H
