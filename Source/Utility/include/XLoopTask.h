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

    //����д�ýӿ�,Ҳ�ɲ���д,ʹ��user֪ͨ
    virtual void onRunLoopTask();
};

#endif
