#include "../include/StlUtil.h"

#ifdef WIN32
#include <Windows.h>
#include <direct.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <io.h>
#elif __linux__
#include <unistd.h>
#include <sys/stat.h> 
#endif

namespace stlu
{
	std::string upper(const std::string& strSrc)
	{
		std::string result = strSrc;
		std::transform(result.begin(),result.end(), result.begin(), ::toupper);
		return result;
	}

    std::wstring upper( const std::wstring& strSrc )
    {
        std::wstring result = strSrc;
        std::transform(result.begin(),result.end(), result.begin(), ::toupper);
        return result;
    }

	std::string lower(const std::string& strSrc)
	{
        std::string result = strSrc;
		std::transform(result.begin(),result.end(), result.begin(), ::tolower);
		return result;
	}

    std::wstring lower( const std::wstring& strSrc )
    {
        std::wstring result = strSrc;
        std::transform(result.begin(),result.end(), result.begin(), ::tolower);
        return result;
    }

    std::string trimC(const std::string& strSrc)
	{
        std::string result = strSrc;
		trim(result);
		return result;
	}

    std::wstring trimC( const std::wstring& strSrc )
    {
        std::wstring result = strSrc;
        trim(result);
        return result;
    }

	//========================***====================
    void upper(std::string& strSrc)
	{
		std::transform(strSrc.begin(),strSrc.end(), strSrc.begin(), ::toupper);
	}

    void upper(std::wstring& strSrc)
    {
        std::transform(strSrc.begin(),strSrc.end(), strSrc.begin(), ::toupper);
    }

    void lower(std::string& strSrc)
	{
		std::transform(strSrc.begin(),strSrc.end(), strSrc.begin(), ::tolower);
	}

    void lower(std::wstring& strSrc)
    {
        std::transform(strSrc.begin(),strSrc.end(), strSrc.begin(), ::tolower);
    }

    void trimLeft(std::string& strSrc, const std::string& strToken)
	{
		const int BEGIN_POSITION = 0;
		strSrc.erase(BEGIN_POSITION, strSrc.find_first_not_of(strToken));
	}

    void trimLeft(std::wstring& strSrc, const std::wstring& strToken)
    {
        const int BEGIN_POSITION = 0;
        strSrc.erase(BEGIN_POSITION, strSrc.find_first_not_of(strToken));
    }

    void trimRight(std::string& strSrc, const std::string& strToken)
	{
		strSrc.erase(strSrc.find_last_not_of(strToken) + 1);
	}

    void trimRight(std::wstring& strSrc, const std::wstring& strToken)
    {
        strSrc.erase(strSrc.find_last_not_of(strToken) + 1);
    }

    void trim(std::string& strSrc)
	{
		trimLeft(strSrc);
        trimLeft(strSrc, " ");
		trimRight(strSrc);
        trimRight(strSrc, "\r");
	}

    void trim(std::wstring& strSrc)
    {
        trimLeft(strSrc);
        trimLeft(strSrc, L" ");
        trimRight(strSrc);
        trimRight(strSrc, L"\r");
    }

    void replace(std::string& strSrc, const std::string& strToken, const std::string& strToken2)
	{
		//strSrc.replace(strSrc.find(strToken), strToken.size(), strToken2.c_str());
        std::string::size_type pos = 0;
        std::string::size_type a = strToken.size();
        std::string::size_type b = strToken2.size();
        while ((pos = strSrc.find(strToken, pos)) != std::string::npos)
        {
            strSrc.replace(pos, a, strToken2);
            pos += b;
        }
	}

    void replace(std::wstring& strSrc, const std::wstring& strToken, const std::wstring& strToken2)
    {
        strSrc.replace(strSrc.find(strToken), strToken.size(), strToken2.c_str());
    }
	
    bool isStartWith(const std::string& strSrc, const std::string& strToken)
	{
		return (0 == strSrc.compare(0, strToken.size(), strToken));
	}

