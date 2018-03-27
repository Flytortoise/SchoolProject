/*
 * 类与类之间的传递信息
 */

#ifndef TRANSMITDATA_H
#define TRANSMITDATA_H

#include <QString>

struct PowerToHandleData        //电源设定数据
{
    QString PulseWidethString;  //脉冲宽度
    QString PulseRateString;    //脉冲频率
    QString PowerString;        //幅值电压
};

struct RunToHandleData          //运动设定数据
{
    enum{
        Positon = 0,
        Speed = 1               //位置和速度
    };
    QString xData[2];           //x位置设定和速度设定
    QString yData[2];           //y位置设定和速度设定
    QString zData[2];           //z位置设定和速度设定
    QString pztData;            //pzt位置设定
};

struct HandleToComData          //传给串口处理好的数据
{
    enum{
        POWERDATA,
        RUNDATA
    };
    char flag;
    QString data;
};

#endif // TRANSMITDATA_H
