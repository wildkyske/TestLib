#include "../include/XFile.h"
#include "../include/XDir.h"
#include "../include/StlUtil.h"
#include <vector>

namespace IOx
{
    XFile::XFile( const std::string& strFilePath )
        : mFileSize(0)
    {
        setFilePath(strFilePath);
    }

    XFile::XFile( const XFile& rhs )
    {
        *this = rhs;
    }

	XFile::XFile(const XDir& rDir, const std::string& strFileName)
	{
		std::string strPath = rDir.absolutePath();
		if (!stlu::isEndWith(strPath, "/") && !stlu::isEndWith(strPath, "\\"))
		{
			strPath += "/";
		}
		setFilePath(strPath + strFileName);
	}

    XFile::~XFile()
    {
        close();
    }

    bool XFile::operator==( const XFile& rhs )
    {
        if (this == &rhs)
        {
            return true;
        }

        if (mAbsolutePath != rhs.mAbsolutePath)
        {
            return false;
        }

        if (mRelativePath != rhs.mRelativePath)
        {
            return false;
        }

        if (mFileSize != rhs.mFileSize)
        {
            return false;
        }

        return true;
    }

    XFile& XFile::operator=( const XFile& rhs )
    {
        if (this == &rhs)
        {
            return *this;
        }

        close();

        mAbsolutePath = rhs.mAbsolutePath;
        mRelativePath = rhs.mRelativePath;
        mFileSize = rhs.mFileSize;

        return *this;
    }

    bool XFile::exist() const
    {
        if (mAbsolutePath.empty())
        {
            return false;
        }

        return stlu::fileExist(mAbsolutePath);
    }

    std::string XFile::absolutePath() const
    {
        return mAbsolutePath;
    }

    std::string XFile::relativePath() const
    {
        return mRelativePath;
    }

    bool XFile::valid() const
    {
        return exist();
    }

    std::string XFile::suffix() const
    {
        if (!valid())
        {
            return "";
        }

        return stlu::parseFileSuffix(mAbsolutePath);
    }

    std::string XFile::baseName() const
    {
        if (!valid())
        {
            return "";
        }

        return stlu::parseFileBaseName(mAbsolutePath);
    }

    std::string XFile::fileName() const
    {
        if (!valid())
        {
            return "";
        }

        return stlu::parseFileName(mAbsolutePath);
    }

    bool XFile::open( bool bReadOnly )
    {
        close();

        mFileSize = stlu::fileSize(mAbsolutePath);

        if (bReadOnly)
        {
            //读取时,保证存在
            if (!valid())
            {
                return false;
            }

            mReadStream.open(mAbsolutePath.c_str(), std::ios::binary | std::ios::in);

            return mReadStream.is_open();
        }
        else
        {
            if (mReadStream.is_open())
            {
                mReadStream.close();
            }
            
            mWriteStream.open(mAbsolutePath.c_str(), std::ios::binary | std::ios::out | std::ios::ate);

            return mWriteStream.is_open();
        }
    }

    bool XFile::read( unsigned char* pBuffer, int nSize /*= -1*/ )
    {
        if (pBuffer == NULL)
        {
            return false;
        }

        if (!mReadStream.is_open())
        {
            return false;
        }

        int nReadSize = nSize;
        if (nReadSize < 0)
        {
            nReadSize = mFileSize;
        }

        if (nReadSize == 0)
        {
            return true;
        }

        /*int nRet = */mReadStream.read((char*)pBuffer, nReadSize);
        
        return true;
    }

    bool XFile::write( unsigned char* pBuffer, int nSize )
    {
        if (pBuffer == NULL)
        {
            return false;
        }

        if (!mWriteStream.is_open())
        {
            return false;
        }

        if (nSize < 0)
        {
            return false;
        }

        if (nSize == 0)
        {
            return true;
        }

        mWriteStream.write((const char*)pBuffer, nSize);

        mFileSize += nSize;

        return true;
    }

    void XFile::close()
    {
        if (mReadStream.is_open())
        {
            mReadStream.close();
        }

        if (mWriteStream.is_open())
        {
            mWriteStream.close();
        }
    }

    bool XFile::isOpen() const
    {
        return (mWriteStream.is_open() || mReadStream.is_open());
    }

