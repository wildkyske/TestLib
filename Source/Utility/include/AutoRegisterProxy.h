#ifndef AutoRegisterProxy_h__
#define AutoRegisterProxy_h__

#include "AutoRegisterObjectManager.h"

/*
	ClassName:	AutoRegisterProxy
	Brief:		自动注册代理
	Author:		kyske
	Date:		2014/01/15
*/
template <typename T>
class AutoRegisterProxy
{
public:


    AutoRegisterProxy(AutoRegisterObjectManager* mgr) : mAroMgr(mgr)
    {
        mObjT = new T;
        mAro = mObjT;
        if (NULL != mAroMgr)
        {
            mAroMgr->insertObject(mAro);
        }
    }

    ~AutoRegisterProxy()
    {
        if (NULL != mAroMgr)
        {
            mAroMgr->removeObject(mAro);
        }

        if (NULL != mObjT)
        {
            delete mObjT;
            mObjT = NULL;
            mAro = NULL;
        }
    }

protected:
    AutoRegisterProxy()
    {
    }

protected:
    AutoRegisterObjectManager* mAroMgr;
    AutoRegisterObject* mAro;
    T* mObjT;
};

#define AUTO_REGISTE_OBJECT(className, mgr) \
    static AutoRegisterProxy<className> g_arp_##className(mgr);

#endif // AutoRegisterProxy_h__