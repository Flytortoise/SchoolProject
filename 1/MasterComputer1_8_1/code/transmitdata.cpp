#include "transmitdata.h"

HandleToComData::HandleToComData()
                :flag(EMPTYDATA),data(DATALEN, 0)
{}

HandleToComData::HandleToComData(const HandleToComData &other)
                :flag(other.flag),data(other.data)
{}

void HandleToComData::clear()
{
    flag = 0;
    for(auto &tmp : data)
        tmp = 0x00;
}

unsigned short CRCHandle(QByteArray &data,unsigned int len)
{
    unsigned short CrcFlag = 0xFFFF;  //初值与下位机协定好
    unsigned int m_dataIndex = 0;
    while(len--)
    {
        for(unsigned char i=0x80; i != 0; i >>= 1)	//8次循环
        {
            if((CrcFlag & 0x8000) != 0)   //上一位存在余式，CRC乘以2再求CRC
            {
                CrcFlag <<= 1;
                CrcFlag ^= 0x1021;  //CRC生成多项式  0x1021，欧洲推荐标准
            }
            else                    //上一位不存在余式
            {
                CrcFlag <<= 1;
            }
            if((data[m_dataIndex]&i) != 0)
                CrcFlag ^= 0x1021;                  //最后加上本位的异或值，产生本位CRC
        }
        m_dataIndex++;
    }
    return CrcFlag;		//Crc校验码
}

void ByteArrayClear(QByteArray &data)
{
    for(auto &tmp : data)
        tmp = 0x00;
}
