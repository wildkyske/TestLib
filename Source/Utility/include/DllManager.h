#ifndef DllManager_h__
#define DllManager_h__

#include <map>
#include "typedefs.h"
#include "UtilityExport.h"
#include "Singleton.h"

class DllManager_Implement;
class DllLoader;
class DllLoadObserver;

//虽说是插件系统，实际上只是负责管理动态库
class UTILITY_EXPORT DllManager
{
public:
    DllManager(void);
    virtual ~DllManager(void);
    
    // @Brief 安装插件 [1/14/2014 kyske]
    void installPlugin(const std::string& pluginName, const std::string& pluginPath, const std::string& userData = "");

    // @Brief 卸载插件 [1/14/2014 kyske]
    void uninstallPlugin(const std::string& pluginName);

    // @Brief 卸载全部插件 [1/14/2014 kyske]
    void uninstallAllPlugin();

    // @Brief 根据用户数据卸载插件 [1/24/2014 kyske]
    void uninstallPluginsByUserData(const std::string& strUserData);

    // @Brief 从文件读取插件 [1/14/2014 kyske]
    virtual bool readFromFile(const std::string& filePath);

    // @Brief 查询返回动态库加载器 [1/21/2014 kyske]
    DllLoader* queryDllByName(const std::string& pluginName);

public: //观察者相关
    // @Brief 注册观察者 [1/24/2014 kyske]
    bool registerObserver(DllLoadObserver* ob);

    // @Brief 取消观察者注册 [1/24/2014 kyske]
    bool unregisterObserver(DllLoadObserver* ob);
protected:
    DllManager_Implement* impl;
};

DECLARE_SINGLETON_CLASS(DllManagerSingleton, DllManager, UTILITY_EXPORT)

#endif // DllManager_h__

