#include "../include/XEncoder.h"
#include "../include/md5.h"
#include "../include/CodeConvert.h"
//#include <tchar.h>

namespace XEncoder
{
    int GetMd5DefaultSize()
    {
        return MD5_DEFAULT_LEN;
    }

    bool md5Encode( std::string& strCryptData, const std::string& strSrcData )
    {
        //MD5±àÂë
        char szMD5Code[MD5_DEFAULT_BUFFER_SIZE] = {0};
        GetMD5Code((unsigned char*)strSrcData.c_str(), strSrcData.length(), szMD5Code);

        return true;
    }

    bool md5Encode( std::wstring& strCryptData, const std::wstring& strSrcData )
    {
        //×ª»»ÎªMB
        int nSrcLen = strSrcData.length();
        const int nSrcMaxBufferLen = nSrcLen * sizeof(xchar);
        char* szSrcBuffer = new char[nSrcMaxBufferLen + 1];
        memset(szSrcBuffer, 0x00, nSrcMaxBufferLen + 1);
        CodeConvert::wc2mb(strSrcData.c_str(), szSrcBuffer, nSrcMaxBufferLen);

        std::string strSrc;
        CodeConvert::wstr2str(strSrcData, strSrc);

        //MD5±àÂë
        std::string strDst;
        md5Encode(strDst, strSrc);

        CodeConvert::str2wstr(strDst, strCryptData);

        return true;
    }

}
