#include "../include/LogSystem.h"
#include <assert.h>
#include "../include/StlUtil.h"

namespace LogSystemNS
{
    IMPLEMENT_SINGLETON_CLASS(LogSystem)

    //======================================
    //==日志系统
    LogSystemBase::LogSystemBase() : mLogMask(LOG_LVL_ALL)
    {

    }

    LogSystemBase::~LogSystemBase()
    {

    }

    void LogSystemBase::notify( int lvl, const std::string& txt )
    {
        Subject<Logger>::notify<void, int, const std::string&>(&Logger::onLog, lvl, txt);
    }

    void LogSystemBase::setLogMask( int nMask )
    {
        mLogMask = nMask;
    }

    bool LogSystemBase::isLogMaskEnable( int nMask ) const
    {
        return mLogMask & nMask;
    }

    void LogSystemBase::enableLvl( int nLvl )
    {
        mLogMask = mLogMask | nLvl;
    }

    void LogSystemBase::disableLvl( int nLvl )
    {
        mLogMask = (mLogMask & (~nLvl));
    }

    //=================================================
    //==日志系统基类

    Logger::Logger() : mLogMask(LOG_LVL_ALL)
    {

    }

    Logger::~Logger()
    {

    }

    void Logger::onLog( int lvl, const std::string& logTxt )
    {
        if (mLogMask & lvl)
        {
            _onLog(lvl, logTxt);
        }
    }

    bool Logger::initialise( const std::string& strParam, const std::string& strPort )
    {
        return true;
    }

    void Logger::cleanup()
    {

    }

    void Logger::setLogMask( int nLogMask )
    {
        mLogMask = nLogMask;
    }

    void Logger::enableLvl( int nLvl )
    {
        mLogMask = mLogMask | nLvl;
    }

    void Logger::disableLvl( int nLvl )
    {
        mLogMask = (mLogMask & (~nLvl));
    }

    //======================================================
    //==文件日志系统
    FileLogger::FileLogger( const std::string& filePath )
    {
        initialise(filePath, "");
    }

    FileLogger::~FileLogger()
    {
        cleanup();
    }

    bool FileLogger::initialise( const std::string& strAddr, const std::string& strPort /* = _TX */ )
    {
        if (!m_streamFile.is_open())
        {
            m_streamFile.open(strAddr.c_str(), std::ios::binary | std::ios::out | std::ios::ate);
        }
        
        return m_streamFile.is_open();
    }

    void FileLogger::cleanup()
    {
        if (m_streamFile.good())
        {
            m_streamFile.close();
        }
    }

    void FileLogger::_onLog( int lvl, const std::string& logTxt )
    {
        if (m_streamFile.fail())
        {
            return;
        }
        //TODO:
        tstring str0 = CodeConvert::str2x(logTxt);
        //m_streamFile<< stlu::date()<< _TX("[") << logLvlToWideString(lvl) << _TX("] ") << str0 << _TX("\r\n");

        //写入文本
        m_streamFile.flush();
    }

    //========================================
    //==控制台日志系统
    ConsoleLogger::ConsoleLogger()
    {

    }

    ConsoleLogger::~ConsoleLogger()
    {

    }

    void ConsoleLogger::_onLog( int lvl, const std::string& logTxt )
    {
        std::cout << stlu::dateMb() << "[" << logLvlToString(lvl) << "] " << logTxt << "\r\n";
    }

    std::string logLvlToString( int lvl )
    {
        const char* LVL_STR[7] = 
        {
            "NULL", 
            "INFO", 
            "NOTICE", 
            "WARNING", 
            "ERROR", 
            "FATAL", 
            "DUMP",
        };

        switch (lvl)
        {
        case LOG_LVL_INFO:
            {
                return LVL_STR[1];
            }
            break;
        case LOG_LVL_NOTICE:
            {
                return LVL_STR[2];
            }
            break;
        case LOG_LVL_WARNING:
            {
                return LVL_STR[3];
            }
            break;
        case LOG_LVL_ERROR:
            {
                return LVL_STR[4];
            }
            break;
        case LOG_LVL_FATAL:
            {
                return LVL_STR[5];
            }
            break;
        case LOG_LVL_DUMP:
            {
                return LVL_STR[6];
            }
            break;
        }
        return std::string(LVL_STR[0]);
    }

