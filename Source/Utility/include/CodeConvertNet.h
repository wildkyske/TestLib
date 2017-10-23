#pragma once
#ifndef CodeConvertNet_h__
#define CodeConvertNet_h__

#include "UtilityExport.h"
#include <string>

//������ƽ̨���ֽ���ת��
namespace CodeConvert
{
    enum
    {
        NUM_UNKNOWN_ORDER = 0,
        NUM_LITTLE_ENDIAN_ORDER = 1,
        NUM_BIG_ENDIAN_ORDER = 2,
    };

    //������ת�����
    UTILITY_EXPORT int hostToBig(int nValue);

    UTILITY_EXPORT short int hostToBig(short int nValue);

    //������תС����
    UTILITY_EXPORT int hostToLittle(int nValue);

    UTILITY_EXPORT short int hostToLittle(short int nValue);

    //�����ת������
    UTILITY_EXPORT int bigToHost(int nValue);

    UTILITY_EXPORT short int bigToHost(short int nValue);

    //С����ת������
    UTILITY_EXPORT int littleToHost(int nValue);

    UTILITY_EXPORT short int littleToHost(short int nValue);

    //��С�˵�������[int]
    UTILITY_EXPORT int swapByteOrder(int nValue);

    //������С��
    UTILITY_EXPORT short int swapByteOrder(short int nValue);

    //��ȡ�����ֽ���
    UTILITY_EXPORT int getHostByteOrder();

    //ʹ�ô����ת��,����: "1.2.3.4" => 0x01020304
    UTILITY_EXPORT int ipStr2Int(const std::string& strIpAddr);

    //ʹ�ô���򻻻�,����: 0x01020304 => "1.2.3.4"
    UTILITY_EXPORT std::string int2IpStr(int nAddr);

    UTILITY_EXPORT void macAddr2Buffer(const std::string& strMacAddr, unsigned char* szBuffer, int nLen);

    UTILITY_EXPORT void buffer2MacAddr(unsigned char* szBuffer, int nLen, std::string& rStrMacAddr);
}
#endif // CodeConvertNet_h__

