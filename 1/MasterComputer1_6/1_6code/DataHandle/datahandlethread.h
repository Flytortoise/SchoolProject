#ifndef DATAHANDLETHREAD_H
#define DATAHANDLETHREAD_H

#include <QThread>
#include <QMutex>
#include "datahandle.h"
#include "transmitdata.h"

class DataHandleThread : public  QThread    //数据处理线程
{
    Q_OBJECT
public:
    DataHandleThread(int DataFlag = 0);

signals:
    void SendReadyData(HandleToComData);    //向串口界面发送封装好的数据
    void ComToRun(ComToRunData);     //已处理好串口传回的数据，发给运动设定

protected:
    void run();

private:
    QMutex m_mutex;                 //锁
    DataHandle *m_handle;           //数据处理
    HandleToComData m_data;         //发给串口的数据
    ComToRunData m_ToRunData;       //串口发给运动设定的数据

    int m_dataFlag;                 //用来区分调用的处理函数
};

#endif // DATAHANDLETHREAD_H
