#pragma once
#ifndef X_LOOP_TASK_H
#define X_LOOP_TASK_H

#include "XTask.h"

class UTILITY_EXPORT XLoopTask :
    public XTask
{
public:
    XLoopTask(void);
    virtual ~XLoopTask(void);

protected:
    void onRunTask();

    //可重写该接口,也可不重写,使用user通知
    virtual void onRunLoopTask();
};

#endif