    std::wstring logLvlToWideString( int lvl )
    {
        const wchar_t* LVL_STR[6] =
        {
            L"LOG_LVL_NULL",
            L"LOG_LVL_INFO",
            L"LOG_LVL_NOTICE",
            L"LOG_LVL_WARNING",
            L"LOG_LVL_ERROR",
            L"LOG_LVL_FATAL",
        };

        switch (lvl)
        {
        case LOG_LVL_INFO:
            {
                return LVL_STR[1];
            }
            break;
        case LOG_LVL_NOTICE:
            {
                return LVL_STR[2];
            }
            break;
        case LOG_LVL_WARNING:
            {
                return LVL_STR[3];
            }
            break;
        case LOG_LVL_ERROR:
            {
                return LVL_STR[4];
            }
            break;
        case LOG_LVL_FATAL:
            {
                return LVL_STR[5];
            }
            break;
        }
        return std::wstring(LVL_STR[0]);
    }

    std::string logLvlMaskToString( int nLvl )
    {
        std::stringstream ss;
        
        bool bHavInfo = false;
        if (nLvl & LOG_LVL_INFO)
        {
            ss << "INFO";
            bHavInfo= true;
        }

        if (nLvl & LOG_LVL_NOTICE)
        {
            if (bHavInfo)
            {
                ss << "|";
            }
            ss << "NOTICE";

            bHavInfo= true;
        }
        else
        {
            bHavInfo = false;
        }

        if (nLvl & LOG_LVL_WARNING)
        {
            if (bHavInfo)
            {
                ss << "|";
            }
            ss << "WARNING";

            bHavInfo= true;
        }
        else
        {
            bHavInfo = false;
        }

        if (nLvl & LOG_LVL_ERROR)
        {
            if (bHavInfo)
            {
                ss << "|";
            }
            ss << "ERROR";

            bHavInfo= true;
        }
        else
        {
            bHavInfo = false;
        }

        if (nLvl & LOG_LVL_FATAL)
        {
            if (bHavInfo)
            {
                ss << "|";
            }
            ss << "FATAL";

            bHavInfo= true;
        }
        else   
        {
            bHavInfo = false;
        }

        return ss.str();
    }

    //=======================================================================
    //==
    LogObject::LogObject(int nLvl, LogSystemBase* pLogSystem)
        : mLogLevel(nLvl)
        , mLogSytemPtr(pLogSystem)
    {
        if(NULL == mLogSytemPtr)
        {
            mLogSytemPtr = LogSystem::getInstancePtr();
        }
    }

    LogObject::LogObject(const LogObject& rhs)
    {
        *this = rhs;
    }

    LogObject& LogObject::operator=(const LogObject& rhs)
    {
        if(this == &rhs)
        {
            return *this;
        }

        mLogLevel = rhs.mLogLevel;
        mLogSytemPtr = rhs.mLogSytemPtr;
        //mStream = rhs.mStream;

        return *this;
    }

    LogObject::~LogObject()
    {
        if (mStream.good() && NULL != mLogSytemPtr)
        {
            if (mLogSytemPtr->isLogMaskEnable(mLogLevel))
            {
                mLogSytemPtr->notify(mLogLevel, mStream.str());
            }
        }
    }

    LogObject& LogObject::operator<<( float nVal )
    {
        mStream<<nVal<<" ";
        return *this;
    }

    LogObject& LogObject::operator<<( double nVal )
    {
        mStream<<nVal<<" ";
        return *this;
    }

    LogObject& LogObject::operator<<( bool bVal )
    {
        mStream<<bVal<<" ";
        return *this;
    }

    LogObject& LogObject::operator<<( short nVal )
    {
        mStream<<nVal<<" ";
        return *this;
    }

    LogObject& LogObject::operator<<( int nVal )
    {
        mStream<<nVal<<" ";
        return *this;
    }

    LogObject& LogObject::operator<<( long nVal )
    {
        mStream<<nVal<<" ";
        return *this;
    }

    LogObject& LogObject::operator<<( unsigned char nVal )
    {
        mStream<<nVal<<" ";
        return *this;
    }

    LogObject& LogObject::operator<<( unsigned int nVal )
    {
        mStream<<nVal<<" ";
        return *this;
    }

    LogObject& LogObject::operator<<( unsigned long nVal )
    {
        mStream<<nVal<<" ";
        return *this;
    }

    LogObject& LogObject::operator<<( const std::wstring& strVal )
    {
        std::string str0;
        CodeConvert::wstr2str(strVal, str0);
        mStream<<str0<<" ";
        return *this;
    }

