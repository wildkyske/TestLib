#pragma once
#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <math.h>
#include <iostream>
#include "UtilityExport.h"
#include "typedefs.h"

class MessageDealer;

enum
{
    INVALID_MSG = -1,
    NO_GROUP = -1,
};

enum
{
    TEL_BUF_LEN = 255
};

class UTILITY_EXPORT Telegram 
{
public:
    MessageDealer* sender;      //消息发送者
    MessageDealer* receiver;    //消息接收者
    int msg;                    //消息代码
    int group;                  //消息组
    double dispatchTime;        //消息时间
    void* extra;                //附加消息
    void* extra_ex;             //额外的附加消息
    char buf[TEL_BUF_LEN + 1];  //数据缓冲区

public:

    Telegram(); 
    Telegram( MessageDealer* s, MessageDealer* r, int m, double tim, void* exInfo, void* exInfo2 = NULL, char* pBuf = NULL, int grp = NO_GROUP );
    //重载拷贝构造函数
    Telegram(const Telegram& rhs);

    //重载=号
    Telegram& operator=(const Telegram& rhs);

    tstring toString() const;
};

static const double SMALLEST_DELAY = 0.25;

inline bool operator==(const Telegram& t1, const Telegram& t2)
{
    return ( fabs(t1.dispatchTime-t2.dispatchTime) < SMALLEST_DELAY) &&
        (t1.sender == t2.sender)        &&
        (t1.receiver == t2.receiver)    &&
        (t1.group == t2.group)  &&
        (t1.msg == t2.msg);
}

inline bool operator<(const Telegram& t1, const Telegram& t2)
{
    if (t1 == t2)
    {
        return false;
    }
    else
    {
        return  (t1.dispatchTime < t2.dispatchTime);
    }
}

#endif
