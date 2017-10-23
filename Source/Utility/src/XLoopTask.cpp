#include "../include/XLoopTask.h"
#include <string.h>

XLoopTask::XLoopTask(void)
{
}

XLoopTask::~XLoopTask(void)
{
}

void XLoopTask::onRunTask()
{
    for (;;)
    {
        if (TASK_STATUS_STOP == taskStatus())
        {
            break;
        }

        this->onRunLoopTask();
#ifdef WIN32
        Sleep(50);
#elif __linux__

#endif
    }
}

void XLoopTask::onRunLoopTask()
{
    if (NULL != mUserPtr)
    {
        mUserPtr->onRunTask(this);
    }
}
