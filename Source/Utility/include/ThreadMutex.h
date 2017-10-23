#pragma once
#ifndef THREADMUTEX_H
#define THREADMUTEX_H
/*
	filename	: 	ThreadMutex.h
	created		:	2013/03/17  14:23
	author		:	LiKuan
	desc		:	
	note		:	
	copyright @ xcahr studio. e-mail:530754393@qq.com
*/

#include "UtilityExport.h"
//#include "base_constant.h"

//WIN_32 支持
#ifdef WIN32
#include <Windows.h>
typedef CRITICAL_SECTION ThreadMutexHandle;
#elif defined(__linux__)
#include <sys/types.h>
#include <pthread.h>
typedef pthread_mutex_t ThreadMutexHandle;
#elif defined VXWORKS
#include "semLib.h"
typedef SEM_ID ThreadMutexHandle;
#endif

/*
	ClassName:	ThreadMutex
	Brief:		线程锁，使用Event实现
	Author:		LiKuan
	Date:		2013/03/17
*/
class UTILITY_EXPORT ThreadMutex
{
public:
	ThreadMutex();
	~ThreadMutex();

	/*
		Method:    	signal [Access:public ]
		Brief:    	发起信号
		Returns:   	bool
		Date:		2013/03/17 - Author:LiKuan
	*/
	bool acquire();

	/*
		Method:    	reset [Access:public ]
		Brief:    	重置
		Returns:   	bool
		Date:		2013/03/17 - Author:LiKuan
	*/
	bool release();
protected:
	ThreadMutexHandle mHandle;
};

#endif 
