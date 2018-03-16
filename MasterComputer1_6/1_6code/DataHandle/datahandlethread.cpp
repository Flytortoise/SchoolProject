#include "datahandlethread.h"
#include <QMutexLocker>

DataHandleThread::DataHandleThread(int DataFlag)
    :m_dataFlag(DataFlag)
{

}



void DataHandleThread::run()
{
    m_handle = new DataHandle;
    m_mutex.lock();
    switch (m_dataFlag) {
    case DATA::POWER:
        m_data = m_handle->PowerDataHandle(PowerData);
        emit SendReadyData(m_data);
        break;
    case DATA::RUN:
        m_data = m_handle->RunDataHandle(RunData);
        emit SendReadyData(m_data);
        break;
    case DATA::CON:
        m_data = m_handle->ConDataHandle(ConData);
        emit SendReadyData(m_data);
        break;
    case DATA::COMTORUN:
        m_ToRunData = m_handle->AnalysisComData(ComRunData);
        emit ComToRun(m_ToRunData);
        break;
    default:
        break;
    }
    m_mutex.unlock();
    delete m_handle;
}




