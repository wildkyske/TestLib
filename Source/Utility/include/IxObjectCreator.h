#ifndef IxObjectCreator_h__
#define IxObjectCreator_h__

#include "IxObject.h"
#include "ThreadMutex.h"
#include <string>
#include <map>
#include <typeinfo>

// @Brief 对象注册代理基类 [1/19/2016 kyske]
class UTILITY_EXPORT IxObjectRegisterAgent
{
public:
    virtual ~IxObjectRegisterAgent(){}

    virtual IxObject* create() = 0;
};

// @Brief 对象注册代理 [1/19/2016 kyske]
template <typename T>
class UTILITY_EXPORT ObjectRegisterAgentT : public IxObjectRegisterAgent
{
public:
    ObjectRegisterAgentT(){}
    virtual ~ObjectRegisterAgentT(){}

    virtual IxObject* create()
    {
        return new T;
    }
};

// @Brief 对象创建器 [1/19/2016 kyske]
class UTILITY_EXPORT IxObjectCreator
{
public:
    IxObjectCreator();
    virtual ~IxObjectCreator();

    // @Brief 注册类型 [1/19/2016 kyske]
    void registerType(const std::string& strTypeName, IxObjectRegisterAgent* pAgent);

    // @Brief 取消类型注册 [1/19/2016 kyske]
    IxObjectRegisterAgent* unregisterType(const std::string& strTypeName);

    // @Brief 创建对象 [1/19/2016 kyske]
    IxObject* createObject(const std::string& strTypeName);

    //模板注册和取消注册
    template <typename T>
    void registerType()
    {
        std::string strClassTypeName = typeid(T).name();
        std::string strClassName = strClassTypeName;
        IxObjectRegisterAgent* pAgent = new ObjectRegisterAgentT<T>();
        registerType(strClassName, pAgent);
    }

    template <typename T>
    void unregisterType()
    {
        std::string strClassTypeName = typeid(T).name();
        std::string strClassName = strClassTypeName;
        IxObjectRegisterAgent* pAgent = unregisterType(strClassName);
        if (NULL != pAgent)
        {
            delete pAgent;
        }
    }

    virtual void unregisterAllType();
protected:
    ThreadMutex m_ObjectAgentsLock;
    std::map<const std::string, IxObjectRegisterAgent*> m_ObjectAgents;
};
#endif // IxObjectCreator_h__
