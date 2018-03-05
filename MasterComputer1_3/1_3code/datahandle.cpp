#include "datahandle.h"
#include <QDebug>
#include "transmitdata.h"

DataHandle::DataHandle()
{

}

HandleToComData DataHandle::PowerDataHandle(PowerToHandleData &powerdata)
{
/*    qDebug() << "PulseWideth:" << powerdata.PulseWidethString << "\n"
             << "PulseRate:" << powerdata.PulseRateString << "\n"
             << "PowerSting:"<< powerdata.PowerString << "\n\n";
*/
    unsigned int m_dataIndex = 0;   //m_data下标
    m_data.flag = HandleToComData::POWERDATA;
    m_data.data[m_dataIndex++] = 0x09;   //开头
    m_data.data[m_dataIndex++] = 0x0A;   //电源设定标识


    //脉冲宽度
    SetMyData(static_cast<unsigned int>(powerdata.PulseWidethString.toDouble() * 1000),
              m_dataIndex);

    //幅值电压
    SetMyData(static_cast<unsigned int>(powerdata.PowerString.toDouble() * 1000),
              m_dataIndex);

    //脉冲频率
    SetMyData(static_cast<unsigned int>(powerdata.PulseRateString.toDouble() *1000),
              m_dataIndex);

    m_data.data[29] = 0x8D;  //CRC标识位
    m_data.data[30] = 0x8E;  //CRC标识位
    unsigned int CRCFlag = CRCHandle(29);
    m_data.data[29] = CRCFlag >> 8;
    m_data.data[30] = CRCFlag & 0xff;
    m_data.data[31] = 0x10;  //结束位

    return m_data;
}

HandleToComData DataHandle::RunDataHandle(RunToHandleData &rundata)
{
/*    qDebug() << "x:" << rundata.xData[0] << " " << rundata.xData[1] << "\n"
             << "y:" << rundata.yData[0] << " " << rundata.yData[1] << "\n"
             << "z:" << rundata.zData[0] << " " << rundata.zData[1] << "\n"
             << "pzt:" << rundata.pztData << "\n\n";
*/

    m_data.flag = HandleToComData::RUNDATA;
    unsigned int m_dataIndex = 0;   //m_data下标
    m_data.data[m_dataIndex++] = 0x09;   //开头
    m_data.data[m_dataIndex++] = 0x0B;   //运动设定标识

    double m_TempXPositon = rundata.xData[RunToHandleData::ShowPositon].toDouble()
                                     - rundata.xData[RunToHandleData::SetPositon].toDouble();
    double m_TempYPositon = rundata.yData[RunToHandleData::ShowPositon].toDouble()
                                     - rundata.yData[RunToHandleData::SetPositon].toDouble();
    double m_TempZPositon = rundata.zData[RunToHandleData::ShowPositon].toDouble()
                                     - rundata.zData[RunToHandleData::SetPositon].toDouble();
    double m_TempPZTPositon = rundata.pztData[RunToHandleData::ShowPositon].toDouble()
                                       - rundata.pztData[RunToHandleData::SetPositon].toDouble();

    if(m_TempXPositon >= 0)
        m_data.data[23] = 0x00;     //x+
    else
    {
        m_TempXPositon = -m_TempXPositon;
        m_data.data[23] = 0x01;      //x-
    }

    if(m_TempYPositon >= 0)
        m_data.data[23] = 0x00 | m_data.data[23];     //y+
    else
    {
        m_TempYPositon = -m_TempYPositon;
        m_data.data[23] = 0x02 | m_data.data[23];      //y-
    }

    if(m_TempZPositon >= 0)
        m_data.data[23] = 0x00 | m_data.data[23];     //z+
    else
    {
        m_TempZPositon = -m_TempZPositon;
        m_data.data[23] = 0x04 | m_data.data[23];      //z-
    }

    if(m_TempPZTPositon >= 0){}
       // m_data.data[23] = 0x00 | m_data.data[23];     //pzt+
    else
    {
        m_TempPZTPositon = -m_TempPZTPositon;
       // m_data.data[23] = 0x08 | m_data.data[23];      //pzt-
    }


    //X差值
    SetMyData(static_cast<unsigned int>(m_TempXPositon * 1000),
              m_dataIndex);

    //Y差值
    SetMyData(static_cast<unsigned int>(m_TempYPositon * 1000),
              m_dataIndex);

    //Z差值
    SetMyData(static_cast<unsigned int>(m_TempZPositon *1000),
              m_dataIndex);

    //PZT差值
    SetMyData(static_cast<unsigned int>(m_TempPZTPositon *1000),
              m_dataIndex);

    //X设定速度
    SetMyData(static_cast<unsigned int>( rundata.xData[RunToHandleData::SetPositon].toDouble() * 1000),
              m_dataIndex);

    //Y设定速度
    SetMyData(static_cast<unsigned int>( rundata.yData[RunToHandleData::SetPositon].toDouble() * 1000),
              m_dataIndex);

    //Z设定速度
    SetMyData(static_cast<unsigned int>( rundata.zData[RunToHandleData::SetPositon].toDouble() * 1000),
              m_dataIndex);

    m_data.data[29] = 0x8D;  //CRC标识位
    m_data.data[30] = 0x8E;  //CRC标识位
    unsigned int CRCFlag = CRCHandle(29);
    m_data.data[29] = CRCFlag >> 8;
    m_data.data[30] = CRCFlag & 0xff;
    m_data.data[31] = 0x10;  //结束位

    return m_data;
}

