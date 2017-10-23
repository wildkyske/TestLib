#ifndef IxComponentManager_h__
#define IxComponentManager_h__

#include "IxComponent.h"
#include "Singleton.h"
#include <map>
#include "ThreadMutex.h"

// x系列组件管理器 [3/6/2016 Administrator]
class UTILITY_EXPORT IxComponentManager : public IxComponent
{
public:
	IxComponentManager();
	
	virtual ~IxComponentManager();

	int id();

	std::string name();

	bool insertComponent(const std::string& strComponentName, IxComponent* pComponent);

	bool removeComponent(const std::string& strComponentName);

	bool removeComponent(IxComponent* pComponent);

	bool removeComponent(int nID);

	void cleanup();

	IxComponent* lookupComponent(const std::string& strComName);

	IxComponent* lookupComponent(int nID);

protected:
	ThreadMutex mComponentSetLock;
	std::map<const std::string, IxComponent*> mComponentSet;
};

// 为了方便该类使用单件,作为程序的切入点 [3/6/2016 Administrator]
DECLARE_SINGLETON_CLASS(IxComponentManagerInstance, IxComponentManager, UTILITY_EXPORT)

#endif // IxComponentManager_h__

