#ifndef AutoRegisterObjectManager_h__
#define AutoRegisterObjectManager_h__

#include "AutoRegisterObject.h"
#include <set>

class AutoRegisterObjectManager;
/*
	ClassName:	AutoRegisterObserver
	Brief:		自动注册观察器
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
	Brief:		自动注册对象管理器
	Author:		kyske
	Date:		2014/01/15
*/
class UTILITY_EXPORT AutoRegisterObjectManager
{
public:
    AutoRegisterObjectManager();
    virtual ~AutoRegisterObjectManager();

    // @Brief 加入一个对象 [1/15/2014 kyske]
    bool insertObject(AutoRegisterObject* pObj);

    // @Brief 移除一个对象 [1/15/2014 kyske]
    bool removeObject(AutoRegisterObject* pObj);

public: //观察者
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