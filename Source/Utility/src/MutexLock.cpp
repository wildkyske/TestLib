#include "../include/MutexLock.h"

MutexLock::MutexLock() 
{
#ifdef WIN32
	::InitializeCriticalSection(&mHandle);
#endif

}

MutexLock::~MutexLock()
{
#ifdef WIN32
	::DeleteCriticalSection(&mHandle);
#endif
}

bool MutexLock::acquire()
{
#ifdef WIN32
	::EnterCriticalSection(&mHandle);
#endif

	return true;
}

bool MutexLock::release()
{
#ifdef WIN32
	::LeaveCriticalSection(&mHandle);
#endif

	return true;
}
