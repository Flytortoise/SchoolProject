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
