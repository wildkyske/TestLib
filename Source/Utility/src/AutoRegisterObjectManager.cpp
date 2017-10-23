#include "../include/AutoRegisterObjectManager.h"
#include <stdlib.h>

AutoRegisterObjectManager::AutoRegisterObjectManager()
{

}

AutoRegisterObjectManager::~AutoRegisterObjectManager()
{

}

bool AutoRegisterObjectManager::insertObject( AutoRegisterObject* pObj )
{
    notifyBeforeObjectRegister(pObj);

    mAroContainer.insert(pObj);

    notifyAfterObjectRegister(pObj);

    return true;
}

bool AutoRegisterObjectManager::removeObject( AutoRegisterObject* pObj )
{
    notifyObjectRemove(pObj);

    mAroContainer.erase(pObj);

    return true;
}

void AutoRegisterObjectManager::notifyBeforeObjectRegister( AutoRegisterObject* pObj )
{
    for (std::set<AutoRegisterObserver*>::iterator it = mAroObservers.begin(); 
        it != mAroObservers.end(); ++it)
    {
        AutoRegisterObserver* ob = (*it);
        if (NULL == ob)
        {
            continue;
        }

        ob->onBeforeObjectRegister(this, pObj);
    }
}

void AutoRegisterObjectManager::notifyAfterObjectRegister( AutoRegisterObject* pObj )
{
    for (std::set<AutoRegisterObserver*>::iterator it = mAroObservers.begin(); 
        it != mAroObservers.end(); ++it)
    {
        AutoRegisterObserver* ob = (*it);
        if (NULL == ob)
        {
            continue;
        }

        ob->onAfterObjectRegister(this, pObj);
    }
}

void AutoRegisterObjectManager::notifyObjectRemove( AutoRegisterObject* pObj )
{
    for (std::set<AutoRegisterObserver*>::iterator it = mAroObservers.begin(); 
        it != mAroObservers.end(); ++it)
    {
        AutoRegisterObserver* ob = (*it);
        if (NULL == ob)
        {
            continue;
        }

        ob->onObjectRemove(this, pObj);
    }
}

bool AutoRegisterObjectManager::registerObserve( AutoRegisterObserver* ob )
{
    mAroObservers.insert(ob);
    return true;
}

bool AutoRegisterObjectManager::unregisterObserver( AutoRegisterObserver* ob )
{
    mAroObservers.erase(ob);
    return true;
}

//==========================================π€≤Ï’ﬂ========================
AutoRegisterObserver::AutoRegisterObserver()
{
    
}

AutoRegisterObserver::~AutoRegisterObserver()
{
    
}