    bool isStartWith(const std::wstring& strSrc, const std::wstring& strToken)
    {
        return (0 == strSrc.compare(0, strToken.size(), strToken));
    }

    bool isEndWith(const std::string& strSrc, const std::string& strToken)
	{
		return (0 == strSrc.compare(strSrc.size() - strToken.size(), strToken.size(), strToken));
	}

    bool isEndWith(const std::wstring& strSrc, const std::wstring& strToken)
    {
        return 0 == strSrc.compare(strSrc.size() - strToken.size(), strToken.size(), strToken);
    }

    void split(const std::string& strSrc, 
        const std::string& token, 
        std::vector<std::string>& vStr)
    {
        vStr.clear();
        std::string::size_type index = 0;
        std::string temp = strSrc;
        trimLeft(temp, token);
        trimRight(temp, token);
        while((index = temp.find_first_of(token)) != -1)
        {
            vStr.push_back(temp.substr(0, index));
            temp = temp.substr(index);
            trimLeft(temp, token);
        }
        vStr.push_back(temp);
    }

    void split(const std::wstring& strSrc, 
        const std::wstring& token, 
        std::vector<std::wstring>& vStr)
    {
        vStr.clear();
        std::wstring::size_type index = 0;
        std::wstring temp = strSrc;
        trimLeft(temp, token);
        trimRight(temp, token);
        while((index = temp.find_first_of(token)) != -1)
        {
            vStr.push_back(temp.substr(0, index));
            temp = temp.substr(index);
            trimLeft(temp, token);
        }
        vStr.push_back(temp);
    }

    std::vector<std::string> split(const std::string& strSrc, const std::string& token)
	{
        std::vector<std::string> result;
        if (strSrc.length() == 0)
        {
            return result;
        }
        std::string::size_type last = strSrc.find_first_not_of(token);
		std::string::size_type index = 0;
		std::string::size_type temp = 0;

		while (temp != -1)
		{
			last = last + index + temp;
			index = strSrc.substr(last).find_first_of(token);
			if (-1 == index)
			{
				result .push_back(strSrc.substr(strSrc.find_last_of(token) + 1));
				break;
			}
			result.push_back(strSrc.substr(last, index));
            temp = last + index;
			temp = strSrc.substr(temp).find_first_not_of(token);
		}
		return result;
	}

    std::vector<std::wstring> split( const std::wstring& strSrc, const std::wstring& token )
    {
        std::vector<std::wstring> result;
        if (strSrc.length() == 0)
        {
            return result;
        }
        std::wstring::size_type last = strSrc.find_first_not_of(token);
        std::wstring::size_type index = 0;
        std::wstring::size_type temp = 0;

        while (temp != -1)
        {
            last = last + index + temp;
            index = strSrc.substr(last).find_first_of(token);
            if (-1 == index)
            {
                result .push_back(strSrc.substr(strSrc.find_last_of(token) + 1));
                break;
            }
            result.push_back(strSrc.substr(last, index));
            temp = last + index;
            temp = strSrc.substr(temp).find_first_not_of(token);
        }
        return result;
    }

    void reverse(std::string& strSrc)
	{
		std::reverse(strSrc.begin(), strSrc.end());
	}

    void reverse(std::wstring& strSrc)
    {
        std::reverse(strSrc.begin(), strSrc.end());
    }

    //----------------------------------------------------
    //解析后缀名
    //----------------------------------------------------
    std::string extendName(const std::string& strSrc, const std::string& strToken)
	{
		std::string result;
		std::string::size_type pos = strSrc.rfind(strToken.c_str());
		result = strSrc.substr(pos == std::string::npos ? strSrc.length() : pos + 1);
		return result;
	}

    std::wstring extendName( const std::wstring& strSrc, const std::wstring& strToken /*= "."*/ )
    {
        std::wstring result;
        std::wstring::size_type pos = strSrc.rfind(strToken.c_str());
        result = strSrc.substr(pos == std::wstring::npos ? strSrc.length() : pos + 1);
        return result;
    }

