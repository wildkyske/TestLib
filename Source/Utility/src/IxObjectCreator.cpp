#include "../include/IxObjectCreator.h"
#include "../include/Guard.h"

IxObjectCreator::IxObjectCreator()
{

}

IxObjectCreator::~IxObjectCreator()
{

}

void IxObjectCreator::registerType( const std::string& strTypeName, IxObjectRegisterAgent* pAgent )
{
    GUARD(ThreadMutex, m_ObjectAgentsLock);

    std::map<const std::string, IxObjectRegisterAgent*>::iterator it = m_ObjectAgents.find(strTypeName);
    if (it != m_ObjectAgents.end())
    {
        return;
    }
    m_ObjectAgents.insert(std::make_pair(strTypeName, pAgent));
}

IxObjectRegisterAgent* IxObjectCreator::unregisterType( const std::string& strTypeName )
{
    GUARD(ThreadMutex, m_ObjectAgentsLock);

    std::map<const std::string, IxObjectRegisterAgent*>::iterator it = m_ObjectAgents.find(strTypeName);
    if (it == m_ObjectAgents.end())
    {
        return NULL;
    }
    IxObjectRegisterAgent* pAgent = it->second;
    m_ObjectAgents.erase(it);

    return pAgent;
}

IxObject* IxObjectCreator::createObject( const std::string& strTypeName )
{
    GUARD(ThreadMutex, m_ObjectAgentsLock);

    std::map<const std::string, IxObjectRegisterAgent*>::iterator it = m_ObjectAgents.find(strTypeName);
    if (it == m_ObjectAgents.end())
    {
        return NULL;
    }
    IxObjectRegisterAgent* pAgent = it->second;
    if (NULL == pAgent)
    {
        return NULL;
    }

    return pAgent->create();
}

void IxObjectCreator::unregisterAllType()
{
    GUARD(ThreadMutex, m_ObjectAgentsLock);
    for (std::map<const std::string, IxObjectRegisterAgent*>::iterator it = m_ObjectAgents.begin(); 
        it != m_ObjectAgents.end(); ++it)
    {
        IxObjectRegisterAgent* pAgent = it->second;
        if (NULL == pAgent)
        {
            continue;
        }
        delete pAgent;
    }

    m_ObjectAgents.clear();
}
