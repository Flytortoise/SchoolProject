#include "transmitdata.h"

//#include <iostream>
//#include <typeinfo>
//using namespace std;

HandleToComData::HandleToComData()
                :flag(POWERDATA),data(DATALEN, 0)
{}

HandleToComData::HandleToComData(const HandleToComData &other)
                :flag(other.flag),data(other.data)
{}

/*
template<typename _Tp>
std::string GetName(_Tp t)
{
    std::string name = "";
    if (std::is_const<decltype(t)>::value)
        name += "const ";
    name += typeid(t).name();
    if (std::is_reference<decltype(t)>::value)
        name += "&";

    return name;
}
*/


void HandleToComData::clear()
{
    flag = 0;

    for(auto &tmp : data)
    {
        tmp = 0x00;
//std::cout << GetName<decltype(tmp)>(tmp) << std::endl;
    }
}


PowerToHandleData PowerData;        //全局的PowerToHandleData变量
RunToHandleData RunData;
QByteArray ComRunData;
HandleToComData HandleComData;
ConToHandle ConData(3,0);


