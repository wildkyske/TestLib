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
        LOG_LVL_NULL = 0,   //û�м���ʲô������
        LOG_LVL_INFO = 0x01,       //��ͼ��𣬳�����Ϣ��־
        LOG_LVL_NOTICE = 0x02,     //���Ѽ���
        LOG_LVL_WARNING = 0x04,    //���漶��
        LOG_LVL_ERROR = 0x08,      //���󼶱�
        LOG_LVL_FATAL = 0x10,      //��������
        LOG_LVL_USER = 0x20,        //�û�����
        LOG_LVL_DUMP = 0x80000000,  //dump����,���⼶��
        LOG_LVL_ALL = 0xffffffff,   //���м���
    };

    UTILITY_EXPORT std::string logLvlToString(int lvl);

    UTILITY_EXPORT std::wstring logLvlToWideString(int lvl);

    UTILITY_EXPORT std::string logLvlMaskToString(int nLvl);

    //������ʾ�ʹ洢��־�ĵط�
    class UTILITY_EXPORT Logger 
    {
    public:
        Logger();
        virtual ~Logger();

        //��ʼ����־,�����ַ�Ͷ˿�,�ļ���־�����ļ�·��
        virtual bool initialise(const std::string& strAddr, const std::string& strPort = "");

        //������־��¼��
        virtual void cleanup();

        void onLog(int lvl, const std::string& logTxt);

        //������־MASK
        void setLogMask(int nLogMask);

        //����ĳ������
        void enableLvl(int nLvl);

        //��ֹĳ������
        void disableLvl(int nLvl);
    protected:

        virtual void _onLog(int lvl, const std::string& logTxt) = 0;

    protected:
        int mLogMask;
        
    };

    /*
        @. �ļ���־.
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
    	Brief:		���ֽ��� - �ļ���¼��
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
        @. ����̨��־
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
        @. ��־ϵͳ��ͨ���۲���ģʽʵ��
        ->��һ��������<<������
    */
    class UTILITY_EXPORT LogSystemBase : public Subject<Logger>
    {
    public:

        LogSystemBase();

        virtual ~LogSystemBase();

        //���м�����Ϣ����־
        void notify(int lvl, const std::string& txt);
        
        // @Brief ������־���� [12/10/2013 kyske]
        void setLogMask(int nMask);
        
        // @Brief ��־�����Ƿ���� [12/10/2013 kyske]
        bool isLogMaskEnable(int nMask) const;

        // @Brief ������ [12/10/2013 kyske]
        void enableLvl(int nLvl);

        // @Brief ���ü��� [12/10/2013 kyske]
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

        //��д���ֲ�����
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

        //��д���ֲ�����
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

//������־��
UTILITY_EXPORT LogSystemNS::LogObject LOG(int lvl = LogSystemNS::LOG_LVL_INFO, LogSystemNS::LogSystemBase* pLogSystem = NULL);

#endif
