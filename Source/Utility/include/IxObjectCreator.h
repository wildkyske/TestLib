#ifndef IxObjectCreator_h__
#define IxObjectCreator_h__

#include "IxObject.h"
#include "ThreadMutex.h"
#include <string>
#include <map>
#include <typeinfo>

// @Brief ����ע�������� [1/19/2016 kyske]
class UTILITY_EXPORT IxObjectRegisterAgent
{
public:
    virtual ~IxObjectRegisterAgent(){}

    virtual IxObject* create() = 0;
};

// @Brief ����ע����� [1/19/2016 kyske]
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

// @Brief ���󴴽��� [1/19/2016 kyske]
class UTILITY_EXPORT IxObjectCreator
{
public:
    IxObjectCreator();
    virtual ~IxObjectCreator();

    // @Brief ע������ [1/19/2016 kyske]
    void registerType(const std::string& strTypeName, IxObjectRegisterAgent* pAgent);

    // @Brief ȡ������ע�� [1/19/2016 kyske]
    IxObjectRegisterAgent* unregisterType(const std::string& strTypeName);

    // @Brief �������� [1/19/2016 kyske]
    IxObject* createObject(const std::string& strTypeName);

    //ģ��ע���ȡ��ע��
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
