#include "../include/ThreadSafeEvent.h"

ThreadSafeEvent::ThreadSafeEvent()
{
	
}

ThreadSafeEvent::~ThreadSafeEvent()
{
	
}

bool ThreadSafeEvent::signal()
{
	return mCondition.signal();
}

bool ThreadSafeEvent::reset()
{
	return mCondition.reset();
}

bool ThreadSafeEvent::wait( int nMiniSecond /*= -1*/ )
{
    return mCondition.wait(mLock, nMiniSecond);
}

bool ThreadSafeEvent::acquire()
{
    return mLock.acquire();
}

bool ThreadSafeEvent::release()
{
    return mLock.release();
}
