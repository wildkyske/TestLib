#pragma once
#ifndef XTASK_H
#define XTASK_H

#include "UtilityExport.h"

class XTask;
class UTILITY_EXPORT XTaskUser
{
public:
	virtual ~XTaskUser(){}
	virtual void onRunTask(XTask* pTask){};
};

#ifdef WIN32
#include <windows.h>
#elif defined(__linux__)
typedef void* HANDLE;
#endif

class UTILITY_EXPORT XTask
{
public:
    enum{
        TASK_STATUS_STOP = 0,
        TASK_STATUS_RUNNING,
        TASK_STATUS_SUSPEND,
    };
public:
    XTask(void);
    virtual ~XTask(void);

    /*
        @. 恢复线程
    */
    bool active();

    /*
        @. 挂起线程
    */
    void suspend();

    /**/
    void resume();

    void join(int nTimeOutMillisecond = -1);

    void stop();

    /*kill*/
    void kill();

    int taskStatus() const;

    void attachUser(XTaskUser* pUser);
protected:
    /*
        @. 重写该函数.重写时,如果要保留客户端模式,请调用基类该函数
    */
    virtual void onRunTask();
protected:
    static void callbackThreadFunc(void* pThis);
protected:
    //线程句柄
    HANDLE mThread;

    //线程ID
    unsigned long mThreadID;

    //线程状态
    int mThreadStatus;

    XTaskUser* mUserPtr;
};

#endif
