#include "../include/CloneObject.h"

CCloneObject::CCloneObject(void) 
{
}

CCloneObject::~CCloneObject(void)
{
}

CCloneObject* CCloneObject::clone()
{
    CCloneObject* pClone = _clone();
    if (NULL == pClone)
    {
        return NULL;
    }
    pClone->mIsClone = true;
    return pClone;
}

void CCloneObject::destroy()
{
    if (!mIsClone)
    {
        return;
    }

    _destroy();
}

//====!

CCloneManager::CCloneManager() : impl(NULL)
{
    impl = new KeyPointerManager<const tstring, CCloneObject>();
}

CCloneManager::~CCloneManager()
{
    if (impl)
    {
        delete impl;
        impl = NULL;
    }
}

CCloneManager* CCloneManager::getInstancePtr()
{
    static CCloneManager _instance;
    return &_instance;
}

CCloneObject* CCloneManager::getObject( const tstring& key )
{
    return impl->getObject(key);
}

bool CCloneManager::insertObject( const tstring& key, CCloneObject* obj )
{
    return impl->insertObject(key, obj);
}

