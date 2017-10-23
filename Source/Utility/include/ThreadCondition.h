#pragma once
#ifndef ThreadCondition_h__
#define ThreadCondition_h__

#include "UtilityExport.h"

//WIN_32 ֧��
#ifdef WIN32
#include <Windows.h>
typedef void* ConditionHandle;
#elif defined(__linux__)
typedef void* ConditionHandle;
#endif

class ThreadMutex;
/*
	ClassName:	ThreadMutex
	Brief:		�߳�����ʹ��Eventʵ��
	Author:		LiKuan
	Date:		2013/03/17
*/
class UTILITY_EXPORT ThreadCondition
{
public:
    ThreadCondition();
    ~ThreadCondition();

    /*
    Method:    	signal [Access:public ]
    Brief:    	�����ź�
    Returns:   	bool
    Date:		2013/03/17 - Author:LiKuan
    */
    bool signal();

    /*
    Method:    	reset [Access:public ]
    Brief:    	����
    Returns:   	bool
    Date:		2013/03/17 - Author:LiKuan
    */
    bool reset();

    bool wait(int nMiniSecond = -1);

    bool wait(ThreadMutex& rThreadMutex, int nMiniSecond = -1);

protected:
    ConditionHandle mHandle;
};

#endif // ThreadCondition_h__

