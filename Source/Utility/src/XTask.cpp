#include "../include/XTask.h"
#include <string.h>

XTask::XTask(void) 
    : mThread(NULL)
    , mThreadID(-1)
    , mThreadStatus(TASK_STATUS_STOP)
    , mUserPtr(NULL)
{
    
}

XTask::~XTask(void)
{
    stop();
}

bool XTask::active()
{
    if (NULL != mThread)
    {
        return true;
    }
#ifdef WIN32
    mThread = CreateThread(
        0, 
        0, 
        (LPTHREAD_START_ROUTINE)(XTask::callbackThreadFunc),
        this, 
        0/*CREATE_SUSPENDED*/, //创建并挂起 
        &mThreadID);

    mThreadStatus = TASK_STATUS_RUNNING;
#elif defined(__linux__)

#endif

    return true;
}


void XTask::resume()
{
#ifdef WIN32
    if (NULL != mThread)
    {
        ResumeThread(mThread);
        mThreadStatus = TASK_STATUS_RUNNING;
	}
#elif defined(__linux__)

#endif
    
}


void XTask::suspend()
{
#ifdef WIN32
    if (NULL != mThread)
    {
        SuspendThread(mThread);
        mThreadStatus = TASK_STATUS_SUSPEND;
	}
#elif defined(__linux__)

#endif
}

void XTask::join(int nTimeOutMillisecond)
{
#ifdef WIN32
    if (NULL == mThread)
    {
        return;
    }
    int nWaitTime = nTimeOutMillisecond < 0 ? INFINITE : nTimeOutMillisecond;

    unsigned int dwRet = WaitForSingleObject(mThread, nWaitTime);

    if (dwRet == WAIT_OBJECT_0)
    {
        CloseHandle(mThread);
    }
    else if (dwRet == WAIT_TIMEOUT)
    {
        kill();
    }
#elif defined(__linux__)

#endif
}

void XTask::stop()
{
    mThreadStatus = TASK_STATUS_STOP;
}

void XTask::callbackThreadFunc( void* pThis )
{
    XTask* theObj = (XTask*)pThis;
    if (NULL == theObj)
    {
        return;
    }

    theObj->onRunTask();

    //线程结束，设置线程状态为停止
    theObj->mThreadStatus = XTask::TASK_STATUS_STOP;
}

int XTask::taskStatus() const
{
    return mThreadStatus;
}

void XTask::kill()
{
#ifdef WIN32
    if (NULL != mThread)
    {
        TerminateThread(mThread, -1);

        CloseHandle(mThread);

        mThread = NULL;
    }

    mThreadStatus = TASK_STATUS_STOP;
#elif defined(__linux__)

#endif
}

void XTask::onRunTask()
{
    if (NULL != mUserPtr)
    {
        mUserPtr->onRunTask(this);
    }
}

void XTask::attachUser( XTaskUser* pUser )
{
    mUserPtr = pUser;
}