unsigned int DataHandle::CRCHandle(unsigned int len)
{
    unsigned int CrcFlag = 0xFFFF;
    unsigned int m_dataIndex = 0;
    while(len--)
    {
        for(unsigned char i=0x80; i != 0; i >>= 1)	//8次循环
        {
            if((CrcFlag & 0x8000) != 0)   //如果最高位为1
            {
                CrcFlag <<= 1;
                CrcFlag ^= 0x1021;
            }
            else
            {
                CrcFlag <<= 1;
            }
            if((m_data.data[m_dataIndex]&i) != 0)
                CrcFlag ^= 0x1021;
        }
        m_dataIndex++;
    }
    return CrcFlag;		//Crc校验码
}

void DataHandle::SetMyData(unsigned int TempData, unsigned int &begin)
{
    m_data.data[begin++] = (TempData >> 16) & 0xff;
    m_data.data[begin++] = (TempData >> 8) & 0xff;
    m_data.data[begin++] = TempData & 0xff;
}

ComToRunData DataHandle::AnalysisComData(QByteArray comdata)
{
    ComToRunData rundata;
    if(0x09 == comdata[0])
    {
        if(0x1F <= comdata[1] && 0x2F >= comdata[1])
            rundata.isOk = true;

        //X
        rundata.PositionData[ComToRunData::XIndex] =
                static_cast<double>((comdata[2]<<16)+(comdata[3]<<8)+comdata[4])/1000;
        if((comdata[23] & 0x01) == 0)
            rundata.isPlus[ComToRunData::XIndex] = true;
        else
            rundata.isPlus[ComToRunData::XIndex] = false;

        //Y
        rundata.PositionData[ComToRunData::YIndex] =
                static_cast<double>((comdata[5]<<16)+(comdata[6]<<8)+comdata[7])/1000;
        if((comdata[23] & 0x02) == 0)
            rundata.isPlus[ComToRunData::YIndex] = true;
        else
            rundata.isPlus[ComToRunData::YIndex] = false;

        //Z
        rundata.PositionData[ComToRunData::ZIndex] =
                static_cast<double>((comdata[8]<<16)+(comdata[9]<<8)+comdata[10])/1000;
        if((comdata[23] & 0x04) == 0)
            rundata.isPlus[ComToRunData::ZIndex] = true;
        else
            rundata.isPlus[ComToRunData::ZIndex] = false;

        //PZT
        rundata.PositionData[ComToRunData::PZTIndex] =
                static_cast<double>((comdata[11]<<16)+(comdata[12]<<8)+comdata[13])/1000;

    }

    return rundata;
}


