/*
 * 类与类之间的传递信息
 */

#ifndef TRANSMITDATA_H
#define TRANSMITDATA_H

#include <QString>
#include <QByteArray>

unsigned short CRCHandle(QByteArray &data,unsigned int len);
void ByteArrayClear(QByteArray &data); //QByteArray清0

struct PowerToHandleData        //电源设定数据
{
    QString PulseWidethString;  //脉冲宽度
    QString PulseRateString;    //脉冲频率
    QString PowerString;        //幅值电压
};

struct RunToHandleData          //运动设定数据
{
    enum{
        ShowPositon = 0,
        SetPositon = 1,
        SetSpeed = 2             //展示，设置位置和设置速度
    };
    QString xData[3];           //x位置展示、设定和速度设定
    QString yData[3];           //y位置展示、设定和速度设定
    QString zData[3];           //z位置展示、设定和速度设定
    QString pztData[2];         //pzt位置展示、设定
};

struct ComToRunData
{
    enum{
      XIndex = 0,
      YIndex = 1,
      ZIndex = 2,
      PZTIndex = 3
    };
    bool isOk = false;          //
    bool isPlus[3];              //是否为正方向
    double PositionData[4];     //接收到的信息
};

struct HandleToComData          //传给串口处理好的数据
{
    HandleToComData();
    HandleToComData(const HandleToComData &other);
    void clear();

    enum{
        EMPTYDATA,
        POWERDATA,
        RUNDATA,
        CONDATA,
        PROBEGINDATA,
        PROENDDATA,
        DATALEN = 32
    };
    char flag;
    QByteArray data;
};

#endif // TRANSMITDATA_H