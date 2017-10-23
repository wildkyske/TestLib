#pragma once
#ifndef XEncoder_h__
#define XEncoder_h__

#include "UtilityExport.h"
#include "typedefs.h"

namespace XEncoder
{
    // @Brief MD5���� [7/1/2013 Administrator]
    UTILITY_EXPORT bool md5Encode(std::string& strCryptData, const std::string& strSrcData);

    // @Brief MD5���� [4/24/2015 kyske]
    UTILITY_EXPORT bool md5Encode(std::wstring& strCryptData, const std::wstring& strSrcData);

    // @Brief ��ȡMD5����Ĭ�ϳ��� [7/1/2013 Administrator]
    extern "C" UTILITY_EXPORT int GetMd5DefaultSize();
}
#endif // XEncoder_h__
