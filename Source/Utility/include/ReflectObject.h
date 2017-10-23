#pragma once
#ifndef REFLECT_OBJECT_H
#define REFLECT_OBJECT_H

#include <string>
#include <list>
#include "typedefs.h"
#include "UtilityExport.h"

class ReflectObject;
class RepInstance_Implement;

/*
	ClassName:	ReflectObjectRegiterObserver
	Brief:		�������ע��۲���
	Author:		kyske
	Date:		2014/01/14
*/
class UTILITY_EXPORT ReflectTypeRegisterObserver
{
public:
    ReflectTypeRegisterObserver();

    virtual~ReflectTypeRegisterObserver();

    virtual bool onReflectTypeRegister(const std::string& className) ;

    virtual bool onReflectTypeUnregister(const std::string& className) ;
};

/*
	ClassName:	RepInstance
	Brief:		�������ע������
	Author:		kyske
	Date:		2014/01/14
*/
class UTILITY_EXPORT RepInstance
{
public:
    RepInstance(const std::string& className);
    
    RepInstance(const std::wstring& className);

    virtual ~RepInstance();

    static ReflectObject* create(const std::string& className);

    static ReflectObject* create(const std::wstring& className);

    virtual ReflectObject* create() = 0;

    // @Brief ��ȡ���� [1/14/2014 kyske]
    std::string& getClassName();

    // @Brief ��ȡ���� [1/14/2014 kyske]
    const std::string& getClassName() const;
protected:
    std::string mClassName;
};

typedef void (*ReflectCallback)(const std::string& strClassName, void* pExtra, void* pExtra2);

template <typename T>
class ReflectInstance : public RepInstance
{
public:
    ReflectInstance(const std::string& className) : RepInstance(className)
    {

    }

    ReflectInstance(const std::string& className, ReflectCallback pCallBack, void* pExtra, void* pExtra2)
        : RepInstance(className)
    {
        if (NULL != pCallBack)
        {
            (*pCallBack)(className, pExtra, pExtra2);
        }
    }
    virtual ~ReflectInstance(){}

    virtual ReflectObject* create();
};

class UTILITY_EXPORT ReflectObject
{
public:
    ReflectObject(void);
    virtual ~ReflectObject(void);

    // @Brief ͨ����������ʵ��(��̬ģ��) [1/14/2014 kyske]
    template<class T>
    static T* createx(const std::string& className)
    {
        ReflectObject* refObj = RepInstance::create(className);
        if (NULL == refObj)
        {
            return NULL;
        }

        return dynamic_cast<T*>(refObj);
    }

    // @Brief ���ýӿ� [1/14/2014 kyske]
    static ReflectObject* create(const std::string& className);

    static ReflectObject* create(const std::wstring& strClassName);

    // @Brief ע�����ӿ� [1/14/2014 kyske]
    virtual RepInstance* getRepInstance() const = 0;

    virtual std::string getClassName() const {return "";}

    //������������Ϊ�����л�����
    void setClassType(const std::string& strClassType);

    std::string& classType();

    const std::string& classType() const;
protected:
    std::string mClassType;
};

template <typename T>
ReflectObject* ReflectInstance<T>::create()
{
    ReflectObject* pReflectObject = new T;
    if (NULL != pReflectObject)
    {
        pReflectObject->setClassType(mClassName);
    }
    return pReflectObject;
}
/*
*�궨��
*/
#define DECLARE_REFLECT_OBJECT(ClassName) \
    static ReflectInstance<ClassName> mRepInstance; \
    virtual RepInstance* getRepInstance() const \
{\
    return &mRepInstance;\
}\
    static std::string getClassNameStatic() { return mRepInstance.getClassName(); } \
    std::string getClassName() const{return std::string(#ClassName);}

#define IMPLEMENT_REFLECT_OBJECT(ClassName) \
    ReflectInstance<ClassName> ClassName::mRepInstance(#ClassName);

#define IMPLEMENT_REFLECT_OBJECT_CALLBACK(ClassName,CallBackFunction, extra, extra2) \
    ReflectInstance<ClassName> ClassName::mRepInstance(#ClassName, CallBackFunction, extra, extra2);

//ע�ᷴ����
#define REGISTER_REFLECT_CLASS(ClassName, BaseClassName, ExportMark) \
class ExportMark ClassName : public BaseClassName, public ReflectObject \
{ \
    DECLARE_REFLECT_OBJECT(ClassName) \
public: \
    ClassName(){} \
    ~ClassName(){} \
}; \
IMPLEMENT_REFLECT_OBJECT(ClassName)

#endif
