#include "../include/CodeConvert.h"
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <memory.h>

namespace CodeConvert
{
    //----------------------------------------
    // char2wchar_t 该函数必须兼容
    //----------------------------------------
    bool mb2wc(const char* mbstr, 
        wchar_t* wcstr, int nMaxLen)
    {
        //UNICODE
        setlocale(LC_ALL,  ".936");
        size_t size, sizeRet;
        size = mbstowcs(NULL,  mbstr,  0);
        if (size > (size_t)nMaxLen || NULL == wcstr)
        {
            return false;
        }
        memset(wcstr, 0, nMaxLen * sizeof(wchar_t));
        sizeRet = mbstowcs(wcstr, mbstr,  size + 1);
        return (-1 != sizeRet);
    }

    //---------------------------------------------
    //wchar_t2char
    //---------------------------------------------
    bool wc2mb(const wchar_t* wcstr, 
        char* mbstr, int nMaxLen)
    {
        setlocale(LC_ALL,  ".936");
        size_t size, sizeRet;
        size = wcstombs(NULL, wcstr, 0);
        if (size > (size_t)nMaxLen || NULL == mbstr)
        {
            return false;
        }
        memset(mbstr, 0, nMaxLen * sizeof(char));
        sizeRet = wcstombs(mbstr, wcstr, size + 1);
        return (-1 != sizeRet);
    }

    bool wstr2str( const std::wstring& wstr, std::string& str )
    {
        int nLen = wstr.length();
        nLen += 1;
        wchar_t* buf = new wchar_t[nLen + 1];
        memset(buf, 0, sizeof(wchar_t) * (nLen + 1));
        memcpy(buf, wstr.c_str(), nLen * sizeof(wchar_t));

        //这里加一个补偿长度，因为，返回长度可能不足
        nLen += 256;
        char* szBuf = new char[nLen + 1];
        memset(szBuf, 0, nLen + 1);

        bool bRet = wc2mb(buf, szBuf, nLen);
        str = std::string(szBuf);

        delete[] buf;
        delete[] szBuf;
        return bRet;
    }

    bool str2wstr( const std::string& str, std::wstring& wstr )
    {
        int nLen = str.length();
        nLen += 1;
        char* buf = new char[nLen + 1];
        memset(buf, 0, sizeof(char) * (nLen + 1));
        memcpy(buf, str.c_str(), nLen * sizeof(char));

        wchar_t* szBuf = new wchar_t[nLen + 1];
        memset(szBuf, 0, sizeof(wchar_t) * (nLen + 1));

        bool bRet = mb2wc(buf, szBuf, nLen);
        wstr = std::wstring(szBuf);

        delete[] buf;
        delete[] szBuf;
        return bRet;
    }

    bool mb2x( const char* str, xchar* rlt, int nMaxLen )
    {
#if defined(UNICODE)
        return mb2wc(str, rlt, nMaxLen);
#else
        memcpy(rlt, str, nMaxLen);
        return true;
#endif
    }

    bool wc2x( const wchar_t* str, xchar* rlt, int nMaxLen )
    {
#if defined(UNICODE)
        memcpy(rlt, str, nMaxLen * sizeof(xchar));
        return true;
#else
        return wc2mb(str, rlt, nMaxLen);
#endif
    }

    tstring str2x( const std::string& str )
    {
#if defined(UNICODE)
        tstring wstr;
        str2wstr(str, wstr);
        return wstr;
#else
        return str;
#endif
    }

    tstring wstr2x( const std::wstring& str )
    {
#if defined(UNICODE)
        return str;
#else
        tstring rlt;
        wstr2str(str, rlt);
        return rlt;
#endif
    }

    bool x2mb( const xchar* xstr, char* rlt, int nMaxLen )
    {
#if defined(UNICODE)
        return wc2mb(xstr, rlt, nMaxLen);
#else
        memcpy(rlt, xstr, nMaxLen);
        return true;
#endif
    }

    UTILITY_EXPORT std::string x2str( const tstring& xstr )
    {
#if defined(UNICODE)
        std::string rlt;
        wstr2str(xstr, rlt);
        return rlt;
#else
        return xstr;
#endif
    }

    bool x2wc( const xchar* xstr, wchar_t* rlt, int nMaxLen )
    {
#if defined(UNICODE)
        memcpy(rlt, xstr, nMaxLen * sizeof(xchar));
        return true;
#else
        return mb2wc(xstr, rlt, nMaxLen);
#endif
    }

    std::wstring x2wstr( const tstring& str )
    {
#if defined(UNICODE)
        return str;
#else
        std::wstring rlt;
        str2wstr(str, rlt);
        return rlt;
#endif
    }

