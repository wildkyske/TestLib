#include "../include/IxComponentManager.h"
#include "../include/Guard.h"

IxComponentManager::IxComponentManager()
{

}

IxComponentManager::~IxComponentManager()
{

}

IxComponent* IxComponentManager::lookupComponent(const std::string& strComName)
{
	GUARD(ThreadMutex, mComponentSetLock);

	IxComponent* pComponent = NULL;

	std::map<const std::string, IxComponent*>::iterator it = mComponentSet.find(strComName);
	if (it == mComponentSet.end())
	{
		return pComponent;
	}

	pComponent = it->second;

	return pComponent;
}

IxComponent* IxComponentManager::lookupComponent(int nID)
{
	GUARD(ThreadMutex, mComponentSetLock);

	IxComponent* pComponent = NULL;

	for (std::map<const std::string, IxComponent*>::iterator it = mComponentSet.begin(); 
		it != mComponentSet.end(); ++it)
	{
		IxComponent* pItorComponent = it->second;
		if (pItorComponent == NULL)
		{
			continue;
		}

		if (pItorComponent->id() == nID)
		{
			pComponent = pItorComponent;
			break;
		}
	}
	return pComponent;
}

bool IxComponentManager::insertComponent(const std::string& strComponentName, IxComponent* pComponent)
{
	if (NULL == pComponent)
	{
		return false;
	}
	GUARD(ThreadMutex, mComponentSetLock);
	//如果已经存在,返回失败
	std::pair<std::map<const std::string, IxComponent*>::iterator, bool> ret = mComponentSet.insert(std::make_pair(strComponentName, pComponent));

	return ret.second;
}

bool IxComponentManager::removeComponent(const std::string& strComponentName)
{
	GUARD(ThreadMutex, mComponentSetLock);
	std::map<const std::string, IxComponent*>::iterator it = mComponentSet.find(strComponentName);
	if (it == mComponentSet.end())
	{
		return false;
	}

	mComponentSet.erase(it);

	return true;
}

bool IxComponentManager::removeComponent(IxComponent* pComponent)
{
	if (NULL == pComponent)
	{
		return false;
	}
	GUARD(ThreadMutex, mComponentSetLock);

	std::map<const std::string, IxComponent*>::iterator it = mComponentSet.begin();
	for (; it != mComponentSet.end(); ++it)
	{
		IxComponent* pTheComponent = it->second;
		if (NULL == pTheComponent)
		{
			continue;
		}

		if (pComponent == pTheComponent)
		{
			break;
		}
	}

	if (it != mComponentSet.end())
	{
		mComponentSet.erase(it);
	}
	return true;
}

bool IxComponentManager::removeComponent(int nID)
{
	GUARD(ThreadMutex, mComponentSetLock);

	std::map<const std::string, IxComponent*>::iterator it = mComponentSet.begin();
	for (; it != mComponentSet.end(); ++it)
	{
		IxComponent* pTheComponent = it->second;
		if (NULL == pTheComponent)
		{
			continue;
		}

		if (nID == pTheComponent->id())
		{
			break;
		}
	}

	if (it != mComponentSet.end())
	{
		mComponentSet.erase(it);
	}
	return true;
}

void IxComponentManager::cleanup()
{
	GUARD(ThreadMutex, mComponentSetLock);
	std::map<const std::string, IxComponent*>::iterator it = mComponentSet.begin();
	for (; it != mComponentSet.end(); ++it)
	{
		IxComponent* pTheComponent = it->second;
		if (NULL == pTheComponent)
		{
			continue;
		}

		//TODO:?
	}
	mComponentSet.clear();
}

int IxComponentManager::id()
{
	return 0x01;
}

std::string IxComponentManager::name()
{
	return "IxComponentManager";
}

IMPLEMENT_SINGLETON_CLASS(IxComponentManagerInstance)

// 实现组件搜索功能 [3/6/2016 Administrator]
IxComponent* searchComponent(const std::string& strComponentName)
{
	IxComponent* pComponent = NULL;
	IxComponentManager* pComponentManager = IxComponentManagerInstance::getInstancePtr();
	if (pComponentManager == NULL)
	{
		return NULL;
	}
	
	pComponent = pComponentManager->lookupComponent(strComponentName);

	return pComponent;
}

IxComponent* searchComponent(int nID)
{
	IxComponent* pComponent = NULL;
	IxComponentManager* pComponentManager = IxComponentManagerInstance::getInstancePtr();
	if (NULL == pComponentManager)
	{
		return NULL;
	}

	pComponent = pComponentManager->lookupComponent(nID);

	return pComponent;
}
