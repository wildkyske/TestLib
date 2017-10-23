#pragma once
#ifndef ThreadEvent_h__
#define ThreadEvent_h__


/*
	filename	: 	ThreadMutex.h
	created		:	2013/03/17  14:23
	author		:	LiKuan
	desc		:	
	note		:	
	copyright @ xcahr studio. e-mail:530754393@qq.com
*/

#include "UtilityExport.h"
#include "base_constant.h"

//WIN_32 支持
#ifdef WIN32
#include <Windows.h>
typedef void* ThreadEventHandle;
#elif defined(__linux__)
typedef void* ThreadEventHandle;
#endif

/*
	ClassName:	ThreadMutex
	Brief:		线程锁，使用Event实现
	Author:		LiKuan
	Date:		2013/03/17
*/
class UTILITY_EXPORT ThreadEvent
{
public:
	ThreadEvent();
	~ThreadEvent();

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

protected:
	ThreadEventHandle mHandle;
};

#endif // ThreadEvent_h__

