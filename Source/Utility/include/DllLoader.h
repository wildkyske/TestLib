#pragma once
#ifndef DLL_LOADER_H
#define DLL_LOADER_H

#include "UtilityExport.h"
#include "base_constant.h"

//WIN_32 支持
#ifdef WIN32
#include <Windows.h>
typedef HMODULE DLLHANDLER;
#elif __linux__
typedef void* DLLHANDLER;
#endif

/*
	ClassName:	DllLoader
	Brief:		动态库加载器
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

    // @Brief 加载动态库 [1/21/2014 kyske]
    bool load(const std::string& dllpath);

    // @Brief 重新加载 [1/21/2014 kyske]
    bool reload();

    // @Brief 释放动态库 [1/21/2014 kyske]
    void release();

	// 还未实现 [2/22/2016 Administrator]
	bool invoke(const std::string& strFuncName);

	// 查询函数指针 [3/20/2016 kyske]
	void* resolve(const std::string& strFuncName);

public: //属性
    // @Brief 加载状态 [1/21/2014 kyske]
    int loadStatus() const;

    // @Brief 加载DLL路径 [1/21/2014 kyske]
    std::string& loadPath();
    const std::string& loadPath() const;

    // @Brief 加载模型路径 [1/21/2014 kyske]
    std::string& loadModelPath();
    const std::string& loadModelPath() const;

    // @Brief 设置名称 [1/21/2014 kyske]
    void setName(const std::string& strName);

    // @Brief 返回名称 [1/21/2014 kyske]
    std::string& name();
    const std::string& name() const;

    // @Brief 用户数据写 [1/24/2014 kyske]
    void setUserData(const std::string& strData);
    std::string& userData();
    const std::string& userData() const;
protected:
    DLLHANDLER mHandler;    //库句柄
    std::string mDllPath;       //库输入路径
    std::string mModelPath;     //模型路径
    std::string mName;       //动态库名称
    int mLoadStatus;        //加载状态

    std::string mUserData;   //用户字串数据
};

#endif
