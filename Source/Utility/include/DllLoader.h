#pragma once
#ifndef DLL_LOADER_H
#define DLL_LOADER_H

#include "UtilityExport.h"
#include "base_constant.h"

//WIN_32 ֧��
#ifdef WIN32
#include <Windows.h>
typedef HMODULE DLLHANDLER;
#elif __linux__
typedef void* DLLHANDLER;
#endif

/*
	ClassName:	DllLoader
	Brief:		��̬�������
	Author:		kyske
	Date:		2014/01/21
*/
class UTILITY_EXPORT DllLoader
{
public:
    enum
    {
        DLL_LOAD_STATUS_UNLOAD = 0,
        DLL_LOAD_STATUS_LOADED,
    };
public:
    DllLoader(const std::string& strName = "");
    ~DllLoader(void);

    // @Brief ���ض�̬�� [1/21/2014 kyske]
    bool load(const std::string& dllpath);

    // @Brief ���¼��� [1/21/2014 kyske]
    bool reload();

    // @Brief �ͷŶ�̬�� [1/21/2014 kyske]
    void release();

	// ��δʵ�� [2/22/2016 Administrator]
	bool invoke(const std::string& strFuncName);

	// ��ѯ����ָ�� [3/20/2016 kyske]
	void* resolve(const std::string& strFuncName);

public: //����
    // @Brief ����״̬ [1/21/2014 kyske]
    int loadStatus() const;

    // @Brief ����DLL·�� [1/21/2014 kyske]
    std::string& loadPath();
    const std::string& loadPath() const;

    // @Brief ����ģ��·�� [1/21/2014 kyske]
    std::string& loadModelPath();
    const std::string& loadModelPath() const;

    // @Brief �������� [1/21/2014 kyske]
    void setName(const std::string& strName);

    // @Brief �������� [1/21/2014 kyske]
    std::string& name();
    const std::string& name() const;

    // @Brief �û�����д [1/24/2014 kyske]
    void setUserData(const std::string& strData);
    std::string& userData();
    const std::string& userData() const;
protected:
    DLLHANDLER mHandler;    //����
    std::string mDllPath;       //������·��
    std::string mModelPath;     //ģ��·��
    std::string mName;       //��̬������
    int mLoadStatus;        //����״̬

    std::string mUserData;   //�û��ִ�����
};

#endif
