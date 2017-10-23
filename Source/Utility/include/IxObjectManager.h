#ifndef IxObjectManager_h__
#define IxObjectManager_h__

#include "IxObjectCreator.h"

class UTILITY_EXPORT IxObjectManager : public IxObjectCreator
{
public:
    IxObjectManager();
    virtual ~IxObjectManager();

    virtual IxObject* createManagedObject(const std::string& strTypeName);

    virtual void destroyManagedObject(IxObject* pObject);

	virtual void destroyManagedObject(int nID);

	IxObject* lookupManagedObject(int nID);

protected:
    ThreadMutex m_ManagedObjectsLock;
    std::map<int, IxObject*> m_ManagedObjects;
};
#endif // IxObjectManager_h__