    std::string complateDir(const std::string& path, const std::string& token)
    {
        if (path.length() <= 0)
        {
            return std::string("./");
        }

        std::string ret = path;
        if (!isEndWith(path, "/") && !isEndWith(path, "\\"))
        {
            ret += token;
        }

        return ret;
    }

    std::wstring complateDir(const std::wstring& path, const std::wstring& token)
    {
        if (path.length() <= 0)
        {
            return std::wstring(L"./");
        }

        std::wstring ret = path;
        if (!isEndWith(path, L"/") && !isEndWith(path, L"\\"))
        {
            ret += token;
        }

        return ret;
    }

    void eraserSuffix(std::string& str)
    {
        std::string::size_type index = str.find_last_of(".");
        if (-1 == index)
        {
            return;
        }

        str = str.substr(0, index);
    }

    void eraserSuffix(std::wstring& str)
    {
        std::wstring::size_type index = str.find_last_of(L".");
        if (-1 == index)
        {
            return;
        }

        str = str.substr(0, index);
    }

	void eraserLastOf(std::string& str, const std::string& token)
	{
		std::string::size_type index = str.find_last_of(token);
		if (-1 == index)
		{
			return ;
		}
		str = str.substr(0, index);
	}

	void eraserLastOf(std::wstring& str, const std::wstring& token)
	{
		std::wstring::size_type index = str.find_last_of(token);
		if (-1 == index)
		{
			return ;
		}
		str = str.substr(0, index);
	}

    void endOfString(std::string& str, const std::string& token)
    {
        std::string::size_type index = str.find_last_of(token);
        if (-1 == index)
        {
            return ;
        }
        str = str.substr(index + 1);
    }

    void endOfString(std::wstring& str, const std::wstring& token )
    {
        std::wstring::size_type index = str.find_last_of(token);
        if (-1 == index)
        {
            return ;
        }
        str = str.substr(index + 1);
    }

    std::string parseFileName(const std::string& path)
    {
        int idx = path.find_last_of("/");
        if (idx < 0)
        {
            idx = path.find_last_of("\\");
            if (idx < 0)
            {
                return path;
            }
        }
        return path.substr(idx + 1);
    }

    std::wstring parseFileName(const std::wstring& path)
    {
        int idx = path.find_last_of(L"/");
        if (idx < 0)
        {
            idx = path.find_last_of(L"\\");
            if (idx < 0)
            {
                return path;
            }
        }
        return path.substr(idx + 1);
    }

    std::string parseFileSuffix( const std::string& strPath )
    {
        std::string strFileName = parseFileName(strPath);
        int nDot1st = strFileName.find_first_of(".");
        if (nDot1st < 0)
        {
            return "";
        }
        return strFileName.substr(nDot1st + 1);
    }

    std::wstring parseFileSuffix( const std::wstring& strPath )
    {
        std::wstring strFileName = parseFileName(strPath);
        int nDot1st = strFileName.find_first_of(L".");
        if (nDot1st < 0)
        {
            return L"";
        }
        return strFileName.substr(nDot1st + 1);
    }

    std::string parseFileBaseName( const std::string& strPath )
    {
        std::string strFileName = parseFileName(strPath);
        int nDot1st = strFileName.find_first_of(".");
        if (nDot1st < 0)
        {
            return "";
        }
        return strFileName.substr(0, nDot1st);
    }

    std::wstring parseFileBaseName( const std::wstring& strPath )
    {
        std::wstring strFileName = parseFileName(strPath);
        int nDot1st = strFileName.find_first_of(L".");
        if (nDot1st < 0)
        {
            return L"";
        }
        return strFileName.substr(0, nDot1st);
    }

    tstring date()
    {
        time_t _now;
        time(&_now);
        char* str_time = asctime(gmtime(&_now));
        return CodeConvert::str2x(std::string(str_time));
    }

    std::string dateMb()
    {
        time_t _now;
        time(&_now);
        char* str_time = asctime(gmtime(&_now));
        return std::string(str_time);
    }

