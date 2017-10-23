#ifndef AutoRegisterObjectManager_h__
#define AutoRegisterObjectManager_h__

#include "AutoRegisterObject.h"
#include <set>

class AutoRegisterObjectManager;
/*
	ClassName:	AutoRegisterObserver
	Brief:		�Զ�ע��۲���
	Author:		kyske
	Date:		2014/01/16
*/
class UTILITY_EXPORT AutoRegisterObserver
{
public:
    AutoRegisterObserver();

    virtual ~AutoRegisterObserver();

    virtual bool onBeforeObjectRegister(AutoRegisterObjectManager* pAutoRegObjMgr, AutoRegisterObject* pObj) = 0;

    virtual bool onAfterObjectRegister(AutoRegisterObjectManager* pAutoRegObjMgr, AutoRegisterObject* pObj) = 0;

    virtual bool onObjectRemove(AutoRegisterObjectManager* pAutoRegObjMgr, AutoRegisterObject* pObj) = 0;
};

/*
	ClassName:	AutoRegisterObjectManager
	Brief:		�Զ�ע����������
	Author:		kyske
	Date:		2014/01/15
*/
class UTILITY_EXPORT AutoRegisterObjectManager
{
public:
    AutoRegisterObjectManager();
    virtual ~AutoRegisterObjectManager();

    // @Brief ����һ������ [1/15/2014 kyske]
    bool insertObject(AutoRegisterObject* pObj);

    // @Brief �Ƴ�һ������ [1/15/2014 kyske]
    bool removeObject(AutoRegisterObject* pObj);

public: //�۲���
    bool registerObserve(AutoRegisterObserver* ob);

    bool unregisterObserver(AutoRegisterObserver* ob);

    void notifyBeforeObjectRegister(AutoRegisterObject* pObj);

    void notifyAfterObjectRegister(AutoRegisterObject* pObj);

    void notifyObjectRemove(AutoRegisterObject* pObj);
protected:
    std::set<AutoRegisterObject*> mAroContainer;

    std::set<AutoRegisterObserver*> mAroObservers;

};

#endif // AutoRegisterObjectManager_h__