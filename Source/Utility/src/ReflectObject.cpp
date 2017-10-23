#include "../include/ReflectObject.h"
#include "../include/ReflectObject_Implement.h"
#include "../include/CodeConvert.h"

RepInstance::RepInstance( const std::string& className ) : mClassName(className)
{
    //初始化加入管理器
    RepInstance_Implement::getInstancePtr()->insert(className, this);
}

RepInstance::RepInstance( const std::wstring& className )
{
    std::string strClassName;
    CodeConvert::wstr2str(className, strClassName);
    RepInstance_Implement::getInstancePtr()->insert(strClassName, this);
}

RepInstance::~RepInstance()
{
    //卸载时，从管理器删除
    RepInstance_Implement::getInstancePtr()->remove(this);
}

ReflectObject* RepInstance::create( const std::string& className )
{
    RepInstance* pInstance = RepInstance_Implement::getInstancePtr()->find(className);
    if (NULL == pInstance)
    {
        return NULL;
    }

    ReflectObject* pReflectObject = pInstance->create();
    if (NULL != pReflectObject)
    {
        pReflectObject->setClassType(className);
    }

    return pReflectObject;
}

ReflectObject* RepInstance::create( const std::wstring& className )
{
    std::string strClassName;
    CodeConvert::wstr2str(className, strClassName);
    return create(strClassName);
}

std::string& RepInstance::getClassName()
{
    return mClassName;
}

const std::string& RepInstance::getClassName() const
{
    return mClassName;
}

ReflectObject::ReflectObject()
{
    setClassType(getClassName());
}

ReflectObject::~ReflectObject(void)
{
}

ReflectObject* ReflectObject::create( const std::string& className )
{
    return RepInstance::create(className);
}

ReflectObject* ReflectObject::create( const std::wstring& strClassName )
{
    std::string className;
    CodeConvert::wstr2str(strClassName, className);
    return create(className);
}

void ReflectObject::setClassType( const std::string& strClassType )
{
    mClassType = strClassType;
}

std::string& ReflectObject::classType()
{
    return mClassType;
}

const std::string& ReflectObject::classType() const
{
    return mClassType;
}

//==========================================================
// @Brief 发射观察者 [1/14/2014 kyske]

ReflectTypeRegisterObserver::ReflectTypeRegisterObserver()
{
    RepInstance_Implement::getInstancePtr()->registeObserver(this);
}

ReflectTypeRegisterObserver::~ReflectTypeRegisterObserver()
{
    RepInstance_Implement::getInstancePtr()->unregisteObserver(this);
}

bool ReflectTypeRegisterObserver::onReflectTypeUnregister( const std::string& className ) 
{
    return true;
}

bool ReflectTypeRegisterObserver::onReflectTypeRegister( const std::string& className ) 
{
    return true;
}
