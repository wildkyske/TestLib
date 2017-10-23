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
    * ������Ϣ
    */
    int dispatchMessage(double delayed, MessageDealer* sender, MessageDealer* receiver, int msg, void* extraInfo);

    //���͵籨
    int dispatchMessage(double delayed, const Telegram& telegram);

    //�����첽�籨
    int dispatchMessageSync(const Telegram& telegram);

    /*
    * ������Ϣ
    */
    void dischargeMessage(MessageDealer* pReceiver, const Telegram& tel);

    /*
    * ������ʱ��Ϣ [update]
    */
    void processMessage(double nElapsedTime);
    
protected:
    ThreadMutex mQueueLock;
    std::set<Telegram> mPriorityQ;
};

#define MsgMgr MessageManager::getInstancePtr() 

#endif
