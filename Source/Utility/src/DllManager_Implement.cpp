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
    //自动释放
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

	//->加载插件,需要切换工作目录到插件所在目录
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
		//如果执行失败,需要切换目录
		stlu::changeDir(strCurDir);
        return;
    }

	//切换到之前的工作目录<-
	stlu::changeDir(strCurDir);

    pluginLoader->setUserData(userData);

    mPlugins.insert(std::make_pair(pluginName, pluginLoader));

    //通知插件加载
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
        //通知插件即将卸载
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
            //通知插件即将卸载
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
            //通知插件即将卸载
            notifyDllUnload(dl);

            dl->release();
            delete dl;
            dl = NULL;
        }

        ++it;
    }
}

