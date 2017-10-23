#pragma once
#ifndef GLOBAL_KEY_GENERATOR_H
#define GLOBAL_KEY_GENERATOR_H

#include "md5.h"
#include "UtilityExport.h"

#include <string>

class UTILITY_EXPORT GlobalKeyGenerator
{
public:
    GlobalKeyGenerator();
    ~GlobalKeyGenerator();

    static int genNewKey();

    static void md5Code(unsigned char* pSrc, int nSize, char pCode[MD5_DEFAULT_BUFFER_SIZE]);

    static std::string md5Code(unsigned char* pSrc, int nSize);

    static std::string md5Code(const std::string& strSrc);

protected:
    static int mCurKey;
};

#endif
