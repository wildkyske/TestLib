#include "../include/ThreadCondition.h"
#include "../include/ThreadMutex.h"

ThreadCondition::ThreadCondition() : mHandle(NULL)
{
#ifdef WIN32
    mHandle = ::CreateEvent(NULL, false, false, NULL);
#elif defined(__linux__)

#endif
}

ThreadCondition::~ThreadCondition()
{
    if (NULL != mHandle)
    {
#ifdef WIN32
        ::CloseHandle(mHandle);
#elif defined(__linux__)

#endif
        mHandle = NULL;
    }
}

bool ThreadCondition::signal()
{
    if (NULL == mHandle)
    {
        return false;
    }
#ifdef WIN32
    if (::SetEvent(mHandle))
    {
        return true;
    }
#elif defined(__linux__)

#endif

    return false;
}

bool ThreadCondition::reset()
{
    if (NULL == mHandle)
    {
        return false;
    }
#ifdef WIN32
    if (::ResetEvent(mHandle))
    {
        return true;
    }
#elif defined(__linux__)

#endif
    return false;
}

bool ThreadCondition::wait( int nMiniSecond /*= -1*/ )
{
    if(mHandle == NULL)
    {
        return false;
    }
#ifdef WIN32
    DWORD dwTimeout = 0;
    if(nMiniSecond < 0)
    {
        dwTimeout = INFINITE;
    }
    else
    {
        dwTimeout = nMiniSecond;
    }

    DWORD nRet = ::WaitForSingleObject(mHandle,dwTimeout);
    if(nRet == WAIT_OBJECT_0)
    {
        return true;
    }
    else if(nRet == WAIT_TIMEOUT)
    {
        return false;
    }
    else
    {
        return false;
    }
#elif defined(__linux__)

#endif
    return true;
}

bool ThreadCondition::wait( ThreadMutex& rThreadMutex, int nMiniSecond /*= -1*/ )
{
    if(mHandle == NULL)
    {
        return false;
    }
#ifdef WIN32
    DWORD dwTimeout = 0;
    if(nMiniSecond < 0)
    {
        dwTimeout = INFINITE;
    }
    else
    {
        dwTimeout = nMiniSecond;
    }

    //windows如果外面加了锁需要先释放，在该函数退出后再获取
    rThreadMutex.release();

    DWORD nRet = ::WaitForSingleObject(mHandle,dwTimeout);
    bool bReturn = false;
    if(nRet == WAIT_OBJECT_0)
    {
        bReturn = true;
    }
    else if(nRet == WAIT_TIMEOUT)
    {
        bReturn = false;
    }
    else
    {
        bReturn = false;
    }

    rThreadMutex.acquire();
	return bReturn;
#elif defined(__linux__)
	return false;
#endif
    
}
