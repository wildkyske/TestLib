#ifndef DllManager_h__
#define DllManager_h__

#include <map>
#include "typedefs.h"
#include "UtilityExport.h"
#include "Singleton.h"

class DllManager_Implement;
class DllLoader;
class DllLoadObserver;

//��˵�ǲ��ϵͳ��ʵ����ֻ�Ǹ������̬��
class UTILITY_EXPORT DllManager
{
public:
    DllManager(void);
    virtual ~DllManager(void);
    
    // @Brief ��װ��� [1/14/2014 kyske]
    void installPlugin(const std::string& pluginName, const std::string& pluginPath, const std::string& userData = "");

    // @Brief ж�ز�� [1/14/2014 kyske]
    void uninstallPlugin(const std::string& pluginName);

    // @Brief ж��ȫ����� [1/14/2014 kyske]
    void uninstallAllPlugin();

    // @Brief �����û�����ж�ز�� [1/24/2014 kyske]
    void uninstallPluginsByUserData(const std::string& strUserData);

    // @Brief ���ļ���ȡ��� [1/14/2014 kyske]
    virtual bool readFromFile(const std::string& filePath);

    // @Brief ��ѯ���ض�̬������� [1/21/2014 kyske]
    DllLoader* queryDllByName(const std::string& pluginName);

public: //�۲������
    // @Brief ע��۲��� [1/24/2014 kyske]
    bool registerObserver(DllLoadObserver* ob);

    // @Brief ȡ���۲���ע�� [1/24/2014 kyske]
    bool unregisterObserver(DllLoadObserver* ob);
protected:
    DllManager_Implement* impl;
};

DECLARE_SINGLETON_CLASS(DllManagerSingleton, DllManager, UTILITY_EXPORT)

#endif // DllManager_h__

