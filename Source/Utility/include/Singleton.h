#pragma once
#ifndef SINGLETON_H
#define SINGLETON_H

#include <stdio.h>

template <typename T>
class Singleton
{
public:
    static T* getInstancePtr()
    {
        static T _instance;
        return &_instance;
    }
protected:
    Singleton(){}
    virtual ~Singleton(){}
};

#define DECLARE_SINGLETON(className) \
    static className* getInstancePtr();

#define IMPLEMENT_SINGLETON(className) \
    className* className::getInstancePtr() {\
        static className _instance; \
        return &_instance;}

#define DECLARE_SINGLETON_CLASS(className, baseClassName, exportSymbol) \
class exportSymbol className : public baseClassName \
{\
public:\
    className();\
    ~className();\
    static className* getInstancePtr();\
protected: \
    static className* mInstance; \
}; 

#define IMPLEMENT_SINGLETON_CLASS(className) \
    className* className::mInstance = NULL; \
    className::className(){}\
    className::~className(){if(NULL != mInstance){delete mInstance; mInstance = NULL;}}\
    className* className::getInstancePtr(){\
        if(NULL != mInstance){ return mInstance;}\
        mInstance = new className();\
        return mInstance;}

#endif
