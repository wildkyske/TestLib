#include "../include/GlobalKeyGenerator.h"

int GlobalKeyGenerator::mCurKey = 0;

GlobalKeyGenerator::GlobalKeyGenerator()
{

}

GlobalKeyGenerator::~GlobalKeyGenerator()
{

}

int GlobalKeyGenerator::genNewKey()
{
    int nKey = mCurKey;
    mCurKey++;
    return nKey;
}

void GlobalKeyGenerator::md5Code( unsigned char* pSrc, 
                                 int nSize, char pCode[MD5_DEFAULT_BUFFER_SIZE] )
{
    GetMD5Code(pSrc, nSize, pCode);
}

std::string GlobalKeyGenerator::md5Code( unsigned char* pSrc, int nSize )
{
    char pCode[MD5_DEFAULT_BUFFER_SIZE] = {0};
    md5Code(pSrc, nSize, pCode);
    return std::string(pCode);
}

std::string GlobalKeyGenerator::md5Code( const std::string& strSrc )
{
    return md5Code((unsigned char*)strSrc.c_str(), strSrc.length());
}
