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

    // @Brief ��װ��� [1/21/2014 kyske]
    void installPlugin(const std::string& pluginName, const std::string& pluginPath, const std::string& userData);

    // @Brief ж�ز�� [1/21/2014 kyske]
    void uninstallPlugin(const std::string& pluginName);

    // @Brief ж�����в�� [1/21/2014 kyske]
    void uninstallAllPlugin();

    // @Brief �����û�����ж�ز�� [1/24/2014 kyske]
    void uninstallPluginsByUserData(const std::string& strUserData);

    // @Brief ͨ�����Ʋ�ѯ��̬�� [1/21/2014 kyske]
    DllLoader* queryDllByName(const std::string& pluginName);

public: //�۲������
    // @Brief ע��۲��� [1/24/2014 kyske]
    bool registerObserver(DllLoadObserver* ob);

    // @Brief ȡ���۲���ע�� [1/24/2014 kyske]
    bool unregisterObserver(DllLoadObserver* ob);

protected:  //֪ͨ��̬����غ�ж��

    // @Brief ֪ͨ��̬����� [1/24/2014 kyske]
    bool notifyDllLoad(DllLoader* pDllLoader);

    // @Brief ֪ͨ��̬��ж�� [1/24/2014 kyske]
    bool notifyDllUnload(DllLoader* pDllLoader);

protected:
    MutexLock mPluginLock;      //�����
    std::map<const std::string, DllLoader*> mPlugins;   //�������

    MutexLock mObserverLock;    //�۲�����
    std::set<DllLoadObserver*> mObservers;   //�۲�������
};

#endif
