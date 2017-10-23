#pragma once
#ifndef CLONE_OBJECT_H
#define CLONE_OBJECT_H

#include "UtilityExport.h"
#include "KeyPointerManager.h"

class CCloneObject;
/*
*@.brief ��¡�������[��¡������]
*/
class UTILITY_EXPORT CCloneManager 
{
public:
    static CCloneManager* getInstancePtr();

    CCloneObject* getObject(const tstring& key);

    bool insertObject(const tstring& key, CCloneObject* obj);

protected:
    CCloneManager();
    ~CCloneManager();
protected:
    KeyPointerManager<const tstring, CCloneObject>* impl;
};

/*
@.breif ��¡�壬����ͨ����������¡����ʱ���ṩ��¡�����
*/
class UTILITY_EXPORT CCloneObject
{
public:
    /*
    *@.class AutoInsertClone
    *@.brief �����Զ������¡��
    */
    template <typename CloneT>
    class AutoInsertClone
    {
    public:
        AutoInsertClone(const tstring& key)
        {
            CCloneManager::getInstancePtr()->insertObject(key, new CloneT);
        }
        ~AutoInsertClone(){}
    protected:
        AutoInsertClone(){}
    };

public:
    CCloneObject(void);
    virtual ~CCloneObject(void);

    CCloneObject* clone();

    void destroy();

    template <typename T> T* toType()
    {
        return dynamic_cast<T*>(this);
    }
protected:
    virtual CCloneObject* _clone() = 0;
    virtual void _destroy() = 0;
protected:
    bool mIsClone;
};

/*
*@.brief ������¡��
*/
#define DECLARE_CLONE_OBJECT(className) \
    protected: \
    virtual CCloneObject* _clone(); \
    virtual void _destroy(); \
    protected: \
    static CCloneObject::AutoInsertClone<className> mAutoInstance;

/*
*@.brief ʵ�ֿ�¡��
*/
#define IMPLEMENT_CLONE_OBJECT(className) \
    CCloneObject* className::_clone() \
    { \
        return new className; \
    } \
    void className::_destroy() \
    { \
        delete this; \
    } \
    CCloneObject::AutoInsertClone<className> className::mAutoInstance = CCloneObject::AutoInsertClone<className>(_TX(#className));

/*
*@.brief ������¡��
*/
#define CLONE(className) CCloneManager::getInstancePtr()->getObject(_TX(#className))->clone()->toType<className>()

#define CLONEX(nameSpace, className) CCloneManager::getInstancePtr()->getObject(_TX(#className))->clone()->toType<nameSpace::className>()

#endif
