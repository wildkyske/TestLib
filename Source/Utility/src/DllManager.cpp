#include "../include/DllManager.h"
#include "../include/DllManager_Implement.h"

IMPLEMENT_SINGLETON_CLASS(DllManagerSingleton)

DllManager::DllManager(void) : impl(NULL)
{
    impl = new DllManager_Implement;
}

DllManager::~DllManager(void)
{
    if (NULL == impl)
    {
        delete impl;
        impl = NULL;
    }
}

void DllManager::installPlugin( const std::string& pluginName, const std::string& pluginPath, const std::string& userData )
{
    if (NULL != impl)
    {
        impl->installPlugin(pluginName, pluginPath, userData);
    }
}

void DllManager::uninstallPlugin( const std::string& pluginName )
{
    if (NULL != impl)
    {
        impl->uninstallPlugin(pluginName);
    }
}

void DllManager::uninstallAllPlugin()
{
    if (NULL != impl)
    {
        impl->uninstallAllPlugin();
    }
}

bool DllManager::readFromFile( const std::string& filePath )
{
    //Ä¬ÈÏ½âÎö
    std::ifstream is;
    is.open(filePath.c_str());
    if (is.fail())
    {
        //Create Default Plugin ConfigFile

        return false;
    }

    std::string strBuffer;
    std::string pluginName;
    std::string pluginPath;
    std::string userData;
    while (std::getline(is, strBuffer))
    {
        std::stringstream ss(strBuffer);
        ss>>pluginName>>pluginPath>>userData;

        if (pluginName.empty() || pluginPath.empty())
        {
            continue;
        }
        installPlugin(pluginName, pluginPath, userData);
    }

    is.close();

    return true;
}

DllLoader* DllManager::queryDllByName( const std::string& pluginName )
{
    return impl->queryDllByName(pluginName);
}

bool DllManager::registerObserver( DllLoadObserver* ob )
{
    return impl->registerObserver(ob);
}

bool DllManager::unregisterObserver( DllLoadObserver* ob )
{
    return impl->unregisterObserver(ob);
}

void DllManager::uninstallPluginsByUserData( const std::string& strUserData )
{
    impl->uninstallPluginsByUserData(strUserData);
}