    std::wstring dateW()
    {
        std::string strDate = dateMb();
        std::wstring strRlt;
        CodeConvert::str2wstr(strDate, strRlt);
        return strRlt;
    }
};

namespace stlu
{
    bool fileCreate( const std::string& strFilePath )
    {
        if (fileExist(strFilePath))
        {
            return true;
        }

        FILE* fp = NULL;
        if(NULL == (fp = fopen(strFilePath.c_str(), "wb")))
        {
            return false;
        }
        fclose(fp);
        return true;
    }

    bool fileCreate( const std::wstring& strFilePath )
    {
        std::string strPath;
        CodeConvert::wstr2str(strFilePath, strPath);
        return fileCreate(strPath);
    }

    bool fileExist( const std::string& strFilePath )
    {
        return -1 != access(strFilePath.c_str(), 0);
    }

    bool fileExist( const std::wstring& strFilePath )
    {
        std::string strPath;
        CodeConvert::wstr2str(strFilePath, strPath);
        return fileExist(strPath);
    }

    unsigned int fileSize( const std::string& strFilePath )
    {
        FILE* fp = NULL;
        if(NULL == (fp = fopen(strFilePath.c_str(), "rb")))
        {
            return -1;
        }
        fseek(fp, 0, SEEK_END);
        int len = ftell(fp);
        fclose(fp);
        return len;
    }

    unsigned int fileSize( const std::wstring& strFilePath )
    {
        std::string strPath;
        CodeConvert::wstr2str(strFilePath, strPath);
        return fileSize(strPath);
    }

    bool fileRemove( const std::string& strFilePath )
    {
        if (!fileExist(strFilePath))
        {
            return true;
        }
        return (remove(strFilePath.c_str()) == 0);
    }

    bool fileRemove( const std::wstring& strFilePath )
    {
        std::string strPath;
        CodeConvert::wstr2str(strFilePath, strPath);
        return fileRemove(strPath);
    }

    std::string currentDir()
    {
        char buf[256 + 1] = {0};
#ifdef WIN32
        _getcwd(buf, 256);
#elif __linux__
        getcwd(buf, 256);
#endif
        return std::string(buf);
    }

	void changeDir(const std::string& strPath)
	{
#ifdef WIN32
		_chdir(strPath.c_str());
#elif __linux__
		chdir(strPath.c_str());
#endif
	}

    std::string moduleDir()
    {
#ifdef WIN32
        xchar szFileName[256] = {0};
        GetModuleFileName(NULL, szFileName, 256);
        return CodeConvert::x2str(tstring(szFileName));
#elif defined(__linux__)
       char szFileName[256] = {0};
       //获取当前目录绝对路径
       if (NULL == getcwd(szFileName, 256))
       {
           return "";
       }
       return std::string(szFileName);
#endif
    }

    bool dirCreate( const std::string& strDirPath )
    {
#ifdef WIN32
        return (mkdir(strDirPath.c_str()) == 0);
#elif defined(__linux__)
		return (mkdir(strDirPath.c_str(), S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH) == 0);
#endif
    }

    bool dirRemove( const std::string& strDirPath )
    {
        return (rmdir(strDirPath.c_str()) == 0) ;
    }

    bool dirExist( const std::string& strDirPath )
    {
#ifdef WIN32
        bool bExist = (access(strDirPath.c_str(), 0) == 0);
        struct stat st;
        if ( stat((char*)strDirPath.c_str(), &st) < 0)
        {
            return false;
        }

        return (_S_IFDIR & st.st_mode);
#elif defined(__linux__)
		return false;
#endif
    }
}

#if defined(WIN32)
#include <Windows.h>
#elif defined(LINUX)
#include <unistd.h>
#include <sys/utime.h>
#endif

namespace stlu
{
    void sleepMS( int nMilSecond )
    {
#if defined(WIN32)
        Sleep(nMilSecond);
#elif __linux__
        usleep(nMilSecond * 1000);
#endif
    }
}
