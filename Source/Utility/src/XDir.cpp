#include "../include/XDir.h"
#include "../include/XFile.h"
#include "../include/StlUtil.h"

#ifdef WIN32
#include <direct.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <io.h>
#elif defined(__linux__)
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

namespace IOx
{
    //==============================
    //=========DirVisitor===========
    XDir::DirVisitor::DirVisitor()
        : mFilterToken("*.*")
    {

    }

    XDir::DirVisitor::~DirVisitor()
    {

    }

    bool XDir::DirVisitor::apply( XFile& rFile )
    {
        return false;
    }

    bool XDir::DirVisitor::apply( XDir& rDir )
    {
        return false;
    }

    void XDir::DirVisitor::setFilter( const std::string& rToken )
    {
        mFilterToken = rToken;
    }

    std::string& XDir::DirVisitor::filter()
    {
        return mFilterToken;
    }

    const std::string& XDir::DirVisitor::filter() const
    {
        return mFilterToken;
    }

    //删除所有文件文件夹访问器
    class RemoveDirVisitor : public XDir::DirVisitor
    {
    public:
        RemoveDirVisitor(){}
        ~RemoveDirVisitor(){}

        bool apply( XDir& rDir )
        {
            RemoveDirVisitor rmDir;
            rDir.travel(rmDir);

            rDir.remove();

            return true;
        }

        bool apply(XFile& rFile)
        {
            rFile.remove();

            return true;
        }
    };

    //获取文件访问器
    class FileListVisitor : public XDir::DirVisitor
    {
    public:
        FileListVisitor(std::list<XFile>& rFileList, const std::string& rFilter)
            : mFileListRef(rFileList)
        {
            setFilter(rFilter);
        }

        ~FileListVisitor(){}

        bool apply(XFile& rFile)
        {
            //过滤判断?
            mFileListRef.push_back(rFile);

            return true;
        }

    protected:
        std::list<XFile>& mFileListRef;
    };

    //==============================
    //=============XDir=============
    XDir::XDir( const std::string& strPath )
    {
        setDirPath(strPath);
    }

    XDir::~XDir()
    {

    }

    bool XDir::exist() const
    {
        return stlu::fileExist(mAbsolutePath);
    }

    std::string XDir::absolutePath() const
    {
        return mAbsolutePath;
    }

    std::string XDir::relativePath() const
    {
        return mRelativePath;
    }

    bool XDir::getAllFiles( std::list<XFile>& rLstFile, const std::string& strFilter) 
    {
        FileListVisitor flstVisitor(rLstFile, strFilter);
        travel(flstVisitor);

        return false;
    }

    void XDir::travel( DirVisitor& rVisitor)
    {
#ifdef WIN32
        std::string strFindString = mAbsolutePath + "/" + rVisitor.filter();
        long hFile = 0;
        _finddata_t fileinfo;
        if((hFile = (long)_findfirst(strFindString.c_str(), &fileinfo)) < 0)
        {
            return;
        }

        do
        {
            //检查是不是目录
            //如果不是,则进行处理
            if((fileinfo.attrib & _A_SUBDIR) == 0)
            {
                XFile xFile(mAbsolutePath + "/" + std::string(fileinfo.name));
                rVisitor.apply(xFile);
            }
            //处理目录
            else
            {
                //去掉.与..目录
                if (std::string(fileinfo.name) == "." || std::string(fileinfo.name) == "..")
                {
                    continue;
                }

                XDir xDir(mAbsolutePath + "/" + std::string(fileinfo.name));
                rVisitor.apply(xDir);
            }
        }
        while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
#elif defined(__linux__)

#endif
    }

    bool XDir::createFile( const std::string& strFileName )
    {
        if (!exist())
        {
            return false;
        }
        std::string strFile = mAbsolutePath + "/" + strFileName;
        XFile xFile(strFile);
        return xFile.create();
    }

    bool XDir::createDir( const std::string& strDirName )
    {
#ifdef WIN32
        int nRet = _mkdir(strDirName.c_str());
#elif defined(__linux__)
		int nRet = mkdir(strDirName.c_str(), S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
#endif
        return (nRet == 0);
    }

    bool XDir::removeFile( const std::string& strFileName )
    {
        if (!exist())
        {
            return false;
        }
        std::string strFile = mAbsolutePath + "/" + strFileName;
        XFile xFile(strFile);
        return xFile.remove();
    }

    bool XDir::removeDir( const std::string& strDirName )
    {
        RemoveDirVisitor rmVisitor;
        travel(rmVisitor);

        return rmdir(strDirName.c_str());
    }

    bool XDir::valid() const
    {
        return exist();
    }

    bool XDir::getAllDir( std::list<XDir>& rLstDir )
    {
        return false;
    }

    bool XDir::create()
    {
        if (exist())
        {
            return true;
        }
        return false;
    }

    bool XDir::remove()
    {
        if (!exist())
        {
            return true;
        }
        return false;
    }

    void XDir::setDirPath( const std::string& strDirPath )
    {
        //获取当前工作路径
        std::string strModuleDir = stlu::moduleDir();
        stlu::replace(strModuleDir, "\\", "/");
        std::vector<std::string> vecModule;
        stlu::split(strModuleDir, "/", vecModule);

		//如果不是以"/"结束那么去掉最后的文件名?

        if (isAbsolutePath(strDirPath))
        {
            mAbsolutePath = strDirPath;

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
			int nBigger = ((vec.size() > vecModule.size()) ? vecModule.size() : vec.size());
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
			if (strTempRelative == "")
			{
				mRelativePath = "./";
			}
			else
			{
				mRelativePath = strTempRelative;
			}
        }
        else
        {
            mRelativePath = strDirPath;
            //绝对路径一定可以计算
            stlu::replace(mRelativePath, "\\", "/");
            std::vector<std::string> vec;
            stlu::split(mRelativePath, "/", vec);

            //这里的相对路径表示形式"./","../../xx/","xx/"
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
    }

    bool XDir::isAbsolutePath( const std::string& strPath )
    {
        //windows上,第二个字符为:则认为绝对路径
#if defined(WIN32)
        return strPath[1] == ':';
#else
        return strPath[0] == '/';
#endif
    }

	XDir XDir::prevDir()
	{
		std::string strPath = mAbsolutePath;
		if (stlu::isEndWith(strPath, "/"))
		{
			//
		}
		//这里需要考虑,结尾处的"/"或"\\"
		stlu::eraserLastOf(strPath, "/");
		return XDir(strPath);
	}

	XDir XDir::append(const std::string& strAppendPath)
	{
		std::string strPath = mAbsolutePath;
		if (!stlu::isEndWith(strPath, "/") && !stlu::isEndWith(strPath, "\\"))
		{
			strPath += "/";
		}
		return XDir(strPath + strAppendPath);
	}

}
