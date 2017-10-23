#include "../include/Telegram.h"
#include "../include/MessageDealer.h"
#include <memory.h>

Telegram::Telegram() 
    : sender(NULL)
    , receiver(NULL)
    , msg(INVALID_MSG)
    , dispatchTime(0.0)
    , extra(NULL)
    , extra_ex(NULL)
    , group(NO_GROUP)
{
    memset(buf, 0, TEL_BUF_LEN + 1);
}

Telegram::Telegram( MessageDealer* s, 
                   MessageDealer* r, 
                   int m, double tim, 
                   void* exInfo, void* exInfo2,
                   char* pBuf, int grp ) 
                   : sender(s)
                   , receiver(r)
                   , msg(m)
                   , dispatchTime(tim)
                   , extra(exInfo)
                   , extra_ex(exInfo2)
                   , group(grp)
{
    if (NULL != pBuf)
    {
        memcpy(buf, pBuf, TEL_BUF_LEN);
        buf[TEL_BUF_LEN] = 0;
    }
    else
    {
        memset(buf, 0, TEL_BUF_LEN + 1);
    }
}

Telegram::Telegram( const Telegram& rhs )
{
    sender = rhs.sender;
    receiver = rhs.receiver;
    msg = rhs.msg;
    dispatchTime = rhs.dispatchTime;
    group = rhs.group;
    extra = rhs.extra;
    extra_ex = rhs.extra_ex;

    memcpy(buf, rhs.buf, TEL_BUF_LEN);
}

Telegram& Telegram::operator=( const Telegram& rhs )
{
    sender = rhs.sender;
    receiver = rhs.receiver;
    msg = rhs.msg;
    dispatchTime = rhs.dispatchTime;
    group = rhs.group;
    extra = rhs.extra;
    extra_ex = rhs.extra_ex;

    memcpy(buf, rhs.buf, TEL_BUF_LEN);

    return *this;
}

tstring Telegram::toString() const
{
    tsstream ss;
    ss<<_TX("sender:")<<(long)sender<<_TX(" recv:")
        <<(long)receiver<<_TX(" msg:")
        <<msg<<_TX(" group:")
        <<group<<_TX(" send time:")
        <<dispatchTime<<_TX(" extra info:")
        <<(long)extra<<_TX(" extra info ex:")
        <<(long)extra_ex<<_TX(" ");
    return ss.str();
}

