//--------------------------------------------------
//filename : usefultstlex.h  && usefultstlex.cpp
//desc : 常用stl方法
//--------------------------------------------------
#pragma once
#ifndef _USEFUL_STL_EX_H
#define _USEFUL_STL_EX_H

#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
#include <list>
#include <time.h>
#include "base_constant.h"
#include "CodeConvert.h"

namespace stlu
{
    // 大写 [4/8/2015 Administrator]
    UTILITY_EXPORT std::string upper(const std::string& strSrc);

    UTILITY_EXPORT std::wstring upper(const std::wstring& strSrc);

    UTILITY_EXPORT void upper(std::string& strSrc);

    UTILITY_EXPORT void upper(std::wstring& strSrc);

    // 小写 [4/8/2015 Administrator]
    UTILITY_EXPORT std::string lower(const std::string& strSrc);

    UTILITY_EXPORT std::wstring lower(const std::wstring& strSrc);

    UTILITY_EXPORT void lower(std::string& strSrc);

    UTILITY_EXPORT void lower(std::wstring& strSrc);

    // 去除空白 [4/8/2015 Administrator]
    UTILITY_EXPORT std::string trimC(const std::string& strSrc);

    UTILITY_EXPORT std::wstring trimC(const std::wstring& strSrc);

    UTILITY_EXPORT void trim(std::string& strSrc);

    UTILITY_EXPORT void trim(std::wstring& strSrc);

    UTILITY_EXPORT void trimLeft(std::string& strSrc, const std::string& strToken = "\n");

    UTILITY_EXPORT void trimLeft(std::wstring& strSrc, const std::wstring& strToken = L"\n");

    UTILITY_EXPORT void trimRight(std::string& strSrc, const std::string& strToken = " ");

    UTILITY_EXPORT void trimRight(std::wstring& strSrc, const std::wstring& strToken = L" ");

    // 替换 [4/8/2015 Administrator]
    UTILITY_EXPORT void replace(std::string& strSrc, const std::string& strToken, const std::string& strToken2);

    UTILITY_EXPORT void replace(std::wstring& strSrc, const std::wstring& strToken, const std::wstring& strToken2);

    // 开头是否为 [4/8/2015 Administrator]
    UTILITY_EXPORT bool isStartWith(const std::string& strSrc, const std::string& strToken);

    UTILITY_EXPORT bool isStartWith(const std::wstring& strSrc, const std::wstring& strToken);

    // 是否结束为 [4/8/2015 Administrator]
    UTILITY_EXPORT bool isEndWith(const std::string& strSrc, const std::string& strToken);

    UTILITY_EXPORT bool isEndWith(const std::wstring& strSrc, const std::wstring& strToken);

    // 拆分字符串 [4/8/2015 Administrator]
    UTILITY_EXPORT void split(const std::string& strSrc, const std::string& token, std::vector<std::string>& vStr);

    UTILITY_EXPORT void split(const std::wstring& strSrc, const std::wstring& token, std::vector<std::wstring>& vStr);

    UTILITY_EXPORT std::vector<std::string> split(const std::string& strSrc, const std::string& token);

    UTILITY_EXPORT std::vector<std::wstring> split(const std::wstring& strSrc, const std::wstring& token);

    // 反转 [4/8/2015 Administrator]
    UTILITY_EXPORT void reverse(std::string& strSrc);

    UTILITY_EXPORT void reverse(std::wstring& strSrc);

    // 扩展名 [4/8/2015 Administrator]
    UTILITY_EXPORT std::string extendName(const std::string& strSrc, const std::string& strToken = ".");

    UTILITY_EXPORT std::wstring extendName(const std::wstring& strSrc, const std::wstring& strToken = L".");

    // 完整目录 [4/8/2015 Administrator]
    UTILITY_EXPORT std::string complateDir(const std::string& path, const std::string& token = "/");

    UTILITY_EXPORT std::wstring complateDir(const std::wstring& path, const std::wstring& token = L"/");

    // 去掉结尾 [4/8/2015 Administrator]
    UTILITY_EXPORT void eraserSuffix(std::string& str);

