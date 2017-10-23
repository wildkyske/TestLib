#pragma once
#ifndef STATE_H
#define STATE_H

#include "Telegram.h"

template <typename T>
class State
{
public :
    virtual void entry(T* excutor) = 0;
    virtual void execute(T* excutor) = 0;
    virtual void exit(T* excutor) = 0;
    virtual bool onMessage(T* excutor, const Telegram& tel) = 0;
    virtual ~State(){}
};

#endif
