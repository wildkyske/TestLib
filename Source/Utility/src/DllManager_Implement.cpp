#include "../include/DllManager_Implement.h"
#include "../include/DllLoader.h"
#include "../include/DllLoadObserver.h"
#include "../include/StlUtil.h"
#include "../include/XFile.h"

DllManager_Implement::DllManager_Implement(void)
{
}

DllManager_Implement::~DllManager_Implement(void)
{
    //�Զ��ͷ�
    uninstallAllPlugin();
}

void DllManager_Implement::installPlugin( const std::string& pluginName, const std::string& pluginPath, const std::string& userData )
{
    GUARD(MutexLock, mPluginLock);

    std::map<const std::string, DllLoader*>::iterator it = mPlugins.find(pluginName);
    if (it != mPlugins.end())
    {
        //hav' exist
        return;
    }

	//->���ز��,��Ҫ�л�����Ŀ¼���������Ŀ¼
	std::string strCurDir = stlu::currentDir();
	XFile dllPath(pluginPath);
	std::string strDir = dllPath.absoluteDir();
	stlu::changeDir(strDir);

    DllLoader* pluginLoader = new DllLoader(pluginName);
    bool bLoadOk = pluginLoader->load(pluginPath);
    if (!bLoadOk)
    {
        //load failed.
        delete pluginLoader;
		//���ִ��ʧ��,��Ҫ�л�Ŀ¼
		stlu::changeDir(strCurDir);
        return;
    }

	//�л���֮ǰ�Ĺ���Ŀ¼<-
	stlu::changeDir(strCurDir);

    pluginLoader->setUserData(userData);

    mPlugins.insert(std::make_pair(pluginName, pluginLoader));

    //֪ͨ�������
    notifyDllLoad(pluginLoader);
}

void DllManager_Implement::uninstallPlugin( const std::string& pluginName )
{
    GUARD(MutexLock, mObserverLock);

    std::map<const std::string, DllLoader*>::iterator it = mPlugins.find(pluginName);
    if (it == mPlugins.end())
    {
        return;
    }
    DllLoader* pluginLoader = it->second;
    if (NULL != pluginLoader)
    {
        //֪ͨ�������ж��
        notifyDllUnload(pluginLoader);

        pluginLoader->release();
        delete pluginLoader;
        pluginLoader = NULL;
    }
    mPlugins.erase(it);
}

void DllManager_Implement::uninstallAllPlugin()
{
    GUARD(MutexLock, mPluginLock);

    for (std::map<const std::string, DllLoader*>::iterator it = mPlugins.begin(); 
        it != mPlugins.end(); ++it)
    {
        DllLoader* pluginLoader = it->second;
        if (NULL != pluginLoader)
        {
            //֪ͨ�������ж��
            notifyDllUnload(pluginLoader);

            pluginLoader->release();
            delete pluginLoader;
            pluginLoader = NULL;
        }
    }

    mPlugins.clear();
}

DllLoader* DllManager_Implement::queryDllByName( const std::string& pluginName )
{
    GUARD(MutexLock, mPluginLock);

    std::map<const std::string, DllLoader*>::iterator it = mPlugins.find(pluginName);
    if (it == mPlugins.end())
    {
        return NULL;
    }

    DllLoader* pDllLoader = it->second;
    if (NULL == pDllLoader)
    {
        return NULL;
    }

    return pDllLoader;
}

bool DllManager_Implement::registerObserver( DllLoadObserver* ob )
{
    GUARD(MutexLock, mObserverLock);
    if (NULL == ob)
    {
        return false;
    }

    std::set<DllLoadObserver*>::iterator it = mObservers.find(ob);
    if (it != mObservers.end())
    {
        return true;
    }

    mObservers.insert(ob);

    return true;
}

bool DllManager_Implement::unregisterObserver( DllLoadObserver* ob )
{
    GUARD(MutexLock, mObserverLock);
    if (NULL == ob)
    {
        return false;
    }

    std::set<DllLoadObserver*>::iterator it = mObservers.find(ob);
    if (it == mObservers.end())
    {
        return true;
    }

    mObservers.erase(ob);

    return true;
}

bool DllManager_Implement::notifyDllLoad( DllLoader* pDllLoader )
{
    GUARD(MutexLock, mObserverLock);

    if (NULL == pDllLoader)
    {
        return false;
    }

    for (std::set<DllLoadObserver*>::iterator it = mObservers.begin(); 
        it != mObservers.end(); ++it)
    {
        DllLoadObserver* dlob = *it;
        if (NULL == dlob)
        {
            continue;
        }

        dlob->onDllLoad(pDllLoader);
    }

    return true;
}

bool DllManager_Implement::notifyDllUnload( DllLoader* pDllLoader )
{
    GUARD(MutexLock, mObserverLock);

    if (NULL == pDllLoader)
    {
        return false;
    }

    for (std::set<DllLoadObserver*>::iterator it = mObservers.begin(); 
        it != mObservers.end(); ++it)
    {
        DllLoadObserver* dlob = *it;
        if (NULL == dlob)
        {
            continue;
        }

        dlob->onDllUnload(pDllLoader);
    }

    return true;
}

void DllManager_Implement::uninstallPluginsByUserData( const std::string& strUserData )
{
    GUARD(MutexLock, mPluginLock);

    for (std::map<const std::string, DllLoader*>::iterator it = mPlugins.begin(); 
        it != mPlugins.end(); )
    {
        DllLoader* dl = it->second;
        if (NULL == dl)
        {
            ++it;
            continue;
        }

        if (dl->userData() == strUserData)
        {
            //֪ͨ�������ж��
            notifyDllUnload(dl);

            dl->release();
            delete dl;
            dl = NULL;
        }

        ++it;
    }
}

