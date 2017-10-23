#include "../include/ThreadMutex.h"

ThreadMutex::ThreadMutex()
{
#ifdef WIN32
    ::InitializeCriticalSection(&mHandle);
#elif defined(__linux__)

#endif
}

ThreadMutex::~ThreadMutex()
{
#ifdef WIN32
    ::DeleteCriticalSection(&mHandle);
#elif defined(__linux__)

#endif
}

bool ThreadMutex::acquire()
{
#ifdef WIN32
    ::EnterCriticalSection(&mHandle);
#elif defined(__linux__)

#endif
	
	return true;
}

bool ThreadMutex::release()
{
#ifdef WIN32
    ::LeaveCriticalSection(&mHandle);
#elif defined(__linux__)

#endif

	return true;
}
