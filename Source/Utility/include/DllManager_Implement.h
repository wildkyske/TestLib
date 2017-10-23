#pragma once
#ifndef PLUGIN_SYSTEM_IMPLEMENT_H
#define PLUGIN_SYSTEM_IMPLEMENT_H

#include <map>
#include <set>
#include "typedefs.h"
#include "MutexLock.h"

class DllLoader;
class DllLoadObserver;

class DllManager_Implement
{
public:
    DllManager_Implement(void);
    ~DllManager_Implement(void);

    // @Brief 安装插件 [1/21/2014 kyske]
    void installPlugin(const std::string& pluginName, const std::string& pluginPath, const std::string& userData);

    // @Brief 卸载插件 [1/21/2014 kyske]
    void uninstallPlugin(const std::string& pluginName);

    // @Brief 卸载所有插件 [1/21/2014 kyske]
    void uninstallAllPlugin();

    // @Brief 根据用户数据卸载插件 [1/24/2014 kyske]
    void uninstallPluginsByUserData(const std::string& strUserData);

    // @Brief 通过名称查询动态库 [1/21/2014 kyske]
    DllLoader* queryDllByName(const std::string& pluginName);

public: //观察者相关
    // @Brief 注册观察者 [1/24/2014 kyske]
    bool registerObserver(DllLoadObserver* ob);

    // @Brief 取消观察者注册 [1/24/2014 kyske]
    bool unregisterObserver(DllLoadObserver* ob);

protected:  //通知动态库加载和卸载

    // @Brief 通知动态库加载 [1/24/2014 kyske]
    bool notifyDllLoad(DllLoader* pDllLoader);

    // @Brief 通知动态库卸载 [1/24/2014 kyske]
    bool notifyDllUnload(DllLoader* pDllLoader);

protected:
    MutexLock mPluginLock;      //插件锁
    std::map<const std::string, DllLoader*> mPlugins;   //插件容器

    MutexLock mObserverLock;    //观察者锁
    std::set<DllLoadObserver*> mObservers;   //观察者容器
};

#endif
