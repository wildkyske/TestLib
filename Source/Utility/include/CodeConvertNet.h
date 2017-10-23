#pragma once
#ifndef CodeConvertNet_h__
#define CodeConvertNet_h__

#include "UtilityExport.h"
#include <string>

//包含跨平台的字节序转换
namespace CodeConvert
{
    enum
    {
        NUM_UNKNOWN_ORDER = 0,
        NUM_LITTLE_ENDIAN_ORDER = 1,
        NUM_BIG_ENDIAN_ORDER = 2,
    };

    //主机序转大端序
    UTILITY_EXPORT int hostToBig(int nValue);

    UTILITY_EXPORT short int hostToBig(short int nValue);

    //主机序转小端序
    UTILITY_EXPORT int hostToLittle(int nValue);

    UTILITY_EXPORT short int hostToLittle(short int nValue);

    //大端序转主机序
    UTILITY_EXPORT int bigToHost(int nValue);

    UTILITY_EXPORT short int bigToHost(short int nValue);

    //小端序转主机序
    UTILITY_EXPORT int littleToHost(int nValue);

    UTILITY_EXPORT short int littleToHost(short int nValue);

    //大小端调换函数[int]
    UTILITY_EXPORT int swapByteOrder(int nValue);

    //交换大小端
    UTILITY_EXPORT short int swapByteOrder(short int nValue);

    //获取本机字节序
    UTILITY_EXPORT int getHostByteOrder();

    //使用大端序转换,例如: "1.2.3.4" => 0x01020304
    UTILITY_EXPORT int ipStr2Int(const std::string& strIpAddr);

    //使用大端序换换,例如: 0x01020304 => "1.2.3.4"
    UTILITY_EXPORT std::string int2IpStr(int nAddr);

    UTILITY_EXPORT void macAddr2Buffer(const std::string& strMacAddr, unsigned char* szBuffer, int nLen);

    UTILITY_EXPORT void buffer2MacAddr(unsigned char* szBuffer, int nLen, std::string& rStrMacAddr);
}
#endif // CodeConvertNet_h__