    UTILITY_EXPORT void eraserSuffix(std::wstring& str);

	// 去掉某个标志以后的字符串 [3/19/2016 Administrator]
	UTILITY_EXPORT void eraserLastOf(std::string& str, const std::string& token);

	UTILITY_EXPORT void eraserLastOf(std::wstring& str, const std::wstring& token);

    // 字符串结尾 [4/8/2015 Administrator]
    UTILITY_EXPORT void endOfString(std::string& str, const std::string& token = "/");

    UTILITY_EXPORT void endOfString(std::wstring& str, const std::wstring& token = L"/");

    // 解析文件名 [4/8/2015 Administrator]
    UTILITY_EXPORT std::string parseFileName(const std::string& path);

    UTILITY_EXPORT std::wstring parseFileName(const std::wstring& path);

    UTILITY_EXPORT std::string parseFileSuffix(const std::string& strPath);

    UTILITY_EXPORT std::wstring parseFileSuffix(const std::wstring& strPath);

    UTILITY_EXPORT std::string parseFileBaseName(const std::string& strPath);

    UTILITY_EXPORT std::wstring parseFileBaseName(const std::wstring& strPath);

    // 日期 [4/8/2015 Administrator]
    UTILITY_EXPORT tstring date();

    UTILITY_EXPORT std::string dateMb();

    UTILITY_EXPORT std::wstring dateW();
};

// 模板实现常用的函数 [4/8/2015 Administrator]
namespace stlu
{
    // 转换为字符串 [4/8/2015 Administrator]
    template<class T>
    tstring toString(T value)
    {
        tsstream s;
        s<<value;
        return s.str();
    }

    template <typename T>
    std::string toMbString(T nValue)
    {
        std::stringstream ss;
        ss << nValue;
        return ss.str();
    }

    template <typename T>
    std::wstring toWString(T nValue)
    {
        std::wstringstream ss;
        ss << nValue;
        return ss.str();
    }

    // 字符串转换为值 [4/8/2015 Administrator]
    template<class T>
    T stringTo(const std::string& strSrc)
    {
        T value;
        std::stringstream(strSrc)>>value;
        return value;
    }

    template<class T>
    T stringTo(const std::wstring& strSrc)
    {
        T value;
        std::wstringstream(strSrc)>>value;
        return value;
    }

    inline bool toBoolean(const std::string& str)
    {
        return str == "true";
    }

    inline bool toBoolean(const std::wstring& str)
    {
        return str == L"true";
    }

    inline std::string toString(bool val)
    {
        return val ? "true" : "false";
    }

    inline std::wstring toWString(bool val)
    {
        return val ? L"true" : L"false";
    }
}

//文件相关的简单函数
namespace stlu
{
    //文件创建
    UTILITY_EXPORT bool fileCreate(const std::string& strFilePath);

    //文件创建
    UTILITY_EXPORT bool fileCreate(const std::wstring& strFilePath);

    //文件存在
    UTILITY_EXPORT bool fileExist(const std::string& strFilePath);

    UTILITY_EXPORT bool fileExist(const std::wstring& strFilePath);

    //文件大小
    UTILITY_EXPORT unsigned int fileSize(const std::string& strFilePath);

    UTILITY_EXPORT unsigned int fileSize(const std::wstring& strFilePath);

    //文件删除
    UTILITY_EXPORT bool fileRemove(const std::string& strFilePath);

    UTILITY_EXPORT bool fileRemove(const std::wstring& strFilePath);

    //返回当前工作路径
    UTILITY_EXPORT std::string currentDir();

	//设置当前工作路径
	UTILITY_EXPORT void changeDir(const std::string& strPath);

    //可执行程序路径
    UTILITY_EXPORT std::string moduleDir();

    //创建目录
    UTILITY_EXPORT bool dirCreate(const std::string& strDirPath);

    //移除目录,只能移除空目录
    UTILITY_EXPORT bool dirRemove(const std::string& strDirPath);

    UTILITY_EXPORT bool dirExist(const std::string& strDirPath);
}

//系统相关
namespace stlu
{
    //睡眠(毫秒)
    void sleepMS(int nMilSecond);
}
#endif




