#include "../include/ReflectObject_Implement.h"
#include "../include/ReflectObject.h"

bool RepInstance_Implement::insert( const std::string& className, RepInstance* repInstace )
{
    ClassMapIter it = mClassMap.find(className);
    if (it != mClassMap.end())
    {
        return false;//已经存在
    }

    mClassMap.insert(std::make_pair(className, repInstace));

    notifyTypeRegiste(className);

    return true;
}

RepInstance* RepInstance_Implement::find( const std::string& className )
{
    ClassMapIter it = mClassMap.find(className);
    if (it == mClassMap.end())
    {
        return NULL;
    }
    return it->second;
}

RepInstance* RepInstance_Implement::remove( const std::string& className )
{
    ClassMapIter it = mClassMap.find(className);
    if (it == mClassMap.end())
    {
        return NULL;//不存在
    }

    notifyTypeUnregiste(className);

    RepInstance* repInst = it->second;

    mClassMap.erase(it);

    return repInst;
}

bool RepInstance_Implement::remove( RepInstance* repInstance )
{
    bool bOk = false;
    for (ClassMapIter it = mClassMap.begin();
        it != mClassMap.end(); )
    {
        RepInstance* tempRepInst = it->second;
        if (NULL == tempRepInst)
        {
            ++it;
            continue;
        }

        if (tempRepInst == repInstance)
        {
            notifyTypeUnregiste(tempRepInst->getClassName());

            mClassMap.erase(it++);
            bOk = true;
        }
        else
        {
            ++it;
        }
    }

    return bOk;
}

bool RepInstance_Implement::registeObserver( ReflectTypeRegisterObserver* ob )
{
    if (NULL == ob)
    {
        return false;
    }

    mTypeObs.insert(ob);

    return true;
}

bool RepInstance_Implement::unregisteObserver( ReflectTypeRegisterObserver* ob )
{
    if (NULL == ob)
    {
        return false;
    }

    mTypeObs.erase(ob);

    return true;
}

bool RepInstance_Implement::notifyTypeRegiste( const std::string& className )
{
    for (std::set<ReflectTypeRegisterObserver*>::iterator it = mTypeObs.begin(); 
        it != mTypeObs.end(); ++it)
    {
        ReflectTypeRegisterObserver* ob = *it;
        if (NULL == ob)
        {
            continue;
        }

        ob->onReflectTypeRegister(className);
    }

    return true;
}

bool RepInstance_Implement::notifyTypeUnregiste( const std::string& className )
{
    for (std::set<ReflectTypeRegisterObserver*>::iterator it = mTypeObs.begin(); 
        it != mTypeObs.end(); ++it)
    {
        ReflectTypeRegisterObserver* ob = *it;
        if (NULL == ob)
        {
            continue;
        }

        ob->onReflectTypeUnregister(className);
    }

    return true;
}

