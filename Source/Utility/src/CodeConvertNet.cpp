#include "../include/CodeConvertNet.h"
#include <stdio.h>

namespace CodeConvert
{
    int swapByteOrder( int nValue )
    {
        int nRlt = ((nValue & 0xff) << 24)
            |((nValue & 0xff00) << 8) | ((nValue & 0xff0000) >> 8) 
            | ((nValue & 0xff000000) >> 24);
        return nRlt;
    }

    short int swapByteOrder( short int nValue )
    {
        short int nRlt = ((nValue & 0xff) << 8)|((nValue & 0xff00) >> 8);
        return nRlt;
    }

    int getHostByteOrder()
    {
        int nValue = 0x12345678;
        char* pValue = (char*)(&nValue);
        if (pValue[0] == 0x78)
        {
            return NUM_LITTLE_ENDIAN_ORDER;
        }

        if (pValue[0] == 0x12)
        {
            return NUM_BIG_ENDIAN_ORDER;
        }

        return NUM_UNKNOWN_ORDER;
    }

    int hostToBig( int nValue )
    {
        int nHostOrder = getHostByteOrder();
        int nRlt = nValue;
        if (nHostOrder == NUM_LITTLE_ENDIAN_ORDER)
        {
            nRlt = swapByteOrder(nValue);
        }
        return nRlt;
    }

    short int hostToBig( short int nValue )
    {
        int nHostOrder = getHostByteOrder();
        short int nRlt = nValue;
        if (nHostOrder == NUM_LITTLE_ENDIAN_ORDER)
        {
            nRlt = swapByteOrder(nValue);
        }
        return nRlt;
    }

    int hostToLittle( int nValue )
    {
        int nHostOrder = getHostByteOrder();
        int nRlt = nValue;
        if (nHostOrder == NUM_BIG_ENDIAN_ORDER)
        {
            nRlt = swapByteOrder(nValue);
        }
        return nRlt;
    }

    short int hostToLittle( short int nValue )
    {
        int nHostOrder = getHostByteOrder();
        short int nRlt = nValue;
        if (nHostOrder == NUM_BIG_ENDIAN_ORDER)
        {
            nRlt = swapByteOrder(nValue);
        }
        return nRlt;
    }

    int bigToHost( int nValue )
    {
        int nHostOrder = getHostByteOrder();
        int nRlt = nValue;
        if (nHostOrder == NUM_LITTLE_ENDIAN_ORDER)
        {
            nRlt = swapByteOrder(nValue);
        }
        return nRlt;
    }

    short int bigToHost( short int nValue )
    {
        int nHostOrder = getHostByteOrder();
        short int nRlt = nValue;
        if (nHostOrder == NUM_LITTLE_ENDIAN_ORDER)
        {
            nRlt = swapByteOrder(nValue);
        }
        return nRlt;
    }

    int littleToHost( int nValue )
    {
        int nHostOrder = getHostByteOrder();
        int nRlt = nValue;
        if (nHostOrder == NUM_BIG_ENDIAN_ORDER)
        {
            nRlt = swapByteOrder(nValue);
        }
        return nRlt;
    }

    short int littleToHost( short int nValue )
    {
        int nHostOrder = getHostByteOrder();
        short int nRlt = nValue;
        if (nHostOrder == NUM_BIG_ENDIAN_ORDER)
        {
            nRlt = swapByteOrder(nValue);
        }
        return nRlt;
    }

    int ipStr2Int( const std::string& strIpAddr )
    {
        int buf[4] = {0};
        sscanf(strIpAddr.c_str(), "%d.%d.%d.%d", &buf[3], &buf[2], &buf[1], &buf[0]);
        int nRet = ((buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0]);

        return nRet;
    }

    std::string int2IpStr( int nAddr )
    {
        unsigned char buf[4] = {0};
        buf[0] = nAddr & 0x000000ff;
        buf[1] = (nAddr >> 8) & 0x000000ff;
        buf[2] = (nAddr >> 16) & 0x000000ff;
        buf[3] = (nAddr >> 24) & 0x000000ff;

        //´ó¶ËÐò 0xc0a8006e
        char szbuf[20 + 1] = {0};
        sprintf(szbuf, "%d.%d.%d.%d", buf[3], buf[2], buf[1], buf[0]);
        return std::string(szbuf);
    }

    void macAddr2Buffer( const std::string& strMacAddr, unsigned char* szBuffer, int nLen )
    {
        sscanf(strMacAddr.c_str(), "%02X-%02X-%02X-%02X-%02X-%02X", &szBuffer[0], &szBuffer[1], 
            &szBuffer[2], &szBuffer[3], &szBuffer[4], &szBuffer[5]);
    }

    void buffer2MacAddr( unsigned char* szBuffer, int nLen, std::string& rStrMacAddr )
    {
        char szTempBuf[127 + 1] = {0};
        sprintf(szTempBuf, "%02X-%02X-%02X-%02X-%02X-%02X", szBuffer[0], szBuffer[1], szBuffer[2], 
            szBuffer[3], szBuffer[4], szBuffer[5]);
        rStrMacAddr = std::string(szTempBuf);
    }

}
