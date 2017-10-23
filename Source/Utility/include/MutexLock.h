#pragma once
#ifndef MUTEXLOCK_H
#define MUTEXLOCK_H
/*
	filename	: 	MutexLock.h
	created		:	2013/03/17  14:04
	author		:	LiKuan
	desc		:	
	note		:	
	copyright @ xcahr studio. e-mail:530754393@qq.com
*/

#include "UtilityExport.h"
#include "base_constant.h"
#include "Guard.h"

//WIN_32 支持
#ifdef WIN32
#include <Windows.h>
typedef CRITICAL_SECTION MutexHandle;
#else
typedef void* MutexHandle;
#endif

/*
	ClassName:	MutexLock
	Brief:		互斥锁, 使用临界区实现
	Author:		LiKuan
	Date:		2013/03/17
*/
class UTILITY_EXPORT MutexLock
{
public:
	MutexLock();
	~MutexLock();

	/*
		Method:    	acquire [Access:public ]
		Brief:    	上锁
		Returns:   	bool
		Date:		2013/03/17 - Author:LiKuan
	*/
	bool acquire();

	/*
		Method:    	release [Access:public ]
		Brief:    	释放锁
		Returns:   	bool
		Date:		2013/03/17 - Author:LiKuan
	*/
	bool release();

protected:
	MutexHandle mHandle;
};

#define MUTEX_GUARD(lock) GuardT<MutexLock>((MutexLock*)&lock)

#endif 
