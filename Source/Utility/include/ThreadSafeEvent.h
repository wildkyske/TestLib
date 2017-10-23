#pragma once
#ifndef ThreadSafeEvent_h__
#define ThreadSafeEvent_h__

#include "ThreadMutex.h"
#include "ThreadCondition.h"

// @Brief Condition必须配合Mutex使用 [6/7/2015 kyske]
class UTILITY_EXPORT ThreadSafeEvent
{
public:
	ThreadSafeEvent();
	~ThreadSafeEvent();

	/*
		Method:    	signal [Access:public ]
		Brief:    	发起信号
		Returns:   	bool
		Date:		2013/03/17 - Author:LiKuan
	*/
	bool signal();

	/*
		Method:    	reset [Access:public ]
		Brief:    	重置
		Returns:   	bool
		Date:		2013/03/17 - Author:LiKuan
	*/
	bool reset();

    bool wait(int nMiniSecond = -1);

    bool acquire();

    bool release();

protected:
	ThreadCondition mCondition;
    ThreadMutex mLock;
};

#endif // ThreadSafeEvent_h__