    LogObject& LogObject::operator<<( char nVal )
    {
        mStream<<nVal<<" ";
        return *this;
    }

    LogObject& LogObject::operator<<( wchar_t nVal )
    {
        mStream<<nVal<<" ";
        return *this;
    }

    LogObject& LogObject::operator<<( const std::string& strVal )
    {
        mStream << strVal << " ";
        return *this;
    }

    LogObject& LogObject::operator<<( char* pszVal )
    {
        if (NULL == pszVal)
        {
            return *this;
        }

        std::string str0 =std::string(pszVal);
        mStream<<str0<<" ";
        return *this;
    }

    LogObject& LogObject::operator<<( const char* pszVal )
    {
        if (NULL == pszVal)
        {
            return *this;
        }

        std::string str0 = std::string(pszVal);
        mStream<<str0<<" ";
        return *this;
    }

    LogObject& LogObject::operator<<( wchar_t* pszVal )
    {
        if (NULL == pszVal)
        {
            return *this;
        }

        std::string str0; 
        CodeConvert::wstr2str(std::wstring(pszVal), str0);
        mStream << str0 << " ";
        return *this;
    }

    LogObject& LogObject::operator<<( const wchar_t* pszVal )
    {
        if (NULL == pszVal)
        {
            return *this;
        }

        std::string str0;
        CodeConvert::wstr2str(std::wstring(pszVal), str0);
        mStream << str0 << " ";
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////
    ////空流 - 基类

    NullStream::NullStream( )
    {

    }

    NullStream::~NullStream()
    {

    }

    NullStream& NullStream::operator<<( float nVal )
    {
        return *this;
    }

    NullStream& NullStream::operator<<( double nVal )
    {
        return *this;
    }

    NullStream& NullStream::operator<<( bool bVal )
    {
        return *this;
    }

    NullStream& NullStream::operator<<( char nVal )
    {
        return *this;
    }

    NullStream& NullStream::operator<<( wchar_t nVal )
    {
        return *this;
    }

    NullStream& NullStream::operator<<( short nVal )
    {
        return *this;
    }

    NullStream& NullStream::operator<<( int nVal )
    {
        return *this;
    }

    NullStream& NullStream::operator<<( long nVal )
    {
        return *this;
    }

    NullStream& NullStream::operator<<( unsigned char nVal )
    {
        return *this;
    }

    NullStream& NullStream::operator<<( unsigned int nVal )
    {
        return *this;
    }

    NullStream& NullStream::operator<<( unsigned long nVal )
    {
        return *this;
    }

    NullStream& NullStream::operator<<( const std::wstring& strVal )
    {
        return *this;
    }

    NullStream& NullStream::operator<<( const std::string& strVal )
    {
        return *this;
    }

    //=========================================================================
    //==========MBCS文件记录器

    FileLoggerMBCS::FileLoggerMBCS()
    {

    }

    FileLoggerMBCS::FileLoggerMBCS( const std::string& filePath )
    {
        std::string strFileName = filePath;
        initialise(strFileName, "");
    }

    FileLoggerMBCS::~FileLoggerMBCS()
    {
        cleanup();
    }

    void FileLoggerMBCS::_onLog( int lvl, const std::string& logTxt )
    {
        if (mFileStream.fail())
        {
            return;
        }
        //TODO:
        std::stringstream strTxt;
        strTxt << stlu::dateMb() << "[" << logLvlToString(lvl) << "] " <<logTxt<< "\r\n";
        std::string str0 = strTxt.str();
        mFileStream<<str0;

        //写入文本
        mFileStream.flush();
    }

    bool FileLoggerMBCS::initialise( const std::string& strAddr, const std::string& strPort /* = _TX */ )
    {
        if (!mFileStream.is_open())
        {
            std::string strFileName = strAddr;
            mFileStream.open(strFileName.c_str(), std::ios::binary | std::ios::out | std::ios::ate);
        }
        
        return mFileStream.is_open();
    }

    void FileLoggerMBCS::cleanup()
    {
        if (mFileStream.is_open())
        {
            mFileStream.close();
        }
    }
}

 LogSystemNS::LogObject LOG(int lvl, LogSystemNS::LogSystemBase* pLogSystem)
 {
     return LogSystemNS::LogObject(lvl, pLogSystem);
 }

