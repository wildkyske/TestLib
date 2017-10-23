#include "../include/DebugObject.h"


DebugObject::DebugObject() : mErrorCode(0)
{

}

DebugObject::~DebugObject()
{

}

void DebugObject::setErrorString( const tstring& strErrorInfo )
{
    mStrErrInfo = strErrorInfo;
}

const tstring& DebugObject::errorString() const
{
    return mStrErrInfo;
}

void DebugObject::setErrorCode( int nCode )
{
    mErrorCode = nCode;
}

int DebugObject::errorCode() const
{
    return mErrorCode;
}
