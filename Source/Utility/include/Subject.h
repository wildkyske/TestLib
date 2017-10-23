#pragma once
#ifndef SUBJECT_H
#define SUBJECT_H

#include <list>
#include <algorithm>
#include "typedefs.h"

//======================================================
//====����һ : ģ�巽ʽ

template <typename T>
class Subject
{
public:
    Subject()
    {

    }

    virtual ~Subject()
    {

    }

    void registerOb(T* o)
    {
        typename std::list<T*>::iterator it = std::find(mObserveres.begin(), mObserveres.end(), o);
        if (it != mObserveres.end())
        {
            return;
        }
        mObserveres.push_back(o);
    }

    void unregisterOb(T* o)
    {
        typename std::list<T*>::iterator it = std::find(mObserveres.begin(), mObserveres.end(), o);
        if (it == mObserveres.end())
        {
            return;
        }
        mObserveres.erase(it);
    }

    void clear()
    {
        mObserveres.clear();
    }

    /*
        @. һ�������Ĺ۲��� 
    */
    template <typename ReturnT, typename ArgT>
    void notify(ReturnT (T::*pfn)(ArgT), typename arg_type_traits<ArgT>::type arg1)
    {
        for (typename std::list<T*>::iterator it = mObserveres.begin();
            it != mObserveres.end(); ++it)
        {
            ((*it)->*pfn)(arg1);
        }
    }

    /*
        @. ���������Ĺ۲���
    */
    template <typename ReturnT, typename Arg1T, typename Arg2T>
    void notify(ReturnT (T::*pfn)(Arg1T, Arg2T), 
        typename arg_type_traits<Arg1T>::type arg1, 
        typename arg_type_traits<Arg2T>::type arg2)
    {
        for(typename std::list<T*>::iterator it = mObserveres.begin();
            it != mObserveres.end(); ++it)
        {
            ((*it)->*pfn)(arg1, arg2);
        }
    }
    
protected:
    std::list<T*> mObserveres;
};

//=======================================================================
//====������:�귽ʽ
#include <set>

#define DECLARE_SUBJECT(obClassName, ext) public:\
    void registerObserver(obClassName* ob);\
    void unregisterObserver(obClassName* ob);\
    protected:\
    std::set<obClassName*> mObserver##ext;

#define IMPLEMENT_SUBJECT(className, obClassName, ext) \
    void className::registerObserver(obClassName* ob){\
    if(NULL == ob) {return;}\
    mObserver##ext.insert(ob);}\
    void className::unregisterObserver(obClassName* ob){\
    if(NULL == ob) {return;}\
    mObserver##ext.erase(ob);}

#endif
