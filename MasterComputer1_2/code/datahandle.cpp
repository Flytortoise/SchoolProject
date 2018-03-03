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

    m_data.flag = HandleToComData::POWERDATA;
    m_data.data = powerdata.PulseWidethString;

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
    m_data.data = rundata.pztData;
    return m_data;
}



