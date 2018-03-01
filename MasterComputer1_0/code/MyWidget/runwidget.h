/*
 * 运动设定
*/
#ifndef RUNWIDGET_H
#define RUNWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPushButton>

class RunWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RunWidget(QWidget *parent = 0);

signals:

public slots:

private:
    enum {
        mmSize = 6,
        mm_sSize = 3,
        umSize = 2,
        setSizeData = 4,
        speedSizeData = 3
    };

    QLabel *xLocationLabel;     // X坐标
    QLabel *yLocationLabel;     // Y坐标
    QLabel *zLocationLabel;     // Z坐标
    QLabel *pztLocationLabel;   // PZT坐标
    QLabel *setLabel[setSizeData];  //设置
    QLabel *speedLabel[speedSizeData];  //速度
    QLabel *mmUnitLabel[mmSize];        //mm
    QLabel *mm_sUnitLabel[mm_sSize];    // mm/s
    QLabel *umUnitLabel[umSize];        //um

    QLineEdit *xLocationEdit;
    QLineEdit *yLocationEdit;
    QLineEdit *zLocationEdit;
    QLineEdit *pztLocationEdit;
    QLineEdit *setEdit[setSizeData];
    QLineEdit *speedEdit[speedSizeData];

    QPushButton *setOk;     //参数确定按钮

    QLabel *TittleLabel;    //标题

    void CreateInit();  //初始化控件
    void CreateLayout();    //布局

};

#endif // RUNWIDGET_H











