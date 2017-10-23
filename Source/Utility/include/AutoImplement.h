#pragma once
#ifndef AUTO_IMPLEMENT_H
#define AUTO_IMPLEMENT_H

#include "typedefs.h"
//
#define DECLARE_AUTO_IMPLEMENT() \
class AutoInsert;\
class Wrapper\
    {\
    protected:\
    static AutoInsert* __auto_insert;\
    };

//
#define BEGIN_AUTO_IMPLEMENT() \
class AutoInsert\
{\
public:\
    AutoInsert()\
    {

//
#define END_AUTO_IMPLEMENT() \
    }\
};\
AutoInsert* Wrapper::__auto_insert = new AutoInsert;

class AutoRegisterInfo
{
public:
    virtual void autoRegister(const tstring& key) = 0;
};
//解决重定义问题

#endif
