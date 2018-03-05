#include "transmitdata.h"

HandleToComData::HandleToComData()
                :flag(POWERDATA),data(DATALEN, 0)
{}

HandleToComData::HandleToComData(const HandleToComData &other)
                :flag(other.flag),data(other.data)
{}

