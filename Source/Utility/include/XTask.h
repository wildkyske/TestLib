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
        @. �ָ��߳�
    */
    bool active();

    /*
        @. �����߳�
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
        @. ��д�ú���.��дʱ,���Ҫ�����ͻ���ģʽ,����û���ú���
    */
    virtual void onRunTask();
protected:
    static void callbackThreadFunc(void* pThis);
protected:
    //�߳̾��
    HANDLE mThread;

    //�߳�ID
    unsigned long mThreadID;

    //�߳�״̬
    int mThreadStatus;

    XTaskUser* mUserPtr;
};

#endif
