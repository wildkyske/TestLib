#include "../include/MessageDealer.h"
#include "../include/MessageManager.h"
//#include "LogSystem.h"
#include "../include/MessageIDGenerator.h"

MessageDealer::MessageDealer()
{
    mID = MessageIDGenerator::makeID();
}

MessageDealer::~MessageDealer()
{

}

void MessageDealer::sendMessage( MessageDealer* other, int msg, void* extra, double nDealyTime /*= 0.0*/ )
{
    MsgMgr->dispatchMessage(nDealyTime, this, other, msg, extra);
}

void MessageDealer::sendMessage( const Telegram& telegram)
{
    MsgMgr->dispatchMessage(0, telegram);
}

void MessageDealer::postMessage( const Telegram& telegram )
{
    MsgMgr->dispatchMessageSync(telegram);
}

int MessageDealer::id() const
{
    return mID;
}
