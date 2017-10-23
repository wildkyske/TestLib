#pragma once
#ifndef CODE_CONVERT_H
#define CODE_CONVERT_H

#include "typedefs.h"
#include "UtilityExport.h"

//¶à×Ö½Ú×ªUnicode

namespace CodeConvert
{
    //----------------------------------------
    // char2wchar_t ¸Ãº¯Êý±ØÐë¼æÈÝ
    //----------------------------------------
    extern "C" UTILITY_EXPORT bool mb2wc(const char* mbstr, 
        wchar_t* wcstr, int nMaxLen);

    //---------------------------------------------
    //wchar_t2char
    //---------------------------------------------
    extern "C" UTILITY_EXPORT bool wc2mb(const wchar_t* wcstr, 
        char* mbstr, int nMaxLen);

    // @Brief ¿í×Ö´®×ª×Ö´® [10/30/2013 Administrator]
    UTILITY_EXPORT bool wstr2str(const std::wstring& wstr, std::string& str);

    // @Brief ×Ö´®×ª¿í×Ö´® [10/30/2013 Administrator]
    UTILITY_EXPORT bool str2wstr(const std::string& str, std::wstring& wstr);

    // @Brief ÆäËû×Ö·û´®×ªµ±Ç°Ê¹ÓÃ×Ö·û´® [10/31/2013 Administrator]
    extern "C" UTILITY_EXPORT bool mb2x(const char* str, xchar* rlt, int nMaxLen);

    extern "C" UTILITY_EXPORT bool wc2x(const wchar_t* str, xchar* rlt, int nMaxLen);

    UTILITY_EXPORT tstring str2x(const std::string& str);

    UTILITY_EXPORT tstring wstr2x(const std::wstring& str);

    // @Brief µ±Ç°×Ö´®×ª¿í×Ö·û [10/31/2013 Administrator]
    extern "C" UTILITY_EXPORT bool x2mb(const xchar* xstr, char* rlt, int nMaxLen);

    UTILITY_EXPORT std::string x2str(const tstring& xstr);

    // @Brief µ±Ç°×Ö·û×ªÒ»°ã×Ö·û [10/31/2013 Administrator]
    extern "C" UTILITY_EXPORT bool x2wc(const xchar* xstr, wchar_t* rlt, int nMaxLen);

    UTILITY_EXPORT std::wstring x2wstr(const tstring& str);

    extern "C" UTILITY_EXPORT void utf8ToUnicode(wchar_t* pOut,char *pText);

    //ucs2±àÂë×ªutf8±àÂë
    extern "C" UTILITY_EXPORT int ucs2ToUtf8(char* pOut, const wchar_t u8Char);

    //utf8±àÂë×ªucs2±àÂë
    extern "C" UTILITY_EXPORT int utf8ToUcs2(wchar_t& rOut, const char* pValue);

    //ucs2±àÂë×Ö·û´®×ªutf8±àÂë
    extern "C" UTILITY_EXPORT int ucs2strToUtf8(char* pOut, const wchar_t* pU8Str);

    //utf8×Ö·û´®×ªucs2×Ö·û´®
    extern "C" UTILITY_EXPORT int utf8strToUcs2(wchar_t* pOut, const char* pValue);

    //ucs2±àÂë×ªutf8
    UTILITY_EXPORT std::string ucs2strToUtf8(const std::wstring& strValue);

    UTILITY_EXPORT std::wstring utf8strToUcs2(const std::string& strValue);

    UTILITY_EXPORT std::string gb2312ToUtf8(const std::string& strValue);

    UTILITY_EXPORT std::string utf8Togb2312(const std::string& strValue);
}

#endif
