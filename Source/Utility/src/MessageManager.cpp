#include "../include/MessageManager.h"
#include <limits>
#include "../include/MessageDealer.h"
#include "../include/Guard.h"

int MessageManager::dispatchMessage(double delayed, 
                                    MessageDealer* sender, 
                                    MessageDealer* receiver, 
                                    int msg, 
                                    void* extraInfo)
{
    GUARD(ThreadMutex, mQueueLock);

    if ( NULL == receiver)
    {
        return EMM_DEALER_NULL;
    }

    Telegram telegram(sender, receiver, msg, delayed, extraInfo);
    if (delayed <= 0.0)
    {
        dischargeMessage(receiver, telegram);
    }else
    {
        mPriorityQ.insert(telegram);
    }

    return MM_OK;
}

int MessageManager::dispatchMessage( double delayed, const Telegram& telegram )
{
    GUARD(ThreadMutex, mQueueLock);

    if (NULL == telegram.receiver)
    {
        return EMM_DEALER_NULL;
    }

    if (delayed <= 0.0)
    {
        dischargeMessage(telegram.receiver, telegram);
    }else
    {
        mPriorityQ.insert(telegram);
    }

    return MM_OK;
}

int MessageManager::dispatchMessageSync( const Telegram& telegram )
{
    GUARD(ThreadMutex, mQueueLock);

    if (NULL == telegram.receiver)
    {
        return EMM_DEALER_NULL;
    }

    mPriorityQ.insert(telegram);

    return MM_OK;
}

void MessageManager::processMessage(double nElapsedTime)
{
    GUARD(ThreadMutex, mQueueLock);

    for (std::set<Telegram>::iterator it = mPriorityQ.begin(); 
        it != mPriorityQ.end(); )
    {
		Telegram* pTelegram = (Telegram*)&(*it);
		pTelegram->dispatchTime -= nElapsedTime;
        if ((*it).dispatchTime < std::numeric_limits<double>::epsilon())
        {
            dischargeMessage((*it).receiver, *it);
            mPriorityQ.erase(it++);
        }else
        {
            ++it;
        }
    }

}

void MessageManager::dischargeMessage(MessageDealer* pReceiver, const Telegram& tel)
{
    if (pReceiver)
    {
        pReceiver->handleMessage(tel);
    }
}

