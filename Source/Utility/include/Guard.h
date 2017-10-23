#pragma once
#ifndef GUARD_H
#define GUARD_H
/*
	filename	: 	Guard.h
	created		:	2013/03/17  14:43
	author		:	LiKuan
	desc		:	自动释放功能的锁保护
	note		:	
	copyright @ xcahr studio. e-mail:530754393@qq.com
*/

template <class T> 
class Guard
{
public:
	Guard(T* lock);
	~Guard();

protected:
    Guard():mLock(NULL){}
protected:
	T* mLock;
    bool mIsLocked;
};

template <class T>
Guard<T>::~Guard()
{
	if (NULL != mLock /*&& mIsLocked*/)
	{
		mLock->release();
       // mIsLocked = false;
	}
}

template <class T>
Guard<T>::Guard( T* lock ) 
    : mLock(lock)
    , mIsLocked(false)
{
	if (NULL != mLock)
	{
		if (mLock->acquire())
		{
            mIsLocked = true;
		}
	}
}

#define GUARD(type, lock) Guard<type> guard_##lock(&lock)
#endif 
