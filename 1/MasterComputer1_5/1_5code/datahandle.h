/*
 * 数据处理类
 */

#ifndef DATAHANDLE_H
#define DATAHANDLE_H

#include "transmitdata.h"


class DataHandle{
public:
    DataHandle();

    HandleToComData PowerDataHandle(PowerToHandleData &powerdata);  //封装电源设定数据
    HandleToComData RunDataHandle(RunToHandleData &rundata);        //封装运动设定数据
    HandleToComData ConDataHandle(QByteArray &condata);             //封装点位控制数据

    ComToRunData AnalysisComData(QByteArray comdata);               //解析串口发回的数据

private:   
    unsigned int CRCHandle(unsigned int len);
    void SetMyData(unsigned int TempData, unsigned int &begin);     //封装时设置m_data的数据

    HandleToComData m_data;
};

#endif // DATAHANDLE_H