    bool XFile::create()
    {
        return stlu::fileCreate(mAbsolutePath);
    }

    bool XFile::remove()
    {
        if (isOpen())
        {
            return false;
        }
        return stlu::fileRemove(mAbsolutePath);
    }

    int XFile::size() const
    {
        return mFileSize;
    }

    void XFile::clear()
    {
        close();
        mWriteStream.open(mAbsolutePath.c_str(), std::ios::trunc | std::ios::out);
        mWriteStream.close();
    }

    void XFile::setFilePath( const std::string& strFilePath )
    {
        //设置路径前,先关闭流
        close();

        //获取当前工作路径
        std::string strModuleDir = stlu::moduleDir();
        stlu::replace(strModuleDir, "\\", "/");
        std::vector<std::string> vecModule;
        stlu::split(strModuleDir, "/", vecModule);

        //计算绝对路径和相对路径
        if (isAbsolutePath(strFilePath))
        {
            mAbsolutePath = strFilePath;
            mRelativePath = "";

            stlu::replace(mAbsolutePath, "\\", "/");
            std::vector<std::string> vec;
            stlu::split(mAbsolutePath, "/", vec);

            if (vecModule.empty() || vec.empty())
            {
                return;
            }

            if (vecModule[0] != vec[0])
            {
                return;
            }

            std::vector<std::string> vecRlt;
            std::vector<std::string> vecRlt2;
            //查询到不同点
            bool bFindX = false;
            int nBigger = ((vec.size() > vecModule.size()) ? vec.size() : vecModule.size());
            for (int i = 0; i < nBigger; ++i)
            {
                if (!bFindX)
                {
                    if (vecModule[i] == vec[i])
                    {
                        continue;
                    }
                }

                bFindX = true;

                //相对路径[去掉exe文件名]
                if (i < vecModule.size() - 1)
                {
                    vecRlt.push_back("..");
                }
                
                if (i < vec.size())
                {
                    vecRlt2.push_back(vec[i]);
                }
            }

            std::string strTempRelative;
            for (int i = 0; i < vecRlt.size(); ++i)
            {
                strTempRelative += vecRlt[i];
                strTempRelative += "/";
            }

            for (int i = 0; i < vecRlt2.size(); ++i)
            {
                strTempRelative += vecRlt2[i];
                if (i < (vecRlt2.size() - 1))
                {
                    strTempRelative += "/";
                }
            }

            //计算相对路径
            mRelativePath = strTempRelative;
        }
        else
        {
            //绝对路径一定可以计算
            mRelativePath = strFilePath;

            stlu::replace(mRelativePath, "\\", "/");
            std::vector<std::string> vec;
            stlu::split(mRelativePath, "/", vec);

            //这里的相对路径表示形式"./","../../xx/dd.txt","xx/dd.txt","dd.txt"
            std::vector<std::string> vecRlt = vecModule;
            //去掉exe文件名
            vecRlt.pop_back();
            for (int i = 0; i < vec.size(); ++i)
            {
                if (vec[i] == ".")
                {
                    continue;
                }
                else if (vec[i] == "..")
                {
                    vecRlt.pop_back();
                }
                else
                {
                    vecRlt.push_back(vec[i]);
                }
            }

            std::string strRlt;
            for (int i = 0; i < vecRlt.size() - 1; ++i)
            {
                strRlt += vecRlt[i];
                strRlt += "/";
            }
            strRlt += vecRlt.back();
            //计算绝对路径
            mAbsolutePath = strRlt;
        }

        mFileSize = stlu::fileSize(mAbsolutePath);
    }

    bool XFile::isAbsolutePath( const std::string& strFilePath )
    {
        //windows上,第二个字符为:则认为绝对路径
		if (strFilePath.empty())
		{
			return false;
		}
#if defined(WIN32)
        return strFilePath[1] == ':';
#else
        return strFilePath[0] == '/';
#endif
    }

	void XFile::dir(XDir& rDir)
	{
		rDir.setDirPath(absoluteDir());
	}

	std::string XFile::absoluteDir() const
	{
		std::string strRlt = mAbsolutePath;
		stlu::eraserLastOf(strRlt, "/");
		return strRlt;
	}

	XFile XFile::getApplicationPath()
	{
		XFile fFile(stlu::moduleDir());
		
		return fFile;
	}

}
