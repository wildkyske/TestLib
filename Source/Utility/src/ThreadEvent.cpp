#include "../include/ThreadEvent.h"

ThreadEvent::ThreadEvent() : mHandle(NULL)
{
#ifdef WIN32
	mHandle = ::CreateEvent(NULL, false, false, NULL);
#elif defined(__linux__)
	
#endif
}

ThreadEvent::~ThreadEvent()
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

bool ThreadEvent::signal()
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

bool ThreadEvent::reset()
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

bool ThreadEvent::wait( int nMiniSecond /*= -1*/ )
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
