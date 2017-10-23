#include "../include/IxObjectManager.h"
#include "../include/Guard.h"
#include "../include/IxObject.h"

IxObjectManager::IxObjectManager()
{

}

IxObjectManager::~IxObjectManager()
{

}

IxObject* IxObjectManager::createManagedObject(const std::string& strTypeName )
{
	int nNewID = generateUniqueID();
    GUARD(ThreadMutex, m_ManagedObjectsLock);
    std::map<int, IxObject*>::iterator it = m_ManagedObjects.find(nNewID);
    if (it != m_ManagedObjects.end())
    {
        //已经存在,返回失败
        return NULL;
    }

    IxObject* pNewObject = createObject(strTypeName);
    if (NULL == pNewObject)
    {
        return NULL;
    }
	pNewObject->setID(nNewID);

	//存储
	m_ManagedObjects.insert(std::make_pair(nNewID, pNewObject));
    
    return pNewObject;
}

void IxObjectManager::destroyManagedObject( int nID )
{
	GUARD(ThreadMutex, m_ManagedObjectsLock);
	std::map<int, IxObject*>::iterator it = m_ManagedObjects.find(nID);
	if (it == m_ManagedObjects.end())
	{
		return ;
	}

	IxObject* pObject = it->second;
	m_ManagedObjects.erase(it);
	delete pObject;
}

void IxObjectManager::destroyManagedObject( IxObject* pObject )
{
    if (NULL == pObject)
    {
        return;
    }

    GUARD(ThreadMutex, m_ManagedObjectsLock);
    std::map<int, IxObject*>::iterator it = m_ManagedObjects.begin();
    for (;it != m_ManagedObjects.end(); ++it)
    {
        IxObject* pMgrObject = it->second;
        if (NULL == pMgrObject)
        {
            continue;
        }

        if (pObject == pMgrObject)
        {
            break;
        }
    }

	if (it == m_ManagedObjects.end())
	{
		return;
	}

	m_ManagedObjects.erase(it);
    delete pObject;
}

IxObject* IxObjectManager::lookupManagedObject(int nID)
{
	GUARD(ThreadMutex, m_ManagedObjectsLock);
	std::map<int, IxObject*>::iterator it = m_ManagedObjects.find(nID);
	if (it == m_ManagedObjects.end())
	{
		return NULL;
	}

	return it->second;
}
