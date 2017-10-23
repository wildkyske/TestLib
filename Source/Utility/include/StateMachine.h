#pragma once
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "State.h"

//--------------------------------------------------------
// name : StateMachine   type : template-class
// base class : 
// describe : State Alternate Driver.
//--------------------------------------------------------
template <typename T>
class StateMachine
{
public:
    StateMachine(T* owner) : mOwner(owner), 
        mCurrentState(NULL), mGlobalState(NULL), mPreviousState(NULL)
    {}
    ~StateMachine(){}

    void update() const;
    bool handleMessage(const Telegram& tel);
    void changeState(State<T>* newState);
    void reverseToPrevState();

    // 设置当前状态 [3/20/2014 Administrator]
    void setCurrentState(State<T>* s) 
    {
        if (NULL != mCurrentState)
        {
            delete mCurrentState;
            mCurrentState = NULL;
        }
        mCurrentState = s;
    }

    // 设置全局状态 [3/20/2014 Administrator]
    void setGlobalState(State<T>* s) 
    {
        if (NULL != mGlobalState)
        {
            delete mGlobalState;
            mGlobalState = NULL;
        }
        mGlobalState = s;
    }

    State<T>* getCurrentState() const 
    {
        return mCurrentState;
    }

    State<T>* getPreviousState() const 
    {
        return mPreviousState;
    }

    State<T>* getGlobalState() const 
    {
        return mGlobalState;
    }

    void setOwner(T* pOwner) 
    {
        mOwner = pOwner;
    }
protected:
    T* mOwner;
    State<T>* mCurrentState;
    State<T>* mPreviousState;
    State<T>* mGlobalState;
};

//-------------StateMachine<T>::handleMessage()--------
// @. state machine handle message.
//
//--------------------------------------------------------
template <typename T>
bool StateMachine<T>::handleMessage( const Telegram& tel )
{
     if (mCurrentState && mCurrentState->onMessage(mOwner, tel))
     {
         return true;
     }

     if (mGlobalState && mGlobalState->onMessage(mOwner, tel))
     {
         return true;
     }

     return false;
}
//-------------StateMachine<T>::update()------------------
// @. state machine update current state && global state.
//
//--------------------------------------------------------
template <typename T>
void StateMachine<T>::update() const
{
    /* execute current state. */
    if (NULL != mCurrentState) 
    { 
        mCurrentState->execute(mOwner); 
    }
    
    /* execute global state. */
    if (NULL != mGlobalState) 
    { 
        mGlobalState->execute(mOwner); 
    }
}

//-------------StateMachine<T>::changeState()--------------
// @. change current state to new state.
//
//---------------------------------------------------------
template <typename T>
void StateMachine<T>::changeState(State<T> *newState)
{
    /* assert (new state). */
    if (NULL == newState)
    {
        return ;
    }

    /* leave current state. */
    if (NULL != mCurrentState)
    {
        mCurrentState->exit(mOwner);
    }

    if (NULL != mPreviousState)
    {
        delete mPreviousState;
        mPreviousState = NULL;
    }

    /* set previous state. */
    mPreviousState = mCurrentState;

    /* enter new state. */
    mCurrentState = newState;
    mCurrentState->entry(mOwner);
}

//-----------------StateMachine<T>::reverseToPrevState()-----
// @. change state from 'mCurrentState' to 'mPreviousState'.
//
//-----------------------------------------------------------
template <typename T>
void StateMachine<T>::reverseToPrevState()
{
    changeState(mPreviousState);
}
#endif
