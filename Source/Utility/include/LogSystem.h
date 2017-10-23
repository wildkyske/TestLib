#pragma once
#ifndef LOG_SYSTEM_H
#define LOG_SYSTEM_H

#include "typedefs.h"
#include "Subject.h"
#include "UtilityExport.h"
#include "Singleton.h"

namespace LogSystemNS
{
    enum
    {
        LOG_LVL_NULL = 0,   //没有级别，什么都不是
        LOG_LVL_INFO = 0x01,       //最低级别，常用信息日志
        LOG_LVL_NOTICE = 0x02,     //提醒级别
        LOG_LVL_WARNING = 0x04,    //警告级别
        LOG_LVL_ERROR = 0x08,      //错误级别
        LOG_LVL_FATAL = 0x10,      //致命级别
        LOG_LVL_USER = 0x20,        //用户级别
        LOG_LVL_DUMP = 0x80000000,  //dump级别,特殊级别
        LOG_LVL_ALL = 0xffffffff,   //所有级别
    };

    UTILITY_EXPORT std::string logLvlToString(int lvl);

    UTILITY_EXPORT std::wstring logLvlToWideString(int lvl);

    UTILITY_EXPORT std::string logLvlMaskToString(int nLvl);

    //用于显示和存储日志的地方
    class UTILITY_EXPORT Logger 
    {
    public:
        Logger();
        virtual ~Logger();

        //初始化日志,输入地址和端口,文件日志输入文件路径
        virtual bool initialise(const std::string& strAddr, const std::string& strPort = "");

        //清理日志记录器
        virtual void cleanup();

        void onLog(int lvl, const std::string& logTxt);

        //设置日志MASK
        void setLogMask(int nLogMask);

        //允许某个级别
        void enableLvl(int nLvl);

        //禁止某个级别
        void disableLvl(int nLvl);
    protected:

        virtual void _onLog(int lvl, const std::string& logTxt) = 0;

    protected:
        int mLogMask;
        
    };

    /*
        @. 文件日志.
    */
    class UTILITY_EXPORT FileLogger : public Logger
    {
    public:
        FileLogger(const std::string& filePath);
        virtual ~FileLogger();

        virtual bool initialise(const std::string& strAddr, const std::string& strPort /* = _TX */);

        virtual void cleanup();

    protected:

        virtual void _onLog(int lvl, const std::string& logTxt);

    protected:
        tofstream m_streamFile;
    };

    /*
    	ClassName:	FileLoggerMBCS
    	Brief:		多字节流 - 文件记录器
    	Author:		kyske
    	Date:		2013/12/10
    */
    class UTILITY_EXPORT FileLoggerMBCS : public Logger
    {
    public:

        FileLoggerMBCS();

        FileLoggerMBCS(const std::string& );

        virtual ~FileLoggerMBCS();

        virtual bool initialise(const std::string& strAddr, const std::string& strPort /* = _TX */);

        virtual void cleanup();
    protected:
        void _onLog(int lvl, const std::string& logTxt);

    protected:
        std::ofstream mFileStream;
    };

    /*
        @. 控制台日志
    */
    class UTILITY_EXPORT ConsoleLogger : public Logger
    {
    public:
        ConsoleLogger();

        virtual ~ConsoleLogger();

    protected:
        virtual void _onLog(int lvl, const std::string& logTxt);
    };

    /*
        @. 日志系统，通过观察者模式实现
        ->下一步，重载<<操作符
    */
    class UTILITY_EXPORT LogSystemBase : public Subject<Logger>
    {
    public:

        LogSystemBase();

        virtual ~LogSystemBase();

        //带有级别信息的日志
        void notify(int lvl, const std::string& txt);
        
        // @Brief 设置日志掩码 [12/10/2013 kyske]
        void setLogMask(int nMask);
        
        // @Brief 日志掩码是否可用 [12/10/2013 kyske]
        bool isLogMaskEnable(int nMask) const;

        // @Brief 允许级别 [12/10/2013 kyske]
        void enableLvl(int nLvl);

        // @Brief 禁用级别 [12/10/2013 kyske]
        void disableLvl(int nLvl);

    protected:
        int mLogMask;
    };

    DECLARE_SINGLETON_CLASS(LogSystem, LogSystemBase, UTILITY_EXPORT)

    class UTILITY_EXPORT NullStream
    {
    public:
        NullStream();
        virtual ~NullStream();

        //重写各种操作符
        virtual NullStream& operator<<(float nVal);
        virtual NullStream& operator<<(double nVal);
        virtual NullStream& operator<<(bool bVal);

        virtual NullStream& operator<<(char nVal);
        virtual NullStream& operator<<(wchar_t nVal);      

        virtual NullStream& operator<<(short nVal);
        virtual NullStream& operator<<(int nVal);
        virtual NullStream& operator<<(long nVal);

        virtual NullStream& operator<<(unsigned char nVal);
        virtual NullStream& operator<<(unsigned int nVal);
        virtual NullStream& operator<<(unsigned long nVal);

        virtual NullStream& operator<<(const std::wstring& strVal);

        virtual NullStream& operator<<(const std::string& strVal);

    };

    class UTILITY_EXPORT LogObject : public NullStream
    {
    public:

        LogObject(int nLvl, LogSystemBase* pLogSystem = NULL);

        virtual ~LogObject();

        LogObject(const LogObject& rhs);

        LogObject& operator=(const LogObject& rhs);

        //重写各种操作符
        LogObject& operator<<(float nVal);
        LogObject& operator<<(double nVal);
        LogObject& operator<<(bool bVal);

        LogObject& operator<<(char nVal);
        LogObject& operator<<(wchar_t nVal);        

        LogObject& operator<<(short nVal);
        LogObject& operator<<(int nVal);
        LogObject& operator<<(long nVal);

        LogObject& operator<<(unsigned char nVal);
        LogObject& operator<<(unsigned int nVal);
        LogObject& operator<<(unsigned long nVal);

        LogObject& operator<<(const std::string& strVal);
        LogObject& operator<<(const std::wstring& strVal);

        LogObject& operator<<(char* pszVal);
        LogObject& operator<<(const char* pszVal);

        LogObject& operator<<(wchar_t* pszVal);
        LogObject& operator<<(const wchar_t* pszVal);
        
    protected:
        int mLogLevel;
        std::stringstream mStream;
        LogSystemBase* mLogSytemPtr;
    };
}

//定义日志宏
UTILITY_EXPORT LogSystemNS::LogObject LOG(int lvl = LogSystemNS::LOG_LVL_INFO, LogSystemNS::LogSystemBase* pLogSystem = NULL);

#endif
