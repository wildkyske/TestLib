#pragma  once
#ifndef MESSAGE_MANAGER_H
#define MESSAGE_MANAGER_H

#include "Telegram.h"
#include "Singleton.h"
#include <set>
#include "UtilityExport.h"
#include "ThreadMutex.h"

class MessageDealer;

enum
{
    EMM_DEALER_NULL = -1,
};

enum
{
    MM_OK = 1,
};

template class UTILITY_EXPORT std::set<Telegram>;

class UTILITY_EXPORT MessageManager : public Singleton<MessageManager>
{
public:
    /*
    * 发送消息
    */
    int dispatchMessage(double delayed, MessageDealer* sender, MessageDealer* receiver, int msg, void* extraInfo);

    //发送电报
    int dispatchMessage(double delayed, const Telegram& telegram);

    //发送异步电报
    int dispatchMessageSync(const Telegram& telegram);

    /*
    * 处理消息
    */
    void dischargeMessage(MessageDealer* pReceiver, const Telegram& tel);

    /*
    * 处理延时消息 [update]
    */
    void processMessage(double nElapsedTime);
    
protected:
    ThreadMutex mQueueLock;
    std::set<Telegram> mPriorityQ;
};

#define MsgMgr MessageManager::getInstancePtr() 

#endif
