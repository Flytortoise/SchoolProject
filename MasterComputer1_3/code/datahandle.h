/*
 * 数据处理类
 */

#ifndef DATAHANDLE_H
#define DATAHANDLE_H

#include "transmitdata.h"


class DataHandle{
public:
    DataHandle();

    HandleToComData PowerDataHandle(PowerToHandleData &powerdata);  //处理电源设定数据
    HandleToComData RunDataHandle(RunToHandleData &rundata);        //处理运动设定数据

    ComToRunData AnalysisComData(QByteArray comdata);

private:   
    unsigned int CRCHandle(unsigned int len);
    void SetMyData(unsigned int TempData, unsigned int &begin);     //设置m_data的数据

    HandleToComData m_data;
};

#endif // DATAHANDLE_H