    //2015-03-19增加的函数:确认Unicode是否为utf16编码
    void utf8ToUnicode(wchar_t* pOut,char *pText)
    {
        char* uchar = (char *)pOut;

        uchar[1] = ((pText[0] & 0x0F) << 4) + ((pText[1] >> 2) & 0x0F);
        uchar[0] = ((pText[1] & 0x03) << 6) + (pText[2] & 0x3F);
    }

    typedef union 
    {
        wchar_t c;
        char l;
        char h;
    }ucharx;

    int ucs2ToUtf8(char* pOut,const wchar_t u8Char)
    {
        char* pchar = (char *)&u8Char;    //这里隐含了小端序
        int nUsedByte = 0;

        //模板:0xxxxxxx
        if (u8Char <= 0x007f)
        {
            pOut[0] = pchar[0];

            nUsedByte = 1;
        }
        //模板:110xxxxx 10xxxxxx
        else if (u8Char >= 0x0080 && u8Char <= 0x07ff)
        {
            pOut[0] = (((pchar[1] << 2) | ((pchar[0] & 0xfc) >> 6)) | 0xc0);
            pOut[1] = ((pchar[0] | 0x3f) | 0x80);

            nUsedByte = 2;
        }
        //模板:1110xxxx 10xxxxxx 10xxxxxx
        else
        {
            pOut[0] = (((pchar[1] & 0xf0) >> 4) | 0xe0);
            pOut[1] = (((pchar[1] & 0x0f) << 2) | ((pchar[0] & 0xc0)  >> 6)) | 0x80;
            pOut[2] = (pchar[0] & 0x3f) | 0x80;

            nUsedByte = 3;
        }

        return nUsedByte;
    }

    int utf8ToUcs2( wchar_t& rOut, const char* pValue )
    {
        //判断多少字节编码
        int nRet = 0;
        char* pChar = (char*)&rOut; //隐含了小端序
        //编码1字节
        if ( (pValue[0] & 0x80) == 0)
        {
            nRet = 1;

            pChar[0] = pValue[0];
        }
        else
        {
            //两字节编码
            if ( (pValue[0] & 0xe0) == 0xc0)
            {
                nRet = 2;

                pChar[0] = ((pValue[1] & 0x3f) | (pValue[0] << 6));
                pChar[1] = ((pValue[0] & 0x1c) >> 2);
            }
            //三字节编码
            else if ( (pValue[0] & 0xe0) == 0xe0)
            {
                nRet = 3;

                pChar[0] = (((pValue[1] & 0x03) << 6) | (pValue[2] & 0x3f));
                pChar[1] = (((pValue[0] & 0x0f) << 4) | ((pValue[1] & 0x3c) >> 2));
            }
        }
        return nRet;
    }

    int ucs2strToUtf8( char* pOut, const wchar_t* pU8Str )
    {
        if (NULL == pOut || NULL == pU8Str)
        {
            return -1;
        }
        const wchar_t* pSrc = pU8Str;
        char* pDst = pOut;
        int nRet = 0;
        while (0 != (*pSrc))
        {
            int nNum = ucs2ToUtf8(pDst, *pSrc);
            pDst += nNum;
            nRet += nNum;
            ++pSrc;
        }

        return nRet;
    }

    std::string ucs2strToUtf8( const std::wstring& strValue )
    {
        const int NUM_LEN = strValue.length() * 3;
        char* pOut = new char[NUM_LEN + 1];
        memset(pOut, 0x00, NUM_LEN + 1);
        int nRet = ucs2strToUtf8(pOut, strValue.c_str());
        std::string strRlt(pOut);
        delete[] pOut;
        return strRlt;
    }

    int utf8strToUcs2( wchar_t* pOut, const char* pValue )
    {
        if (NULL == pOut || NULL == pValue)
        {
            return -1;
        }

        wchar_t* pDst = pOut;
        const char* pSrc = pValue;
        int nRet = 0;

        while(0 != (*pSrc))
        {
            int nNum = utf8ToUcs2(*pDst, pSrc);
            pSrc += nNum;
            nRet += nNum;
            ++pDst;
        }

        return nRet;
    }

    std::wstring utf8strToUcs2( const std::string& strValue )
    {
        const int  NUM_LEN = strValue.length() * 2;
        wchar_t* pOut = new wchar_t[NUM_LEN + 1];
        memset(pOut, 0x00, (NUM_LEN + 1) * sizeof(wchar_t));
        int nRet = utf8strToUcs2(pOut, strValue.c_str());
        std::wstring strRlt(pOut);
        delete[] pOut;
        return strRlt;
    }

    std::string gb2312ToUtf8( const std::string& strValue )
    {
        std::wstring temp;
        str2wstr(strValue, temp);

        return ucs2strToUtf8(temp);
    }

    std::string utf8Togb2312( const std::string& strValue )
    {
        std::wstring temp = utf8strToUcs2(strValue);
        std::string strRlt;
        wstr2str(temp, strRlt);

        return strRlt;
    }
}
